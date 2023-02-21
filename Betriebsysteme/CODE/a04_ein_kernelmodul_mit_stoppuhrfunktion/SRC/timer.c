/**
 * Timer module
 */
#include "timer.h"
/* ******************************************************* static vars  */
int major=0; /* major number container  */

struct timer_dev *tfdev = NULL;  /* timerf dev: devs "private" vars */
struct timer_dev *trdev = NULL;  /* timerr dev: devs "private" vars */
struct semaphore open_sem;       /* mutex to block the whole module */
/* **************************************************** file_operations */
struct file_operations timer_fops = {
    .owner   = THIS_MODULE,
    .read    = timer_read,
    .write   = timer_write,
    .open    = timer_open,
    .release = timer_release,
};
/* ****************************************************** debug function */
/* ------------------------------------------------------------ dev_dump */
/**
 * printing information of the timer_dev structure - 
 * and the current state, the timer is in. 
 */
void 
dev_dump(struct timer_dev *dev)
{       
    PDEBUG("DUMP: minor:%d"
           " - name:%s"
           " - state:%d"
           " - offset:" U64_FMT 
           " - enter_pause:" U64_FMT
           " - load:"U64_FMT "\n",
           dev->minor, 
           dev->name, 
           dev->state, 
           dev->time.offset, 
           dev->time.enter_pause, 
           dev->time.load);
}
/* ************************************************************ TIMER_INIT */
/* -------------------------------------------------------- timer_dev_init */
static void
timer_dev_init(struct timer_dev **pdev, int minor, char const *name)
{
    int res     = EXIT_FAILURE;  /* return check var for cdev_add */
    dev_t devno = 0;             /* number of this device */
    struct timer_dev *dev = NULL; /* pointer to the timer_dev struct, 
                                     that is created here */
                                     
    PDEBUG("TIMER_DEV_INIT\n");
    /* allocate the memory in the kernel mem space for timer_dev */
    dev = (struct timer_dev *)kmalloc(sizeof( struct timer_dev ), GFP_KERNEL);
    if (!dev) {
        PDEBUG( "kmalloc failed\n" );
    }

    /* fill the struct timer_dev */
    /* distinguish vars */
    dev->minor            = minor;  
    strncpy(dev->name, name, TIMER_NAME_LEN );
    
    /* state vars */
    dev->time.offset      = TIME_DEFAULT;
    dev->time.enter_pause = TIME_DEFAULT;
    dev->time.load        = TIME_DEFAULT;
    dev->state            = STATE_READY;

    /* init the device mutex 
       to preserve the dynamic local buff in read/write */
    sema_init(&dev->sem, 1);
    
    /* character driver stuff */
    cdev_init( &dev->cdev, &timer_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &timer_fops;

    devno = MKDEV( major, minor );
    res = cdev_add( &dev->cdev, devno, 1);
    /** not so hard at this*/
    if ( res ){
        PDEBUG("ERROR in cdev_add");
        printk(KERN_NOTICE "cdev_add failed at %s\n", name);
    }
    
    /* "return" the created data struct outside the function  */
    *pdev = dev;
}
/* ************************************************************ timer_init */
static int /* module_init */
timer_init()
{
    dev_t dev = 0;  /* var to get a majornumber */
    int res = EXIT_SUCCESS; /* return check var */
    sema_init(&open_sem, 1); /* module mutex */
    
    PDEBUG("INITIALISATION TIMER\n");
    
    /* register a Char driver  */
    /* also get a dynamic major number (from the OS) */
    res = alloc_chrdev_region( &dev,
                               TIMERF_MINOR, /* lowest minor */
                               NDEVS,
                               TIMER_NAME);
    major = MAJOR( dev );
    PDEBUG("MAJOR: %d\n", major);
    if( 0 > res ){
        printk(KERN_NOTICE "Unable to get %s major, error %d\n", 
               TIMER_NAME,
               res);
        res = -ENOMEM;
        return res;
    }
    
    /* INIT char dev struct */
    timer_dev_init(&tfdev, TIMERF_MINOR, TIMERF_NAME);
    timer_dev_init(&trdev, TIMERR_MINOR, TIMERR_NAME);
    
    /* CHECK if the timer_devs get exists */
    if(!tfdev){
        PDEBUG("tfdev points to NULL\n");
        res = -ENOMEM;
    } else if (!trdev) {
        PDEBUG("trdev points to NULL\n");
        res = -ENOMEM;
    }
    
    return res;
}
/* ********************************************************** timer_cleanup*/
static void /* module_exit */
timer_cleanup()
{
    dev_t devno = 0;  /* to free the and destroy the module  */
    
    PDEBUG("TIMER_CLEANUP\n");
    /* free the two timer_devs */
    if (!tfdev){ 
        PDEBUG("tfdevs point to NULL \n");
    } else {
        cdev_del(&(tfdev->cdev));
	PDEBUG("after cdev_del \n");
        kfree(tfdev);
    }    
    if (!trdev){ 
        PDEBUG("trdevs point to NULL \n");
    } else {
        cdev_del(&(trdev->cdev));
        kfree(trdev);
    }
    
    /* get Dev number...  */
    devno = MKDEV(major, TIMERF_MINOR); /* first dev num */
    /* to free the Char driver */
    unregister_chrdev_region(devno, NDEVS);
}
/* ************************************************************ timer open */
int 
timer_open(struct inode *inode, struct file *filp)
{
    struct timer_dev *dev; /* device information */
    
    /* Lock the whole thing to protect the file */
    if (1 == down_trylock(&open_sem)){
        return -EBUSY;
    }
    
    PDEBUG("TIMER_OPEN\n");
    
    /* pack the information into the file to use them in read / write */
    dev = container_of(inode->i_cdev, struct timer_dev, cdev);
    filp->private_data = dev; /* for other methods */

    return EXIT_SUCCESS;
}
/* ********************************************************* timer_release */
int 
timer_release(struct inode *inode, struct file *filp)
{
    PDEBUG("TIMER_RELEASE\n");
    /* release the file */
    up(&open_sem);
    return EXIT_SUCCESS;
}
/* ************************************************************ TIMER_READ */
/* ------------------------------------------------------------- calc_time */
u64
calc_time(struct timer_dev *dev)
{
    /* needed local time vars */
    u64 now   = get_jiffies_64();    /* time stamp for this very moment */
    u64 time  = TIME_DEFAULT;        /* return var */
    u64 pause = TIME_DEFAULT;        /* duration of pause state */
    u64 goal  = TIME_DEFAULT;        /* for revers timer: time, when the 
                                        loaded time is reached */
    
    /* PAUSE duration calculation*/
    if (STATE_PAUSE == dev->state){
        pause = now - dev->time.enter_pause;
    }
    
    /* READY is every time 0 */
    if ( STATE_READY == dev->state ) {
        time = TIME_DEFAULT;
        
    /* time calculation for forward timer */
    } else if ( TIMERF_MINOR == dev->minor ){
        time = now - ( dev->time.offset + pause);
        
    /* time calculation for backward / reverse timer */   
    } else if ( TIMERR_MINOR == dev->minor ){
        if (STATE_LOADED == dev->state) {
            time = dev->time.load;
        } else {
            goal = dev->time.offset + dev->time.load + pause;
            if (time_before64(now, goal ) ) {
                time = goal - now  ;
            } else {
                time = TIME_DEFAULT;
            }
        }
        
    } else { 
        printk(KERN_ALERT "Unknown minor %d\n", dev->minor);
    }
    
    PDEBUG("CALC_TIME : now: %llu - pause: %llu"
           " - goal: %llu - time: %llu \n",
           now, pause, goal, time);

    return time;
}
/* ------------------------------------------------------------ timer_read */
/* this function needs to be called 
 * one time returning length of buffer and 
 * second time returning 0 to terminate 
 */
ssize_t       
timer_read(struct file *filp,  
           char __user *buff,
           size_t count,
           loff_t *f_pos)
{

    unsigned long res = EXIT_SUCCESS; 
    struct timer_dev *dev = filp->private_data;
    u64 time = 0;  /* container for the timevalue */
    char *msg = NULL; /* pointer to the local kernel buffer */
    
    /* asking if at last time copy to user transfered the whole msg to buff
       if it succeed, then exit the read function with returning 0
       to get out of the loop of calling the read function */
    if ( NBUFF <= *f_pos ){
        *f_pos = 0;
        return EXIT_SUCCESS;
    }
    
    PDEBUG("TIMER_READ\n");
    down(&dev->sem); /*hardlock to protect the local dynamic buffer*/
    
    msg = (char *)kmalloc( NBUFF, GFP_KERNEL );
    if ( NULL == msg ){
        res = -ENOMEM;
        PDEBUG("ERROR: timer_read kmalloc failed!\n");
        return res; /* no mem today my buff is gone away*/
    }
    
    memset(msg, '\0',NBUFF); /* reset the buffer with NULL */

    time = calc_time(dev); /* getting the time value */ 
    
    /* filling the kernel buff with the actual infos for the user */
    if ( TIMERF_MINOR  == dev->minor ){
        sprintf( msg, TIMERF_MSG, time);
    } else if (TIMERR_MINOR == dev->minor ){
        sprintf( msg, TIMERR_MSG, time );
    }
    
    /* get the amount, what the copy_to_user function has to transfer */
    count = ( count < NBUFF )? count : NBUFF;
    
    /* transferring data from kernel buff to user buff */
    res = copy_to_user( buff, msg+(*f_pos) , count );
    
    *f_pos = count - res; /* position, until copy_to_user failed */
    if (0 != res){
        PDEBUG("copy_to_user did not transfer this amount of bytes: %lu\n",
               res);
    }
    res = count;
    
    kfree(msg);
    up(&dev->sem); /* release the mutex */
    dev_dump(dev);
    return res;
}

/* ************************************************************ timer_write */
/* -------------------------------------------------------------- GET_EVENT */
static const char cmdarr[]={ CMD_CHAR_START,    /* 's': EVENT_START    = 0 */
                             CMD_CHAR_PAUSE,    /* 'p': EVENT_PAUSE    = 1 */
                             CMD_CHAR_CONTINUE, /* 'c': EVENT_CONTINUE = 2 */
                             CMD_CHAR_RESET,    /* 'r': EVENT_RESET    = 3 */
                             CMD_CHAR_LOAD };   /* 'l': EVENT_LOAD     = 4 */
struct event_time
get_event(char const * buff)
{
    struct event_time event_time= {EVENT_UNKNOWN,0}; /* define return var */
    char * ptrcmd = NULL;   /* character position with command char in buff */
    int cmd_counter=0;          /* counts the commands in buff 
                               only one command is allowed */
    int is_time_valid = TRUE;    /* check if loaded time value is valid */
    int res = EXIT_FAILURE; /* check var for sscanf */
    int i;                  /* iteration var 
                               and because of enum: event number */
    
    PDEBUG("GET_EVENT\n");
    
    for ( i=0; CMD_NR > i; i++ ){
        ptrcmd = strchr( buff, cmdarr[i] );
        if (ptrcmd) {
            event_time.event = i;    /* enum event is arranged like cmdarr */
            cmd_counter++;
            
            /* Loaded needs an integer value to be successful */
            if ( EVENT_LOAD == event_time.event ){
                res = sscanf( ptrcmd + 1, U64_FMT, &(event_time.time) );
                if (1 != res ){
                    PDEBUG("Event_load needs an valid argument\n");
                    is_time_valid = FALSE;
                }
            }
        }
    }
    
    /* Checking if valid */
    if ( 1 != cmd_counter || !is_time_valid ){
        PDEBUG("invalid or to many arguments!\n");
        event_time.event = EVENT_UNKNOWN;
        event_time.time = 0;
    }
    PDEBUG("user input:>> %s\n", buff);
    
    return event_time;
}
/* ----------------------------------------------------------- update_state */
void
update_state( struct timer_dev *dev, const char * cmdstr )
{
    enum state new_state = dev->state;  /* define the next state var */
    struct event_time event_time = get_event( cmdstr );
    
    PDEBUG("UPDATE_STATE: \n");
    
    /* checking the global events */
    if ( EVENT_RESET == event_time.event  ){
        dev->time.offset      = TIME_DEFAULT;
        dev->time.enter_pause = TIME_DEFAULT;
        dev->time.load        = TIME_DEFAULT;
        new_state = STATE_READY;
        PDEBUG("EVERYWHERE: %s is reseted\n", dev->name);
    } else if ( EVENT_UNKNOWN == event_time.event ){
        PDEBUG("EVERYWHERE: %s gets an unknown event: do nothing!\n",
                dev->name);
    /* now the rest */
    } else {
        switch(dev->state){
            case  STATE_READY : /* -------------------------------------- READY*/
                if ( TIMERF_MINOR == dev->minor && 
                     EVENT_START == event_time.event){
                    
                    dev->time.offset = get_jiffies_64();
                    new_state= STATE_RUNNING;
                    PDEBUG("%s starts: offset changed\n",
                           dev->name);
                } else if ( TIMERR_MINOR == dev->minor &&
                            EVENT_LOAD == event_time.event) {
                    
                    dev->time.load = event_time.time;
                    new_state = STATE_LOADED;
                    PDEBUG("READY: %s was loaded: load changed\n",
                           dev->name);                
                } else {
                    PDEBUG("READY: nothing to do!\n");
                }
                break;
            case STATE_RUNNING: /* ----------------------------------- RUNNING */
                if ( EVENT_PAUSE == event_time.event ){
                    dev->time.enter_pause = get_jiffies_64();
                    new_state = STATE_PAUSE;
                    PDEBUG("RUNNING: %s was paused: enter_pause changed\n", 
                            dev->name);
                } else {
                    PDEBUG("RUNNING: nothing to do!\n");
                }
                break;
            case STATE_LOADED: /* ------------------------------------ LOADED */
                if ( TIMERR_MINOR == dev->minor &&
                     EVENT_START == event_time.event){
                    
                     dev->time.offset = get_jiffies_64();
                     new_state = STATE_RUNNING;
                     PDEBUG("LOADED: %s starts, offset changed\n", 
                             dev->name);
                } else {
                    PDEBUG("LOADED: nothing to do!\n");
                }
                break;
            case STATE_PAUSE: /* ------------------------------------- PAUSE */
                if ( EVENT_CONTINUE == event_time.event ){
                    
                    /* pause duration is added to the offset */
                    dev->time.offset += (get_jiffies_64() -
                                         dev->time.enter_pause);
                    dev->time.enter_pause = TIME_DEFAULT;
                    new_state = STATE_RUNNING;
                    PDEBUG("PAUSE: %s continues: offset,enter_pause changed\n",
                           dev->name);
                } else {
                    PDEBUG("PAUSE: nothing to do!\n");
                }
                break;
            default     :
                printk(KERN_ALERT "update_state: unknown state\n");
            }
        }
        
        dev->state = new_state;
}

/* ------------------------------------------------------------ timer_write */
ssize_t 
timer_write(struct file *filp,
            const char __user *buff,
            size_t count,
            loff_t *f_pos)
{

    ssize_t res = EXIT_SUCCESS; /* return check var */
    struct timer_dev *dev = filp->private_data;  /* info data */
    char *cmdstr = NULL;   /* local kernel buff pointer */
    
    PDEBUG("TIMER_WRITE\n");
    down(&dev->sem); /* protect the local dynamic kernel buff */
    cmdstr = kmalloc( NBUFF , GFP_KERNEL);
    if (!cmdstr){
        PDEBUG("kmalloc for cmdstr failed\n");
        return -ENOMEM;
    }
    
    memset(cmdstr, '\0', NBUFF); /* set everything to NULL */
    
    res = copy_from_user(cmdstr, buff, count); /* get infos from user */
    res = count - res;  
    /* if res <  count : not all bytes where copied
                         -> calling write again 
       if res == count : write was successful */
    if(res != count){
        PDEBUG("copy_from_user failed: so many chars are lost:%d\n", res);
        kfree(cmdstr);
        return -EIO;
    } 
    
    update_state(dev, cmdstr);
    
    dev_dump(dev);
    kfree(cmdstr);
    up(&dev->sem);
    
    return res;
}
/* ********************************************************* module_THINGIS */
module_init(timer_init);
module_exit(timer_cleanup);
