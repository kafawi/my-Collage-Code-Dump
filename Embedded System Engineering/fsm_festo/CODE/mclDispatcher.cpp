/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mclDispatcher.cpp
 * Author: kafa
 * 
 * Created on June 8, 2017, 2:59 AM
 */

#include "mclDispatcher.h"
#include "mcl.h"
#include "MCL_signals.h"

MclDispatcher::MclDispatcher ()
: receiver_ (*(Mcl::getInstance ()->getChMasterControlIn ()))
, inMpx_(Mcl::getInstance ()->getData ())
, btController_()
{ 
  std::cout<< "mcl ctor" << std::endl;
}
MclDispatcher::~MclDispatcher () { }
void
MclDispatcher::loop () {
  Pulse_t pin = receiver_.pull();
  if (INCOMMING_CODE  == pin.code)
  {
    switch(pin.value.i)
    {
      case(STOP_BTN):
        btController_.reportStopPressed ();
        break;
      case(START_BTN):
        btController_.reportStartPressed ();
        break;
      case(RESET_BTN):
        //btController_
        break;
      case(E_STOP_PRESSED):
        //btController_.reportEStopOn ();
        break;
      case(E_STOP_RELEASED):
        //btController_.reportEstopOff ();
        break;
    };
    inMpx_.processCode((MCL_input_signal) pin.value.i);
  
  }
}

