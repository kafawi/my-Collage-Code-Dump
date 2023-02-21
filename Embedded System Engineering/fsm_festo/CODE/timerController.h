/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimerController.h
 * Author: kafa
 *
 * Created on June 14, 2017, 9:34 PM
 */

#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include "timer.h"
#include "lock.h"
#include "thread.h"
#include "channel.h"
#include "mgt.h"
#include <list>

#define STEP_TIME_MS 10

#define SPEED_FAST 100
#define SPEED_SLOW  31
#define SPEED_STOP   0

#define DELTA_ENTRY  (SPEED_FAST * 1993)
#define DELTA_MIDDLE (SPEED_FAST * 900)
#define DELTA_OUTLET (SPEED_FAST * 1972)
#define DELTA_GATE   (SPEED_FAST * 856)
#define DELTA_TOLERANCE (SPEED_FAST * 600)
#define DELTA_PROFILEDETECTION (SPEED_FAST * 800)

#define MAXTIME_SERIAL 3000
#define MAXTIME_RAMP 500
#define MAXTIME_METAL 100
#define MAXTIME_GATE 300
#define MAXTIME_ANTI_PRELL 100 // ESTOP_ANTI_PRELL_TIMER
typedef struct CalibartionData{
  CalibartionData()
  :speed{
    SPEED_FAST
   ,SPEED_SLOW
   ,SPEED_STOP
  }
  ,delta{
    DELTA_ENTRY
   ,DELTA_MIDDLE
   ,DELTA_OUTLET
   ,DELTA_GATE
   ,DELTA_PROFILEDETECTION
   ,DELTA_TOLERANCE
  }
  ,maxtime{
    MAXTIME_SERIAL
   ,MAXTIME_RAMP
   ,MAXTIME_METAL
   ,MAXTIME_GATE
   ,MAXTIME_ANTI_PRELL
  }
  {}
  // TODO CalibrationData custom Ctor 
  struct{
    int32_t fast;
    int32_t slow;
    int32_t stop;
  } speed;
  struct{
    int32_t entry;
    int32_t middle;
    int32_t outlet;
    int32_t gate; 
    int32_t profiledetection;
    int32_t tolerance;
  } delta;
  struct{
    int32_t serial;
    int32_t ramp;
    int32_t metal;
    int32_t gate;
    int32_t antiprell;
  } maxtime;
}CalibrationData;

enum Speed{
  FAST
 ,SLOW
 ,STOP
};

class TimerController : public Stoppable
{
 public:
  void step();
  Timer *getTimer();
  void static speedUpdate(enum Speed speed );
  void setCalibrationData(CalibrationData cd);
  void resetTimer(Timer *timer, enum MCL_input_signal ret);
  void suspendTimers();
  void resumeTimers();
  TimerController();
  virtual ~TimerController();
 private:
  void resetTimer(Timer *timer, enum MCL_input_signal ret, int32_t delta);
  Timer *createTimer(enum MCL_input_signal ret);
  int32_t getSpeedVal();
  int32_t getDelta(enum MCL_input_signal ret);
  CalibrationData caliData_;
  PulseTransmitter trans_;
  std::list<Timer> timerList_;
  Mutex listMtx_;
  Thread * th_;
  Worker * worker_;
  mgt::TimePoint tp_;
  static enum Speed speed_;
};




#endif /* TIMERCONTROLLER_H */
