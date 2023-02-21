/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   analogSensor.cpp
 * Author: kafa
 * 
 * Created on June 6, 2017, 6:57 AM
 */

#include "analogSensor.h"
#include "hal.h"
#include "analogPortStrat.h"
#include "replayLogger.h"
//#include "SamplingSignal.h"
#include "ProfileDetection_signals.h"

#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <hw/inout.h>
#endif
#include <iostream>
#include <stdint.h>
#include <unistd.h>

// hilfsfunktionen (keine methsoden)
// hilfsvarablen
void
AnalogSensor::step ()
{
  if (isSampleEnd_)
  {
    Pulse_t pout;
    pout.code = ENDSAMPLING;
    pout.value.i = 0;
    LOG_REPLAY_PULSE(HEIGHTMEASURE, pout)
    transmitter_.push (pout);
    std::cout << "Smpling ended" << std::endl;
    stop();
  }
  else
  {
    value_ = portStrat_.getValue ();
    array_[count_%ARR_LEN] = value_;
    if (count_ >= ARR_LEN)
    {
      value_ = firFilter ();
      Pulse_t pout;
      pout.code = SAMPLE;
      pout.value.i = static_cast<int32_t>(value_);
      LOG_REPLAY_PULSE (HEIGHTMEASURE, pout)
      transmitter_.push (pout);
    } else {
    count_++;
    }
  }
}

#define PORTINFO { 0x320, 0x2, 0x3, 0x2,0x10,0x0FFF } 

AnalogSensor::AnalogSensor ()
: transmitter_ (*(Hal::getInstance ()->getChAnalogSensorOut()))
, portStrat_ (PORTINFO)
, th_ (nullptr)
, worker_ (nullptr)
, value_ (0)
, array_{0}
, h_ {H_MINUS} // median
, count_ ()
, isSampleEnd_ (false)
{
  //std::cout << h_[0] << h_[1] << h_[2] << h_[3] << h_[4] << std::endl;
  stop ();
  worker_ = new Worker (*this);
  th_ = new Thread ((*worker_));
}
AnalogSensor::~AnalogSensor ()
{
  th_->join ();
  delete ( th_);
  delete ( worker_);
}
uint16_t
AnalogSensor::firFilter ()
{
  static int pos = 0;
  pos = (pos + 1) % ARR_LEN;
  uint16_t ret = 0;
  for (int i = 0; ARR_LEN > i; i++)
  {
    ret += (array_[(pos + i) % ARR_LEN] * h_[i]) / ARR_LEN;
  }
  return ret;
}
void
AnalogSensor::endSampling ()
{
  isSampleEnd_=true;
  std::cout << "Sampling ende "<< endl;
  count_ = 0;
};
void
AnalogSensor::startSampling ()
{
  count_ = 0;
  isSampleEnd_=false;
  conti ();
};
