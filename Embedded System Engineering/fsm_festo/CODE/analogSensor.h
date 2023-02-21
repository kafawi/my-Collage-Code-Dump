/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   analogSensor.h
 * Author: kafa
 *
 * Created on June 6, 2017, 6:57 AM
 */

#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "gpio.h"
#include "analogPortStrat.h"
#include "channel.h"
#include "thread.h"

#define ARR_LEN 5
#define H_MINUS 1,1,1,1,1

class AnalogSensor : public Stoppable
{
 public:
  virtual void step();
  void endSampling();
  void startSampling();
  AnalogSensor();
  virtual ~AnalogSensor();
 private:
  uint16_t firFilter();
  PulseTransmitter transmitter_;
  AnalogPortStrat portStrat_;
  Thread *th_;
  Worker *worker_;
  uint16_t value_;
  uint16_t array_[ARR_LEN];
  const uint16_t h_[ARR_LEN];
  uint32_t count_;
  bool isSampleEnd_;
 // uint16_t fir();
 // uint16_t array[];
};

#endif /* ANALOGSENSOR_H */

