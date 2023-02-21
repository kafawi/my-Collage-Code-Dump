/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimerController.cpp
 * Author: kafa
 * 
 * Created on June 15, 2017, 1:55 PM
 */

#include "timerController.h"
#include "timer.h"
#include "mcl.h"
#include <iostream>
//#include "logAndReplayLogger.h"
TimerController::TimerController ()
:caliData_()
,trans_(*(Mcl::getInstance ()->getChMasterControlIn ()))
,timerList_()
,listMtx_()
,th_(nullptr)
,worker_(nullptr)
,tp_()
{ 
  std::cout << "TimerController ctor" << std::endl;
  tp_ = mgt::timeNow ();
  worker_ = new Worker(*this);
  th_ = new Thread(*(worker_));
  //speedUpdate (SLOW);
}
TimerController::~TimerController () 
{
  this->terminate();
  if (th_->joinable ()){
    th_->join();
  }
  delete (th_);
  delete (worker_);
}
int32_t 
TimerController::getDelta(enum MCL_input_signal ret){
  int32_t delta = -1;
  switch(ret){
    case (TO_PROFILE_DETECTION_MIN):
      delta = caliData_.delta.entry - caliData_.delta.tolerance;
      break;
    case (TO_PROFILE_DETECTION_MAX):
      delta = caliData_.delta.entry + caliData_.delta.tolerance;
      break;
    case (TO_METAL_DETECTION_MIN):
      delta = caliData_.delta.middle - caliData_.delta.tolerance;
      break;
    case (TO_METAL_DETECTION_MAX):
      delta = caliData_.delta.middle + caliData_.delta.tolerance;
      break;
    case (TO_EXIT_MIN):
      delta = caliData_.delta.entry - caliData_.delta.tolerance;
      break;
    case (TO_EXIT_MAX):
      delta = caliData_.delta.entry + caliData_.delta.tolerance;
      break;
    case (PROFILE_DETECTION_TIMER):
      delta = caliData_.delta.profiledetection;
      break;
    case (RAMP_TIMER):
      delta =  caliData_.maxtime.ramp; 
      break;
    case (METAL_DETECTION_TIMER):
      delta = caliData_.maxtime.metal;
      break; 
    case(GATE_TIMER): // this is a DistanceTimer now
      delta = caliData_.delta.gate;
      std::cout << "GATETIMER_CREATET" << delta << std::endl;
      break;
    case(ESTOP_ANTI_PRELL_TIMER):
      delta = caliData_.maxtime.antiprell;
      break;
    default:
      delta = -1;
  }
  return delta;
}

Timer *
TimerController::getTimer ()
{
  Timer *rettimer = createTimer(UNKNOWN_MCL_SIGNAL);
  return rettimer;
}
Timer *
TimerController::createTimer (enum MCL_input_signal ret)
{
  listMtx_.acquire ();
  Timer t;
  timerList_.push_back (t);
  Timer &tptr= timerList_.back ();
  listMtx_.release ();
  return &tptr;
}
void
TimerController::resetTimer (Timer* timer,enum MCL_input_signal ret) {
  resetTimer(timer, ret,getDelta(ret) );
}
void
TimerController::resetTimer (Timer * timer
                            , enum MCL_input_signal ret
                            , int32_t delta
) {
 listMtx_.acquire ();
 timer->reset (ret, delta);
 listMtx_.release ();
}

enum Speed
TimerController::speed_=STOP;
enum Speed 
stspeed = STOP;
void
TimerController::speedUpdate (Speed speed){
  stspeed = speed;
  std::cout << "updateSpeed: " << speed << std::endl; 
}

void 
TimerController::step(){
  static int32_t v = 0;
  static std::list<std::list<Timer>::iterator> toDelete;
  Speed s = stspeed;


  switch(s){
    case(STOP):
      v = caliData_.speed.stop;
      break;
    case(SLOW):
      v = caliData_.speed.slow;
      break;
    case(FAST):
      v = caliData_.speed.fast;
      break;
  }
  if(speed_ != s){
	  std::cout << "\nv: " << v << "\n"<< std::endl;
	  speed_ =s;
  }
  mgt::Time duration = mgt::elapsed (tp_);
  listMtx_.acquire ();
  for (std::list<Timer>::iterator it = timerList_.begin();
       it != timerList_.end();
       it++)
  {
    if (it->isDestroyed_){
      toDelete.push_back (it);
      continue;
    }
    if (!it->isSuspended_ && !it->isExpired_){
      if (it->type_ == TIME){
        it->delta_ -= duration;
      } else if (it->type_ == DISTANCE){
        it->delta_ -= duration * v;
        std::cout << "delta: " << it->ret_ << "  " << it->delta_ << " " << v <<std::endl;
      }
      if (it->delta_ <= 0 ){
        it->isExpired_ = true;
        Pulse_t pout;
        pout.code = INCOMMING_CODE;
        pout.value.i = it->ret_;
        it->ret_ = UNKNOWN_MCL_SIGNAL;
        trans_.push (pout);
      }
    }
  }
  // deletion
  while (!toDelete.empty ()){
    std::list<Timer>::iterator it = toDelete.front ();
    timerList_.erase (it);   
    toDelete.pop_front ();
  }
  listMtx_.release();
  mgt::threadSleep (STEP_TIME_MS);
}

void 
TimerController::setCalibrationData(CalibrationData cd){
  caliData_ = cd;
}

void 
TimerController::suspendTimers(){
  stop();    
}
void
TimerController::resumeTimers(){
  tp_ = mgt::timeNow ();
  conti();
}
