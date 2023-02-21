/** Definitions for virtual memory management model
 * File: mmanage.h
 *
 * Prof. Dr. Wolfgang Fohl, HAW Hamburg
 * Winter 2016
 */
#ifndef MMANAGE_H
#define MMANAGE_H
#include "vmem.h"
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

/** Event struct for logging */
struct logevent {
    int req_pageno;
    int replaced_page;
    int alloc_frame;
    int pf_count;
    int g_count;
};

/** Prototypes */
void usage(void);

void sighandler(int signo);

void vmem_init(void);

void allocate_page(void);

void fetch_page(int pt_idx);

void store_page(int pt_idx);

void update_pt(int frame);

/*int find_remove_frame(void); */ /* become an function pointer */

int find_remove_fifo(void);

int find_remove_clock(void);

int find_remove_lru(void);

int search_freeframe(void);

void init_pagefile(const char *pfname);

void cleanup(void);

void logger(struct logevent le);

void dump_pt(void);

/** Misc */
#define MMANAGE_PFNAME "./pagefile.bin" /**< pagefile name */
#define MMANAGE_LOGFNAME "./LOG/logfile.txt"        /**< logfile name */

#define VMEM_ALGO_FIFO  0
#define VMEM_ALGO_LRU   1
#define VMEM_ALGO_CLOCK 2

#define SEED_PF 070514        /**< Get reproducable pseudo-random numbers for
                           init_pagefile */

#define VOID_IDX -1

/* Edit to modify algo, or remove line and provide
 * -DVMEM_ALGO ... compiler flag*/
/* #define VMEM_ALGO VMEM_ALGO_FIFO */

#define INVALID_RAND_NUM -1     /* rand() goes from 0 to RAND_MAX */

#define PF_NUMFMT   "%10d"     /* CHAR* FORMAT for a num */
#define PF_NUMDLM   ";"        /* Char* format for the num delimiter */   
#define PF_PAGEDLM  "\n"       /* char * format for the page delimiter */
#define PF_NUMSIZE  10         /* size of PF_NUMFMT */
#define PF_DLMSIZE   1         /* size of PF_NUMDLM bzw. PF_PAGEDLM */
#define PF_PAGESIZE (PF_NUMSIZE + PF_DLMSIZE) * VMEM_PAGESIZE /* pagagesize
                                                                 in 
                                                                 pagefile.bin
                                                              */

#endif /* MMANAGE_H */
