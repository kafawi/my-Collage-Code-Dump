/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   timer.h
 * Author: kafa
 *
 * Created on June 14, 2017, 9:27 PM
 */

#ifndef TIMER_H
#define TIMER_H
#include "MCL_signals.h"
#include <cstdint>
#include <stdint.h>

enum TimerType{
  //Timeouts
  ENTRY_MIN,
  ENTRY_MAX,
  MIDDLE_MIN,
  MIDDLE_MAX,
  OUTLET_MIN,
  OUTLET_MAX,
  RAMP_MAX,
  METAL_DETECTION_MAX,
  GATETIME,
  GATEDISTANCE,
  SERIALTIME
};

enum DistanceTime{
  DISTANCE
 ,TIME
 ,UNDEFINED
};

class Timer{
 public:
  Timer();
  ~Timer();
  void cancel();
  void destroy();
  void reset(enum MCL_input_signal ret, int32_t delta);
  enum MCL_input_signal ret_; 
  int32_t delta_;
  bool isSuspended_;
  bool isDestroyed_;
  bool isExpired_;
  enum DistanceTime type_;
 private:
  void calcType();
};


#endif /* TIMER_H */

