/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/* 
 * File:   newfile.h
 * Author: kafa
 *
 * Created on May 22, 2017, 3:48 AM
 */

#ifndef _PULSE_H
#define _PULSE_H
/**
 * @struct Datatype to hold the pulse Message in a OS independent condition
 */
typedef struct Pulse{
  int8_t code;     /**< mostly source of event */
  union{
    int32_t i;
    void * p;
  } value;
  //int32_t value;   /**< type or kind of event  */
}Pulse_t;



#endif /* _PULSE_H */

