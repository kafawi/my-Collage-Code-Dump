/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sio.h
 * Author: kafa
 *
 * Created on June 13, 2017, 6:50 PM
 */

#ifndef SIO_H
#define SIO_H

#include "channel.h"
class SerialDispatcher;
class Thread;
class Mutex;
class Worker;

class Sio
{
 public:
  /**
   * Gets instance of the Sio owner
   */
  static Sio *getInstance();
  /**
   * Initialization of all Components in Serial
   */
  void init();
  /**
   * Destruction of all Components in Serial
   */
  void destroy();
  /**
   * Destructor
   */
  virtual ~Sio();
  
  // getter setter
  PulseChannel *getChCmdIn();
  
  PulseChannel *getChEventOut();
  
  void setChEventOut(PulseChannel *ch);
 private:
  PulseChannel chCmdIn_;
  PulseChannel *chEventOut_;
  SerialDispatcher *disp_;
  Thread *sioTh_;
  Worker *worker_;
  static Mutex initMtx_;              /**< for instance_ access security */
  static Sio *instance_;              /**< pointer to the only instance */
  Sio();                              /**< private Constructor (Singleton)  */
};

#endif /* SIO_H */

