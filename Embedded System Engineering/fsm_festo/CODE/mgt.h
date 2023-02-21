/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/**
 * @file   mgt.h
 * @brief this is are some usefule typedefs and functions
 *    
 *   this is like our own system library 
 * @author kafa
 *
 * Created on May 21, 2017, 11:53 PM
 */

#ifndef _MGT_H
#define _MGT_H

#include <chrono>

/**
 * @class for this project useful "Typedefs" and functions
 *  
 * this is more like a namespace, but in an objective way
 */
class mgt
{
 public:
  //using Speed = double;                     /**< Type of speed */
  using TimeMs = std::chrono::milliseconds; /**< Type of milliseconds */
  using Clock = std::chrono::steady_clock;  /**< Type of our used clock */
  using TimePoint = Clock::time_point;      /**< Type of an Timepoint */
  using Time = int32_t;                     /**< time type to calculate with */
  using Distance = int32_t;                 /**< distance type to calc with */
  
  /**
   * Get current Time
   * @return 
   *   TimePoint from now for advance calculating in TimeSpace
   */
  static TimePoint timeNow(void);
  
  /**
   * Change Type TimeMs to an more useful type of Time (ms)
   * @param t 
   *    duration in ms  
   * @return 
   *    t as an useful type Time
   */
  static Time TimePointToMs(TimeMs t); 
  
  /**
   * sets thread to sleep for some ms
   * @param ms
   *   duration to sleep
   */  
  static void threadSleep(Time ms);
  
  static Time elapsed(TimePoint& _last);
};

#endif /* _MGT_H */

