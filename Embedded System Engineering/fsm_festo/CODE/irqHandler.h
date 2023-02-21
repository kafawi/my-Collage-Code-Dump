/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   irqHandler.h
 * Author: kafa
 *
 * Created on June 6, 2017, 6:28 AM
 */

#ifndef IRQHANDLER_H
#define IRQHANDLER_H

#include "channel.h"
#include "thread.h"
#include "digitalPortStrat.h"

class IrqHandler: public Loopable{
 public:
  IrqHandler();
  virtual ~IrqHandler();
  virtual void loop();
  void signIn();
  void signOut();
  
 private:
  PulseTransmitter transmitter_;
  DigitalPortStrat portStrat_;
  int irqChid_;
  int irqChcon_;
};
#endif /* IRQHANDLER_H */

