/* Header file for vmappl.c
 * File: vmaccess.h
 * Prof. Dr. Wolfgang Fohl, HAW Hamburg
 * Winter 2016
 */

#ifndef VMACCESS_H
#define VMACCESS_H
#include "vmem.h"

/** Connect to shared memory (key from vmem.h) */
void vm_init(void);

/** Read from "virtual" address */
int vmem_read(int address);

/** Write data to "virtual" address */
void vmem_write(int address, int data);

#endif
