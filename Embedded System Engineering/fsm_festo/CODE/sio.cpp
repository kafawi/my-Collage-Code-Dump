/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sio.cpp
 * Author: kafa
 * 
 * Created on June 13, 2017, 6:50 PM
 */

#include "sio.h"
#include "channel.h"
#include "lock.h"
#include "serialDispatcher.h"
#include "thread.h"
/// Channel
PulseChannel * 
Sio::getChCmdIn(){
  return &chCmdIn_;
};

PulseChannel *
Sio::getChEventOut(){
  return chEventOut_;
};
  
void
Sio::setChEventOut(PulseChannel *ch){
  chEventOut_ = ch;
};


/// init and destroy;
void
Sio::init()
{
  std::cout << "sio init enter" <<std::endl;
  disp_ = new SerialDispatcher();
  std::cout << "sio init disp_" <<std::endl;
  worker_ = new Worker(*disp_);
  std::cout << "sio init worker" <<std::endl;
  sioTh_ = new Thread(*(worker_));
  std::cout << "sio init thread -- end " <<std::endl;
}

void
Sio::destroy()
{
  sioTh_->join ();
  delete (sioTh_);
  delete (worker_);
  delete (disp_);
  std::cout << "hal destroy"<< std::endl;
}



/// SINGELTON
Sio::Sio ()
:chCmdIn_()
,chEventOut_(nullptr)
,sioTh_(nullptr)
,worker_(nullptr)
{ }

Sio::~Sio () 
{
  initMtx_.acquire();
  instance_ = nullptr;
  initMtx_.release();
}

Sio *
Sio::getInstance(){
  if (nullptr == instance_){
    initMtx_.acquire();
    if (nullptr == instance_){
    	instance_ = new Sio();
    }
    initMtx_.release();
  }
  return instance_; 
}

Mutex
Sio::initMtx_;
Sio *
Sio::instance_ = nullptr;  