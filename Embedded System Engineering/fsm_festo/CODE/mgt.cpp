/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/* 
 * File:   mgt.cpp
 * Author: kafa
 * 
 * Created on May 21, 2017, 11:53 PM
 */

#include "mgt.h"
#include <thread>
#include <chrono>

mgt::TimePoint
mgt::timeNow(void){
    return Clock::now();
};

mgt::Time
TimeMsToTime(mgt::TimeMs t){
    return t.count();
};
void
mgt::threadSleep(mgt::Time ms){
    std::this_thread::sleep_for(TimeMs(ms));
};

mgt::Time
mgt::elapsed(mgt::TimePoint& _last){
  TimePoint now  = timeNow();
  TimeMs res = std::chrono::duration_cast<TimeMs>(timeNow() - _last);
  _last = now;
  return res.count();
}
