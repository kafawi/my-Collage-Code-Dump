/**
 * @file    global.h
 * @author  bibut and kafawi
 * @version V0.1
 * @date    05.11.2016
 * @brief   Defines of some constants
 */

#ifndef __GLOBAL_H
#define __GLOBAL_H
/* ---------------------------------------------------------------- Includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
/* -------------------------------------------------------- Exported typedef */


/* --------------------------------------------------------- Exported define */
#define FALSE  0
#define TRUE   !FALSE

/* ---------------------------------------------------------- Exported types */


/* ----------------------------------------------------- Exported constrants */


/* ---------------------------------------------------------- Exported macro */
#define PRINT_POSITION(line, file, func) printf( \
        "Line %d : File %s : function %s \n",\
        line,      file,     func )
/* ------------------------------------------------------ Exported functions */
/**
 * If an error happen, print some infos and abort / exit the process.
 * @param result
 * @param errnum
 * @param *mssge
 */
void handle_error(
    int result, int errnum, char const *mssge
);

#endif /* __GLOBAL_H */
