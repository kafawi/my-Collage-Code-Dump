/* Description: Memory Manager BSP3*/
/* Prof. Dr. Wolfgang Fohl, HAW Hamburg */
/* Winter 2016
 *
 * This is the memory manager process that
 * works together with the vmaccess process to
 * mimic virtual memory management.
 *
 * The memory manager process will be invoked
 * via a SIGUSR1 signal. It maintains the page table
 * and provides the data pages in shared memory
 *
 * This process is initiating the shared memory, so
 * it has to be started prior to the vmaccess process
 *
 * TODO:
 * getopt, allocate_page, fetch_page, store_page, update_pt, find_remove_fifo
 * clock, lru, search_freeframe,
 * */

#include "mmanage.h"

struct vmem_struct *vmem = NULL;
FILE *pagefile = NULL;
FILE *logfile = NULL;
int signal_number = 0;          /* Received signal */
int vmem_algo = VMEM_ALGO_FIFO;
int shm_id;

/** local prototypes */
void setalgo(int argc, char **argv);

/** func pointer for the find_remove_algo */
int (*find_remove_frame) (void) = NULL;

int
main(int argc, char **argv)
{
    struct sigaction sigact;

    setalgo(argc, argv);

    /* Init pagefile */
    init_pagefile(MMANAGE_PFNAME);
    if(!pagefile) {
        perror("Error creating pagefile");
        exit(EXIT_FAILURE);
    }

    /* Open logfile */
    logfile = fopen(MMANAGE_LOGFNAME, "w");
    if(!logfile) {
        perror("Error creating logfile");
        exit(EXIT_FAILURE);
    }

    /* Create shared memory and init vmem structure */
    vmem_init();
    if(!vmem) {
        perror("Error initialising vmem");
        exit(EXIT_FAILURE);
    }
    else {
        PDEBUG("vmem successfully created\n")
    }

    /* Setup signal handler */
    /* Handler for USR1 */
    sigact.sa_handler = sighandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    if(sigaction(SIGUSR1, &sigact, NULL) == -1) {
        perror("Error installing signal handler for USR1");
        exit(EXIT_FAILURE);
    }
    else {
        PDEBUG("USR1 handler successfully installed\n")
    }

    if(sigaction(SIGUSR2, &sigact, NULL) == -1) {
        perror("Error installing signal handler for USR2");
        exit(EXIT_FAILURE);
    }
    else {
        PDEBUG("USR2 handler successfully installed\n");
    }

    if(sigaction(SIGINT, &sigact, NULL) == -1) {
        perror("Error installing signal handler for INT");
        exit(EXIT_FAILURE);
    }
    else {
        PDEBUG("INT handler successfully installed\n");
    }

    /* Signal processing loop */
    while(1) {
        signal_number = 0;
        pause();
        if(signal_number == SIGUSR1) {  /* Page fault */
            PDEBUG("Processed SIGUSR1\n");
            signal_number = 0;
        }
        else if(signal_number == SIGUSR2) {     /* PT dump */
            PDEBUG("Processed SIGUSR2\n");
            signal_number = 0;
        }
        else if(signal_number == SIGINT) {
            PDEBUG("Processed SIGINT\n");
        }
    }

    return 0;
}

/* *************************************************************************/
/* Your code goes here... */
/* --------------------------------------------------------- init_pagefile */
void
init_pagefile(const char *pfname)
{
    /* create a new file (w), for RW (+) */
    int tmp_rand = INVALID_RAND_NUM;
    int i = VOID_IDX;
    pagefile = fopen(pfname, "w+");
    if(!pagefile) {
        perror("Error creating pagefile");
        exit(EXIT_FAILURE);
    }
    /* fill pagefile */
    srand(SEED_PF);
    for(i = 0; VMEM_VIRTMEMSIZE > i; i++) {
        tmp_rand = rand();
        fprintf(pagefile, PF_NUMFMT, tmp_rand);
        if(0 == ((i + 1) % VMEM_PAGESIZE)) {
            fprintf(pagefile, PF_PAGEDLM);
        }
        else {
            fprintf(pagefile, PF_NUMDLM);
        }

    }
    fflush(pagefile);
    return;
}
/* ------------------------------------------------------------- vmem_init */
void
vmem_init()
{
    int res = EXIT_FAILURE;
    int i = VOID_IDX;           /* iteration var */
    int clear_flags = 0;        /* nothing set */
    PDEBUG("vmem_init enterd\n");

    key_t shmkey = (key_t) * SHMNAME;
    if((key_t) - 1 == shmkey) {
        perror("ERROR creating shmkey with ftok failed");
        exit(EXIT_FAILURE);
    }
    PDEBUG("shmkey:%d\n", (int) shmkey);

    shm_id = shmget(shmkey, SHMSIZE, IPC_CREAT | SHMPERM);
    if(shm_id == EXIT_FAILURE) {
        perror("Error creating shared memory failed");
        exit(EXIT_FAILURE);
    }
    PDEBUG("shm created\n");

    vmem = (struct vmem_struct *) shmat(shm_id, NULL, 0);
    if(vmem == (void *) EXIT_FAILURE) {
        perror("Error allocating vmem in shm");
        cleanup();
        exit(EXIT_FAILURE);
    }
    PDEBUG("vmem struct in allocated\n");

    /* INIT */
    /* vmem->adm */
    PDEBUG("vmem->adm init start\n");
    vmem->adm.size = VMEM_VIRTMEMSIZE;  /* WHY? */
    vmem->adm.mmanage_pid = getpid();   /* getpid is always successful */

    res = sem_init(&(vmem->adm.sema), 1, 0);
    if(res == EXIT_FAILURE) {
        perror("Error init semaphor failed");
        cleanup();
        exit(EXIT_FAILURE);
    }
    PDEBUG("semaphor allocated\n");

    vmem->adm.size = VMEM_VIRTMEMSIZE;  /* i dont know why */
    vmem->adm.mmanage_pid = getpid();   /* getpid is always successful */
    vmem->adm.req_pageno = VOID_IDX;    /* Number of requested pages */
    vmem->adm.last_alloc_idx = VOID_IDX;        /* Next frame_index to
                                                   allocate */
    vmem->adm.pf_count = 0;     /* Page fault count */
    vmem->adm.g_count = 0;      /* Glob. access counter (timestep) */

    /* vmem->pt */
    /* vmem->pt.entries */
    PDEBUG("vmem->pt.entries init start\n");
    for(i = 0; i < VMEM_NPAGES; i++) {
        /* clear flags */
        vmem->pt.entries[i].flags = clear_flags;        /* clear all
                                                           flags */
        vmem->pt.entries[i].frame = VOID_IDX;   /* frame address */
        vmem->pt.entries[i].count = 0;  /* quasi-timestep for LRU */
    }

    /* vmem-pt.framepages */
    PDEBUG("vmem->pt.frampages init start\n");
    for(i = 0; i < VMEM_NFRAMES; i++) {
        vmem->pt.framepage[i] = VOID_IDX;       /* pages on frame */
    }

    PDEBUG("vmem init end\n");
}
/* -------------------------------------------------- sighandler */
void
sighandler(int signo)
{
    int res = EXIT_FAILURE;

    PDEBUG("MMANAGE: Enter signalhandler with ");
    switch (signo) {
    case SIGUSR1:      /* page fault */
        PDEBUG("SIGUSR1 - page fault\n");
        allocate_page();
        res = sem_post(&(vmem->adm.sema));
        if(res == EXIT_FAILURE) {
            perror("Error sem_post failed: terminate!");
            cleanup();
            exit(EXIT_FAILURE);
        }
        break;
    case SIGUSR2:      /* dump_pt */
        PDEBUG("SIGUSR2 - dump_pt\n");
        dump_pt();
        break;
    case SIGINT:       /* termination */
        PDEBUG("SIGINT - exit program\n");
        cleanup();
        exit(EXIT_SUCCESS);
    default:   /* every other signal -> termination */
        PDEBUG("NOT IN SCOPE - signal SIGINT\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
    PDEBUG("MMANAGE:Exit sighandler\n");
}
/* ************************************************************** */
/** ----------------------------------------------- allocate_page */
void
allocate_page()
{
    PDEBUG("MMANAGE: ENTER allocate_page\n");
    int alloc_frame = VOID_IDX;
    int old_page_idx = VOID_IDX;
    int page_dirty_flag = 0;
    struct logevent le;

    /* check is there any free frame */
    alloc_frame = search_freeframe();
    /* find to remove page, find_remove_frame() */
    if(VOID_IDX == alloc_frame) {
        alloc_frame = find_remove_frame();
    }
    /* save alloc_idx into last_alloc_idx for later use in ec
       fetsh_page */
    vmem->adm.last_alloc_idx = alloc_frame;
    /* get next page_idx */
    old_page_idx = vmem->pt.framepage[alloc_frame];

    /* Dirtybit checkt, should page be stored back? */
    page_dirty_flag = vmem->pt.entries[old_page_idx].flags & PTF_DIRTY;
    if(VOID_IDX != old_page_idx && PTF_DIRTY == page_dirty_flag) {
        store_page(old_page_idx);
    }

    /* Write requested page to */
    fetch_page(vmem->adm.req_pageno);
    update_pt(alloc_frame);
    /* Write the alloc_frame back in Memory */

    /* logger event init */
    le.req_pageno = vmem->adm.req_pageno;
    le.replaced_page = old_page_idx;
    le.alloc_frame = alloc_frame;
    le.pf_count = vmem->adm.pf_count;
    le.g_count = vmem->adm.g_count;

    logger(le);
    PDEBUG("MMANAGE: Exit allocate_page\n");
}

/* ------------------------------------------------------- search_freeframe */
int
search_freeframe()
{
    int freeframe = VOID_IDX;
    int i = 0;

    for(i = 0; VMEM_NFRAMES > i; i++) {
        if(VOID_IDX == vmem->pt.framepage[i]) {
            freeframe = i;
            break;
        }
    }
    return freeframe;
}

/** ############################################ PAGE REPLACEMENT ALGORITHM */
/** ------------------------------------------------------ find_remove_fifo */
int
find_remove_fifo()
{
    int frame = (vmem->adm.last_alloc_idx + 1) % VMEM_NFRAMES;
    return frame;
}

/** ----------------------------------------------------- find_remove_clock */
int
find_remove_clock()
{
    int clock = (vmem->adm.last_alloc_idx + 1) % VMEM_NFRAMES;
    int page = vmem->pt.framepage[clock];
    int is_used = vmem->pt.entries[page].flags & PTF_USED;

    while(PTF_USED == is_used) {
        /* set to unused */
        vmem->pt.entries[page].flags &= ~(PTF_USED);

        /* push clock one up -> next frame */
        clock = (clock + 1) % VMEM_NFRAMES;
        /* -> next page */
        page = vmem->pt.framepage[clock];
        /* calc the used flag for this page */
        is_used = vmem->pt.entries[page].flags & PTF_USED;
    }
    return clock;
}

/** ------------------------------------------------------- find_remove_lru */
int
find_remove_lru()
{
    int frame = VOID_IDX;
    int age = -1;
    int oldest = age;
    int lru_frame = frame;
    int page = VOID_IDX;

    int i = VOID_IDX;
    for(i = 0; VMEM_NFRAMES > i; i++) {
        frame = (vmem->adm.last_alloc_idx + i) % VMEM_NFRAMES;
        page = vmem->pt.framepage[frame];
        age = vmem->pt.entries[page].count;
        if(oldest < age) {
            lru_frame = frame;
            oldest = age;
        }
    }
    return lru_frame;
}

/** ------------------------------------------------------------ fetch_page */
void
fetch_page(int pt_idx)
{
    int i = VOID_IDX;           /* iteration var */
    int datum = -1;
    /* address where fetched page is going to stored */
    int frame_adr = vmem->adm.last_alloc_idx * VMEM_PAGESIZE;
    /* get position in pagefile.bin from BOF to Line number pt_idx */
    fseek(pagefile, pt_idx * PF_PAGESIZE, SEEK_SET);

    /* write whole frame */
    for(i = 0; VMEM_PAGESIZE > i; i++) {
        fscanf(pagefile, PF_NUMFMT, &datum);

        fseek(pagefile, PF_DLMSIZE, SEEK_CUR);
        vmem->data[i + frame_adr] = datum;
    }
    fflush(pagefile);
    return;
}

/** ------------------------------------------------------------ store_page */
void
store_page(int pt_idx)
{
    int i = VOID_IDX;

    /* STARTIng ADR from frame that is going to written to pagefile */
    int frame = vmem->pt.entries[pt_idx].frame;
    /* jump to replace pageentrie */
    fseek(pagefile, pt_idx * PF_PAGESIZE, SEEK_SET);

    /* REPLACE LOOP */
    for(i = 0; VMEM_PAGESIZE > i; i++) {
        fprintf(pagefile, PF_NUMFMT, vmem->data[i + frame]);
        fseek(pagefile, PF_DLMSIZE, SEEK_CUR);
    }
    fflush(pagefile);
    return;
}

/** ------------------------------------------------------------- update_pt */
void
update_pt(int frame)
{
    int old_page = vmem->pt.framepage[frame];
    int new_page = vmem->adm.req_pageno;
    /* Clear old entry if it exists */
    if(VOID_IDX != old_page) {
        vmem->pt.entries[old_page].frame = VOID_IDX;
        vmem->pt.entries[old_page].flags = 0;
    }

    /* SET NEW ENTRIES */
    vmem->pt.entries[new_page].frame = frame * VMEM_PAGESIZE;/*phy_frame_adr*/
    vmem->pt.entries[new_page].flags |= PTF_PRESENT;    /* PTF_USED is
                                                           set by
                                                           vmaccess */
    vmem->pt.framepage[frame] = new_page;       /* set a link from
                                                   frame to new page */
    return;
}

/** --------------------------------------------------------------- cleanup */
void
cleanup()
{
    int res = EXIT_FAILURE;
    /* Close files */
    res = fclose(pagefile);
    if(EOF == res) {
        perror("Error: fclose pagefile failed!\n");
    };
    res = fclose(logfile);
    if(EOF == res) {
        perror("Error: fclose logfile failed!\n");
    }
    res = sem_destroy(&(vmem->adm.sema));
    if(EXIT_FAILURE == res) {
        perror("Error: sem_destroy failed!\n");
    }
    res = shmdt((void *) vmem);
    if(EXIT_FAILURE == res) {
        perror("Error: shmdt failed!\n");
    }
    res = shmctl(shm_id, IPC_RMID, 0);
    if(EXIT_FAILURE == res) {
        perror("Error: shmctl failed!\n");
    }
}

/** ---------------------------------------------------------------- logger */
/* Do not change!  */
void
logger(struct logevent le)
{
    fprintf(logfile, "Page fault: %10d, Global count: %10d, "
            "Removed:    %10d, Allocated:    %10d, Frame: %10d\n",
            le.pf_count, le.g_count,
            le.replaced_page, le.req_pageno, le.alloc_frame);
    fflush(logfile);
}

/** --------------------------------------------------------------- dump_pt */
void
dump_pt()
{
    int i = VOID_IDX;
    puts("\nDUMP PAGE TABLE --------------------------------------------\n");
    puts("PAGE : FLAGS : FRAMES : COUNT\n");
    for(i = 0; i < VMEM_NPAGES; i++) {
        printf("%4d : %5d : %6d : %5d\n",
               i,
               vmem->pt.entries[i].flags,
               vmem->pt.entries[i].frame, vmem->pt.entries[i].count);
    }
    puts("\n frame page \n");
    for(i = 0; i < VMEM_NFRAMES; i++) {
        printf("%d::%d - ", i, vmem->pt.framepage[i]);
    }
    puts("\n-----------------------------------------------------the end\n");

}

/** ---------------------------------------------------------------- usage */
void
usage()
{
    printf("Usage: mmanage [OPTION]        \n\
           Options:                        \n\
            -c | --clock: clock algorithm  \n\
            -f | --fifo:  fifo algorithm   \n\
            -l | --lru:   lru algorithm    \n");
    exit(EXIT_FAILURE);

}

/** --------------------------------------------------------------- setalgo */
void
setalgo(int argc, char **argv)
{
    int optset_flag = FALSE;

    int option_index = 0;
    char *short_options = "clfh";
    struct option long_options[] = {
        {"clock", no_argument, 0, 'c'},
        {"fifo", no_argument, 0, 'f'},
        {"lru", no_argument, 0, 'l'},
        {"help", no_argument, 0, 'h'}
    };
    int option = getopt_long(argc,
                             argv,
                             short_options,
                             long_options,
                             &option_index);

    while(-1 != option) {
        switch (option) {
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
        case 'f':
            if(optset_flag) {
                printf("To many arguments\n");
                usage();
                exit(EXIT_FAILURE);
            }
            else {
                optset_flag = TRUE;
                vmem_algo = VMEM_ALGO_FIFO;
            }
            break;
        case 'c':
            if(optset_flag) {
                printf("To many arguments\n");
                usage();
                exit(EXIT_FAILURE);
            }
            else {
                optset_flag = TRUE;
                vmem_algo = VMEM_ALGO_CLOCK;
            }
            break;
        case 'l':
            if(optset_flag) {
                printf("To many arguments\n");
                usage();
                exit(EXIT_FAILURE);
            }
            else {
                optset_flag = TRUE;
                vmem_algo = VMEM_ALGO_LRU;

            }
            break;
        default:
            printf("Inavalid argument!\n");
            usage();
            exit(EXIT_FAILURE);
        }
        option = getopt_long(argc,
                             argv,
                             short_options,
                             long_options, &option_index);
    }

    switch (vmem_algo) {
    case VMEM_ALGO_FIFO:
        find_remove_frame = find_remove_fifo;
        printf("Set fifo as algorithm\n");
        break;
    case VMEM_ALGO_CLOCK:
        find_remove_frame = find_remove_clock;
        printf("Set clock as algorithm\n");
        break;
    case VMEM_ALGO_LRU:
        find_remove_frame = find_remove_lru;
        printf("Set lru as algorithm\n");
        break;
    }
}
