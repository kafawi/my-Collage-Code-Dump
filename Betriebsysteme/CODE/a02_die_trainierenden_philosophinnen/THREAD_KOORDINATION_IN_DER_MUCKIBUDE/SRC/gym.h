/**
 * @file    gym.h
 * @author  bibut and kafawi
 * @version V0.7
 * @date    05.11.2016
 * @brief   Interface / Header for the monitor gym.c
 */

#ifndef __GYM_H
#define __GYM_H
/* ---------------------------------------------------------------- Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "parameter.h"

/* -------------------------------------------------------- Exported typedef */


/* --------------------------------------------------------- Exported define */
// BUFFSIZES for print and string manipulation

#define FORMAT_WEIGHT "%1d"
#define NWEIGHT_BUFF 1 + 4

#define NWEIGHTS_BUFF NWEIGHTS_T * ( NWEIGHT_BUFF - 1 )

#define FORMAT_SUPPLY    "  Supply[%s]\n" // size 13
#define FORMAT_STATUS "%1d(%1d)%c:%c:[%s] " // size 12 without %s
#define NSTATUS_BUFF  NWEIGHTS_BUFF + 12 
#define NSUPPLY_BUFF  NWEIGHTS_BUFF + 13 
//
#define NOUTPUT_BUFF NSTATUS_BUFF * NPHILO + 13 + NWEIGHTS_BUFF


/* ---------------------------------------------------------- Exported types */


/* ----------------------------------------------------- Exported constrants */


/* ---------------------------------------------------------- Exported macro */
/* ------------------------------------------------------ Exported functions */


/**
 * initial the synchronisations objects for the monitor:
 * condition variable and mutex 
 */
int init_gym_obj( void );


/**
 * terminate_functions
 */
int free_gym_obj( void );

/**
 * free the trapped threads which are waiting on the condition variable.
 */
void free_gym_threads( void );

/**
 * Monitor functions where the philo thread gets a calculated amount of 
 * different weighttypes. If not getting the requierd amount, he is blocked 
 * with an pthread condition variable on the monitors mutex. 
 * @param tid identification number / index for a philo thread
 * @return EXIT_SUCCESS
 */
int get_weights( int tid );

/**
 * Monitor function where the philo tread puts the weights back in the stock.
 * @param tid identification number / index for a philo thread
 * @return EXIT_SUCCESS
 *
 */
int put_weights( int tid );

/**
 * Puts the status of the threads and the weights locations to stdout.
 * @return EXIT_SUCCESS
 */
int display_status( void );


#endif /* __GYM_H */
