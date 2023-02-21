/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mclDispatcher.h
 * Author: kafa
 *
 * Created on June 8, 2017, 2:59 AM
 */

#ifndef MCLDISPATCHER_H
#define MCLDISPATCHER_H

#include "thread.h"
#include "channel.h"
#include "InputMultiplexer.h"
#include "ButtonLightController.h"

class MclDispatcher : public Loopable
{
 public:
  virtual void loop();
  MclDispatcher();
  virtual ~MclDispatcher();
 private:
  PulseReceiver receiver_;
  InputMultiplexer inMpx_;
  ButtonLightController btController_;
};

#endif /* MCLDISPATCHER_H */

