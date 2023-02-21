/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialDispatcher.h
 * Author: kafa
 *
 * Created on June 15, 2017, 11:36 AM
 */

#ifndef SERIALDISPATCHER_H
#define SERIALDISPATCHER_H
#include "thread.h"
#include "channel.h"
#include "serialSender.h"
#include "serialReceiver.h"

class SerialDispatcher: public Stoppable{
 public:
  SerialDispatcher();
  ~SerialDispatcher();
  void step();
 private:
  PulseReceiver receiver_;
  SerialSender sSender_;
  SerialReceiver sReceiver_;
  Thread *th_;
  Worker *worker_;
};


#endif /* SERIALDISPATCHER_H */

