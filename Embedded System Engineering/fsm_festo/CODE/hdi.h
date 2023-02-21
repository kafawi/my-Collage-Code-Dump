/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hid.h
 * Author: kafa
 *
 * Created on June 15, 2017, 2:02 PM
 */

#ifndef HID_H
#define HID_H
#include "channel.h"
class HidDispatcher;
class Thread;
class Worker;

class Hdi
{
 public:
  /**
   * Gets instance of the Sio owner
   */
  static Hdi *getInstance();
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
  virtual ~Hdi();
  // getter setter
  PulseChannel *getChCmdIn();
  PulseChannel *getChEventOut();
  void setChEventOut(PulseChannel *ch);
 private:
  PulseChannel chCmdIn_;
  PulseChannel *chEventOut_;
  HidDispatcher *disp_;
  Thread *hidTh_;
  Worker *worker_;
  static Mutex initMtx_;         /**< for instance_ access security */
  static Hdi *instance_;         /**< pointer to the only instance */
  Hdi();
};
#endif /* HID_H */

