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
#include <iostream>
#include "mcl.h"
#include "channel.h"
#include "lock.h"
#include "thread.h"






// getter Setter
PulseChannel *
  Mcl::getChMasterControlIn(){
    return &chMasterControlIn_;
  }

  PulseChannel *
  Mcl::getChActorOut(){
    return chActorOut_;
  }

  PulseChannel *
  Mcl::getChAnalogSensorIn(){
    return &chAnalogSensorIn_;
  }

  void
  Mcl::setChActorOut(PulseChannel *ch){
    chActorOut_= ch ;
  }
  
  void
  Mcl::setChSerialOut(PulseChannel *ch){
    chSerialOut_=ch;
  }
  
  PulseChannel *
  Mcl::getChSerialOut (){
    return chSerialOut_;
    
  }
  
  PulseChannel *
  Mcl::getChSerialIn(){
    return &chSerialIn_;
  }
  
  PulseChannel *
  Mcl::getChHidIn(){
    return &chHidIn_;
  }
  
  PulseChannel *
  Mcl::getChHidOut(){
    return chHidOut_;
  }
  void 
  Mcl::setChHidOut(PulseChannel *ch){
    chHidOut_ = ch;
  }
// --------------------------------------------- Singelton stuff
Mcl::Mcl()
: chMasterControlIn_()
, chAnalogSensorIn_()
, chActorOut_(nullptr)
, chSerialIn_()
, chSerialOut_(nullptr)
, chHidIn_()
, chHidOut_(nullptr)
, mclTh_(nullptr)
, worker_(nullptr)
, disp_(nullptr)
, data_(nullptr)
{
  std::cout << "mcl ctor" <<std::endl;
}
Mcl::~Mcl(){
  initMtx_.acquire();
  instance_ = nullptr;
  initMtx_.release();
  std::cout << "hal dtor" <<std::endl;
}
Mcl*
Mcl::getInstance()
{
  if (nullptr == instance_){
    initMtx_.acquire();
    if (nullptr == instance_){
    	instance_ = new Mcl();
    }
    initMtx_.release();
  }
  return instance_;
}
//------------------------------------------ TODO TODO TODO
void
Mcl::init(bool isReceivingEnd)
{
  std::cout << "mcl init" <<std::endl;
  data_ = new Data(isReceivingEnd);
  disp_ = new MclDispatcher();
  worker_ = new Worker(*disp_);
  mclTh_ = new Thread(*(worker_));
  // init the hole thingi
  // TODO think about all this, does it in heap;
  // no class should know this hal.
  // The main Class should init all Instances
  // shell it know all Main Instances (namely Dispatcher, Sensor , Actor?)
  // yes because, it has to free the Classes.
  // dispatchth_ = new Thread();
}

void
Mcl::destroy()
{
  mclTh_->join ();
  delete (mclTh_);
  delete (worker_);
  delete (disp_);
  std::cout << "hal destroy"<< std::endl;
}

Data *
Mcl::getData(){
  return data_;  
}

Mcl*
Mcl::instance_ = nullptr;
Mutex
Mcl::initMtx_;

