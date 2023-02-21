/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GateController.h
 * Author: kafa
 *
 * Created on June 8, 2017, 5:34 AM
 */

#ifndef GATECONTROLLER_H
#define GATECONTROLLER_H
#include "channel.h"
class GateController
{
 public:
  GateController();
  virtual ~GateController();
  void open();
  void close();
 private:
  //todo: Timer *gateTmr
  PulseTransmitter trans_;
  Pulse_t pout_;
};

#endif /* GATECONTROLLER_H */

