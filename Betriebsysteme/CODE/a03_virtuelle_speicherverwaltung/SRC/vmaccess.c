/*
*vmaccess - access functions to virtual memory
*/

#include "vmaccess.h"   /* virtual memory access header */

/* Static variables*/

struct vmem_struct *vmem = NULL;        /* reference to virtual memory */

/* prototypes */
void algo_pt_update(int modified_page);

/**
* vmem_init
* this function is initiating the connection to virtual memory
* virtual memory must be created by mmanage.c
*/
/** --------------------------------------------------------------- vm_init */
void
vm_init(void)
{
    PDEBUG("VMAPPL: Enter vm_init\n");

    key_t shmkey = (key_t) * SHMNAME;
    PDEBUG("shmkey:%d\n", (int) shmkey);

    int shmid = shmget(shmkey, SHMSIZE, SHMPERM);       /* without
                                                           ipc_creat */
    if(shmid == -1) {
        printf("error knowing shared memory failed\n");
        exit(EXIT_FAILURE);
    }

    vmem = (struct vmem_struct *) shmat(shmid, NULL, 0);
    if((void *) EXIT_FAILURE == vmem) {
        printf("error attaching shared memory\n");
    }
    PDEBUG("vmem struct attatched\n");

    /* 
     *assigning shmemdata to vmem
     */
    PDEBUG("VMAPPL: Exit vm_init\n");
}
/* ------------------------------------------------------------- vmem_read */
int
vmem_read(int address)
{
    PDEBUG("VMACCESS: Enter vmem_read\n");
    if(vmem == NULL) {
        vm_init();
        PDEBUG("vmem init end \n");
    }
    int offset = address % VMEM_PAGESIZE;
    int page = address / VMEM_PAGESIZE;
    int phy_address = -1;
    int data = -1;

    // teste auf PTF_PRESENT
    if(PTF_PRESENT != (vmem->pt.entries[page].flags & PTF_PRESENT)) {
        vmem->adm.pf_count++;
        vmem->adm.req_pageno = page;
        kill(vmem->adm.mmanage_pid, SIGUSR1);
        sem_wait(&(vmem->adm.sema));
    }

    /* Frame now in memory -> read data */
    phy_address = vmem->pt.entries[page].frame + offset;
    data = vmem->data[phy_address];

    algo_pt_update(page);
    vmem->adm.g_count++;

    PDEBUG("VMACCESS:Exit vmem_read\n");
    return data;
}
/* ----------------------------------------------------------- vmem_write */
void
vmem_write(int address, int data)
{
    PDEBUG("VMACCESS: Enter vmem_write\n");
    if(vmem == NULL) {
        vm_init();
        PDEBUG("vmem init end \n");
    }
    int offset = address % VMEM_PAGESIZE;
    int page = address / VMEM_PAGESIZE;
    int phy_address = -1;

    // teste auf PTF_PRESENT
    if(PTF_PRESENT != (vmem->pt.entries[page].flags & PTF_PRESENT)) {
        vmem->adm.pf_count++;
        vmem->adm.req_pageno = page;
        // kill(vmem->adm.mmanage_pid, SIGUSR2);
        kill(vmem->adm.mmanage_pid, SIGUSR1);
        sem_wait(&(vmem->adm.sema));
        // kill(vmem->adm.mmanage_pid,SIGUSR2);
    }

    /* frame in memory -> write data */
    phy_address = vmem->pt.entries[page].frame + offset;
    vmem->data[phy_address] = data;
    vmem->pt.entries[page].flags |= PTF_DIRTY;

    algo_pt_update(page);
    vmem->adm.g_count++;

    PDEBUG("VMACCESS:Exit vmem_write\n");
}

/** update pt for page replacement algorithms */
void
algo_pt_update(int modified_page)
{
    int i = -1;
    int iter_page = -1;
    /* CLOCK */
    vmem->pt.entries[modified_page].flags |= PTF_USED;

    /* LRU */
    /* let all active pages get a bit older */
    for(i = 0; VMEM_NFRAMES > i; i++) {
        iter_page = vmem->pt.framepage[i];
        vmem->pt.entries[iter_page].count += 1;
    }
    /* reset the count of last used page */
    vmem->pt.entries[modified_page].count = 0;
}
