/*
 * halDipatcher.h
 *
 *  Created on: Jun 1, 2017
 *      Author: kafa
 */

#ifndef HAL_LIB_HALDIPATCHER_H_
#define HAL_LIB_HALDIPATCHER_H_

#include "thread.h"
#include "channel.h"
#include "digitalPortStrat.h"
#include "sensor.h"

class HalDispatcher : public Loopable
{
 public:
  virtual void loop();
  HalDispatcher();
  virtual ~HalDispatcher();
 private:
  PulseReceiver receiver_;
  DigitalPortStrat portStrat_;
  Sensor sensor_;
};

#endif /* HAL_LIB_HALDIPATCHER_H_ */
