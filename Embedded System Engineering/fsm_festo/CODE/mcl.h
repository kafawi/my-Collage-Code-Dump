/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/**
 * @file mcl.h
 * @brief Singelton to control the connection between layers and initialization
 *
 * The instance will create and hold all channel inside the MCL,
 * And also gets pointer from HAL, SIO, HDI to connect with it.
 * Also the main Thread of Mcl is stored and all
 * main instances be here inizialed and also holds the destroy control of them.
 *
 * Pattern Singelton;
 *
 * @author kafa
 *
 * Created on 2017 06 08
 */

#ifndef _MCL_H
#define _MCL_H

#include "channel.h"
#include "mclDispatcher.h"
#include "Data.h"
class Thread;
class Mutex;
class Worker;

class Mcl{
 public:
  /**
   * Gets instance of the Mcl owner
   */
  static Mcl *getInstance();
  /**
   * get the Actor Channel, which stores commands for the Actors
   * @return
   *   pointer of Actor Channel
   */
  PulseChannel *getChSerialIn();
  /**
   * get the Serial Channel, 
   *   to communicate -> Serial Layer -> the neighbor system
   * @return
   *   poiter to the serial chanel
   */
  PulseChannel *getChSerialOut();
  /**
   * get the Actor Channel, which stores commands for the Actors
   * @return
   *   pointer of Actor Channel
   */
  PulseChannel *getChMasterControlIn();
  
  /**
   * get the digital Actor channel,
   * to command HAL
   * @return
   *   pointer of digital Sensor channel
   */
  PulseChannel *getChActorOut();
  
  /**
   * get the analog Sensor channel,
   * the profile measurement will write its samples on it
   */
  PulseChannel *getChAnalogSensorIn();
  /**
   * get Data
   * @param ch
   */
  Data *getData();
  /**
   * set the digital actor channel
   * @param ch
   *   pointer to the digital actor channel
   */
  void setChActorOut(PulseChannel *ch);
  /**
   * set the serial out channel
   * @param ch
   *   pointer to the digital actor channel
   */
  void setChSerialOut(PulseChannel *ch);
  
  PulseChannel *getChHidIn();
  PulseChannel *getChHidOut();
  void setChHidOut(PulseChannel *ch);
  
  /**
   * Initialization of all Components in Hal
   */
  void init(bool isReceivingEnd); // needs a flag to init as first or second
  /**
   * Destruction of all Components in Hal
   */
  void destroy();
  /**
   * Destructor
   */
  ~Mcl();

 private:
 // TODO all Channel but for first, just to HAL (without )
  PulseChannel chMasterControlIn_;  /**< digital sensor channel for interrupts */
  PulseChannel chAnalogSensorIn_;   /**< analog sensor channel for profile sampling */
  PulseChannel *chActorOut_;        /**< Actor channel for commands to HAL */
  PulseChannel chSerialIn_;         /**< */ 
  PulseChannel *chSerialOut_;       /**< */
  PulseChannel chHidIn_;
  PulseChannel *chHidOut_;
  Thread  *mclTh_;                    /**< main Mcl thread ()*/
  Worker  *worker_;
  MclDispatcher *disp_;               /**< main Object, that runns the thread */ 
  static Mutex initMtx_;              /**< for instance_ access security */
  static Mcl *instance_;              /**< pointer to the only instance */
  Data *data_;
  Mcl();                              /**< private Constructor (Singleton)  */
};
#endif /** _MCL_H */
