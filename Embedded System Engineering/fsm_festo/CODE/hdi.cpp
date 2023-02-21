/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hid.cpp
 * Author: kafa
 * 
 * Created on June 15, 2017, 2:02 PM
 */

#include "hdi.h"
//#include "hidDispatcher.h"
#include "thread.h"


Hdi::Hdi ()
:chCmdIn_()
,chEventOut_(nullptr)
,disp_(nullptr)
,hidTh_(nullptr)
,worker_(nullptr)
{}
Hdi::~Hdi () 
{
  initMtx_.acquire();
  instance_ = nullptr;
  initMtx_.release();
}
Hdi *
Hdi::getInstance()
{
  if (nullptr == instance_){
    initMtx_.acquire();
    if (nullptr == instance_){
    	instance_ = new Hdi();
    }
    initMtx_.release();
  }
  return instance_; 
}
void 
Hdi::init(){
  //disp_ = new HidDispatcher();
  //worker_ = new Worker(*disp_);
  //hidTh_  = new Thread((worker_));
}
void 
Hdi::destroy(){
  if (hidTh_->joinable ()){
    hidTh_->join ();
  }
  delete (hidTh_);
  delete (worker_);
//  delete (disp_);
}
PulseChannel *
Hdi::getChCmdIn(){
  return &chCmdIn_;    
} 
PulseChannel *
Hdi::getChEventOut(){
  return chEventOut_;
}
void 
Hdi::setChEventOut(PulseChannel *ch){
  chEventOut_ = ch;
}

Mutex
Hdi::initMtx_;         /**< for instance_ access security */
Hdi *
Hdi::instance_ = nullptr;         /**< pointer to the only instance */