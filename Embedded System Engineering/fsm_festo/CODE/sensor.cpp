/*
 * sensor.cpp
 *
 *  Created on: Jun 1, 2017
 *      Author: kafa
 */

#include "sensor.h"
#include <iostream>

Sensor::Sensor()
: irq_()
, asensor_()
, irqTh_(nullptr)
, aTh_(nullptr)
, irqWorker_(nullptr)
, aWorker_(nullptr)
{
  irqWorker_ = new Worker(irq_);
  aWorker_= new Worker(asensor_);
  irqTh_ = new Thread(*(irqWorker_));
  aTh_ = new Thread(*(aWorker_));
}

void Sensor::startAnalog() {
  asensor_.startSampling ();
}

void Sensor::stopAnalog() {
  asensor_.endSampling ();
}

void Sensor::pauseAnalog() {
  asensor_.stop ();
}

void Sensor::continueAnalog() {
  asensor_.conti ();
}

void Sensor::startIRQ() {
  irq_.signIn ();
}

void Sensor::stopIRQ() {
  irq_.signOut ();
}

void Sensor::terminate() {
  irq_.terminate ();
  asensor_.terminate ();
}

Sensor::~Sensor() {
  if (irqTh_->joinable ()){
    irqTh_->join ();
  }
  delete (irqTh_);
  if (aTh_->joinable ()){
    aTh_->join ();
  }
  delete (aTh_);
  delete (irqWorker_);
  delete (aWorker_);
}