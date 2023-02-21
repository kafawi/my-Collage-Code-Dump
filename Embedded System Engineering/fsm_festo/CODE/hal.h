/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/**
 * @file hal.h
 * @brief Singelton to control the connection between layers and initialization
 *
 * The instance will create and hold all channel inside the HAL,
 * And also gets pointer from MCL to connect with it.
 * Also the main Thread of Hal is stored and all
 * main instances be here inizialed and also holds the destroy control of them.
 *
 * Pattern Singelton;
 *
 * @author kafa
 *
 * Created on May 22, 2017, 1:36 AM
 */

#ifndef _HAL_H
#define _HAL_H

#include "channel.h"

class Thread;
class Mutex;
class Worker;
class HalDispatcher;

class Hal{
 public:
  /**
   * Gets instance of the HAL owner
   */
  static Hal *getInstance();

  /**
   * get the Actor Channel, which stores commands for the Actors
   * @return
   *   pointer of Actor Channel
   */
  PulseChannel *getChActorIn();
  
  /**
   * get the digital Sensor channel,
   * the Interrupts will write on it
   * @return
   *   pointer of digital Sensor channel
   */
  PulseChannel *getChDigitalSensorOut();
  
  /**
   * get the analog Sensor channel,
   * the profile measurement will write its samples on it
   */
  PulseChannel *getChAnalogSensorOut();
  
  /**
   * set the digital Sensor channel
   * @param ch
   *   pointer to the analog Sensor channel
   */
  void setChDigitalSensorOut(PulseChannel *ch);
  
  /**
   * set the digital Sensor channel
   * @param ch
   *   pointer to the analog Sensor channel
   */
  void setChAnalogSensorOut(PulseChannel *ch);

  /**
   * Initialization of all Components in Hal
   */
  void init();

  /**
   * Destruction of all Components in Hal
   */
  void destroy();
  /**
   * Destructor
   */
  ~Hal();

 private:
  PulseChannel chActorIn_;            /**< Actor channel for commands from the MCL */
  PulseChannel *chDigitalSensorOut_;  /**< digital sensor channel for interrupts */
  PulseChannel *chAnalogSensorOut_;   /**< analog sensor channel for profile sampling */
  Worker  *worker_;
  Thread  *halTh_;                    /**< main Hal thread ()*/
  HalDispatcher *disp_;
  static Mutex initMtx_;              /**< for instance_ access security */
  static Hal *instance_;              /**< pointer to the only instance */
  Hal();                              /**< private Constructor (Singleton)  */
};
#endif /** _HAL_H */


