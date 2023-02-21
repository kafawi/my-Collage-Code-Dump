/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/**
 * @file hal.cpp
 *
 *  Created on: Jun 1, 2017
 * @author kafa
 */

#include "hal.h"
#include "halDispatcher.h"
#include "channel.h"
#include "lock.h"
#include "thread.h"
#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <hw/inout.h>
#endif
// See Manual M104-DIO-48S.A1i, Cap. 5: Programming
#define CTRL_REG_GROUP0     0x303
#define DEFAULT_PORTS_SETTINGS 0x8A

// getter Setter
PulseChannel *
  Hal::getChActorIn(){
	  return &chActorIn_;
  }

  PulseChannel *
  Hal::getChDigitalSensorOut(){
    return chDigitalSensorOut_;
  }

  PulseChannel *
  Hal::getChAnalogSensorOut(){
    return chAnalogSensorOut_;
  }

  void
  Hal::setChDigitalSensorOut(PulseChannel *ch){
    chDigitalSensorOut_= ch ;
  }

  void
  Hal::setChAnalogSensorOut(PulseChannel *ch){
    chAnalogSensorOut_ = ch;
  }

// --------------------------------------------- Singelton stuff
Hal::Hal()
: chActorIn_()
, chDigitalSensorOut_(nullptr)
, chAnalogSensorOut_(nullptr)
, worker_(nullptr)
, halTh_(nullptr)
, disp_()
{
  std::cout << "hal ctor" <<std::endl;
#if defined(__QNXNTO__)
  out8(CTRL_REG_GROUP0 ,DEFAULT_PORTS_SETTINGS);
#endif
}

Hal::~Hal(){
	initMtx_.acquire();
	instance_ = nullptr;
	initMtx_.release();
        std::cout << "hal dtor" <<std::endl;
}
Hal*
Hal::getInstance()
{
  if (nullptr == instance_){
    initMtx_.acquire();
    if (nullptr == instance_){
    	instance_ = new Hal();
    }
    initMtx_.release();
  }
  return instance_;
}
//------------------------------------------ 
void
Hal::init()
{
  std::cout << "hal init" <<std::endl;

  disp_ = new HalDispatcher();
  worker_ = new Worker(*disp_);
  halTh_ = new Thread(*(worker_));
  // init the hole thingi
  // TODO think about all this, does it in heap;
  // no class should know this hal.
  // The main Class should init all Instances
  // shell it know all Main Instances (namely Dispatcher, Sensor , Actor?)
  // yes because, it has to free the Classes.
  // dispatchth_ = new Thread();
}

void
Hal::destroy()
{
  halTh_->join ();
  delete (halTh_);
  delete (worker_);
  delete (disp_);
  std::cout << "hal destroy"<< std::endl;
}
Hal*
Hal::instance_ = nullptr;
Mutex
Hal::initMtx_;
