/*
 * SerialReceiver.h
 *
 *  Created on: 08.06.2017
 *      Author: abs430
 */

#ifndef SERIALRECEIVER_H_
#define SERIALRECEIVER_H_

#include "thread.h"
#include "channel.h"
#include "serialStrat.h"
//#include "SerialManager.h"

class SerialReceiver : public Stoppable
{
 private:
  PulseTransmitter trans_;
  SerialStrat strat_;
  const char* dev_;
  int fdesc_;
 public:
  SerialReceiver();
  ~SerialReceiver();
  void step();
 private:
  //Serial(const Serial& other);
  //Serial& operator=(const Serial& other);
};


#endif /* SERIALRECEIVER_H_ */
