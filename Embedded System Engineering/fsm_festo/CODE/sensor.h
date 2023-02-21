/*
 * sensor.h
 *
 *  Created on: Jun 1, 2017
 *      Author: kafa
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "irqHandler.h"
#include "analogSensor.h"
#include "thread.h"

class Sensor
{
 public:
  Sensor();
  virtual void startAnalog();
  virtual void stopAnalog();
  virtual void pauseAnalog();
  virtual void continueAnalog();
  virtual void startIRQ();
  virtual void stopIRQ();
  virtual void terminate();
  virtual ~Sensor();

 private:
  IrqHandler irq_;
  AnalogSensor asensor_;
  Thread* irqTh_;
  Thread* aTh_;
  Worker* irqWorker_;
  Worker* aWorker_;
};

#endif /* SENSOR_H_ */
