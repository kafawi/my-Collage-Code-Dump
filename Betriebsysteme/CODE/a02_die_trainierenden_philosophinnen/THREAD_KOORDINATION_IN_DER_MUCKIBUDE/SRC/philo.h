/**
 * @file    philo.h
 * @author  bibut and kafawi
 * @version V0.7
 * @date    14.11.2016
 * @brief   Interface / Header for the thread functions in philo.c
 */

#ifndef __PHILO_H
#define __PHILO_H
/* ---------------------------------------------------------------- Includes */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "parameter.h"

/* -------------------------------------------------------- Exported typedef */
/**
 * State of the current accepted command the thread is in.
 */
typedef enum {
    QUIT=20,
    BLOCKED,
    NORMAL
} Cmd_state_t;

/**
 * State of the current activity the thread is in.
 */
typedef enum {
    GET_WEIGHTS=10,
    WORKOUT,
    PUT_WEIGHTS,
    REST
} Train_state_t;

/**
 * Struct to store data and thread objects for synchronisation
 */
typedef struct {
    sem_t block_sem;  // change name for a better understanding
    Cmd_state_t cmd_state;
    Train_state_t train_state;
    int tid;
} Philo_t;


/**
 * Thread function to start the philo threads
 * @param ptr_tid pointer to an Integer where the thread number is stored
 * @return every time the null pointer (NULL)
 */
void * philothread (void * ptr_tid);

/**
 * Getter for cmd_state
 * @param tid thread number to identify the thread
 * @return the current command state
 */
Cmd_state_t get_cmd_state(int tid);

/**
 * Getter for train_state
 * @param tid thread number to identify the thread 
 * @return the current train state
 */
Train_state_t get_train_state(int tid);

/**
 * Setter train_state
 * @param train_state train state the philo thread changes to
 * @param tid thread number to identify the thread
 */
void set_train_status(Train_state_t train_state, int tid);

/**
 * Initialize the synchronisations Objects like the semaphore and the structs
 *
 */
void init_philo_obj(void);

/**
 *
 *
 */
void free_philo_obj(void);

/**
 *
 *
 */
void unblock_philo(int tid);
/* --------------------------------------------------------- global Variable */
extern char cmd_arr[];
#endif /* __PHILO_H */
