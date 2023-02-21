/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "timer.h"
#include "MCL_signals.h"
#include <iostream>
Timer::Timer ()
:ret_(UNKNOWN_MCL_SIGNAL)
,delta_(-1)
,isSuspended_(true)
,isDestroyed_(false)
,isExpired_(false)
,type_(UNDEFINED)
{ 
}
Timer::~Timer () { }
void
Timer::cancel () {
  isSuspended_ = true;
}
void
Timer::destroy(){
  isDestroyed_ = true;
}
void
Timer::reset (enum MCL_input_signal ret, int32_t delta)
{
  ret_ = ret;
  calcType();
  delta_ = delta;
  std::cout << "DELTA:" << delta << std::endl;
  isSuspended_ = false;
  isExpired_ = false;
}

void 
Timer::calcType(){
  switch (ret_){
    case(TO_PROFILE_DETECTION_MIN):
    case(TO_PROFILE_DETECTION_MAX):
    case(TO_METAL_DETECTION_MIN):
    case(TO_METAL_DETECTION_MAX):
    case(TO_EXIT_MIN):
    case(TO_EXIT_MAX):
    case(PROFILE_DETECTION_TIMER):
    case(GATE_TIMER):
      type_= DISTANCE ;
      break;
    case(RAMP_TIMER):
    case(METAL_DETECTION_TIMER):
    case(ESTOP_ANTI_PRELL_TIMER):
      type_ = TIME;
      break;
    default:
      type_ = UNDEFINED;
  }
}