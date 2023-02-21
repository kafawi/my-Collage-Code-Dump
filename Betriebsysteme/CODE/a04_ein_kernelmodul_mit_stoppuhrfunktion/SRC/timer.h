/**
 * Timer module header
 *
 * 
 * table of content
 * - INCLUDES
 * - STD_DEFINES
 * - DEBUG
 * - INIT STUFF
 * - FSM STUFF
 * - COMMAND CHARS
 * - 
 * - PROTOTYPES
 * - MODULE STUFF
*/
#ifndef _TIMER_H_
#define _TIMER_H_

/* *************************************************************** INCLUDES */
#include <linux/module.h> 
#include <linux/init.h>
/* #include <linux/moduleparam.h> */

#include <linux/kernel.h>  /* printk() */
#include <linux/slab.h>    /* kfree kmalloc */
#include <linux/fs.h>
#include <linux/errno.h>   /* error codes */
#include <linux/types.h>   /* size_t */
#include <linux/cdev.h> 
#include <asm/uaccess.h>   /* copy_to/from_user */

#include <linux/string.h>  /* string functions  */
#include <linux/jiffies.h> /* 250 Hz and u64 */

/* *********************************************************** MODULE STUFF */
MODULE_LICENSE("Dual BSD/GPL");
/* DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE */
/* **************************************************************** DEFINES */
/* -------------------------------------------------------------------- std */
#define FALSE 0
#define TRUE  !FALSE

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
/* --------------------------------------------------------------- defaults */
#define TIME_DEFAULT 0
/* ------------------------------------------------ names and Minor / Major */
#define TIMER_NAME     "timer"
#define NDEVS          2
#define TIMERF_NAME    "timerf"
#define TIMERF_MINOR   0
#define TIMERR_NAME    "timerr"
#define TIMERR_MINOR   1
#define TIMER_NAME_LEN 6
/* ----------------------------------------------------------------- output */
#define NBUFF      36
#define TIMERF_MSG TIMERF_NAME" t:%20llu +++++\n"
#define TIMERR_MSG TIMERR_NAME" t:%20llu -----\n"
#define U64_FMT   "%llu"
/* ----------------------------------------------------- command characters */
#define CMD_CHAR_START    's'
#define CMD_CHAR_PAUSE    'p'
#define CMD_CHAR_CONTINUE 'c'
#define CMD_CHAR_RESET    'r'
#define CMD_CHAR_LOAD     'l'
#define CMD_NR             5

/* ***************************************************************** MACROS */

/* ------------------------------------------------------------------ DEBUG */
/* ----------------------------------------------------------------- PDEBUG */
#ifdef DEBUG_MESSAGES
#   ifdef __KERNEL__
#       define PDEBUG(fmt, args...) \
            printk( KERN_DEBUG "timer: " fmt, ## args)
#   else
#       define PDEBUG(fmt, args...) \
            fprintf(stderr, "timer: " fmt, ## args)
#   endif
#else
#   define PDEBUG(fmt, args...)
#endif
/* ************************************************************** FSM STUFF */
/* ------------------------------------------------------------------ enums */
#define STATE_NR 4
enum state {
    STATE_READY = 0,
    STATE_RUNNING,
    STATE_PAUSE,
    STATE_LOADED
};
#define EVENT_NR 6
enum event {
    EVENT_START = 0,
    EVENT_PAUSE,
    EVENT_CONTINUE,
    EVENT_RESET,
    EVENT_LOAD,
    EVENT_UNKNOWN
};
/* ----------------------------------------------- fsm return for get_event */
struct event_time{
    enum event event;
    u64 time;
};
/* ********************************************************** DEVICE STRUCT */
/* ------------------------------------------------------------------- time */
struct time {
    u64 offset;
    u64 enter_pause;
    u64 load;
};
/* -------------------------------------------------------------- timer_dev */
struct timer_dev {
    int minor;                                 /* identificarion number */
    char name[TIMER_NAME_LEN];                 /* name of device */
    
     /* state vars  */
    struct time time;                         
    enum state state;
    
    /*OTHER STUFF for the */
    struct semaphore sem;     /* mutex: protect local dynamic kernel buff*/
    struct cdev cdev;         /* char driver stuff */
};
/* ****************************************************** MODULE PROTOTYPES */
static int __init timer_init(void);
static void timer_cleanup(void);

int timer_open(struct inode *inode, struct file *filp);

int timer_release(struct inode *inode, struct file *filp);

ssize_t timer_read(struct file *filp,
                   char __user *buff,
                   size_t count,
                   loff_t *f_pos);
ssize_t timer_write(struct file *filp,
                    const char __user *buff,
                    size_t count,
                    loff_t *f_pos);
/* ******************************************************************** END */
#endif /* _TIMER_H_ */
