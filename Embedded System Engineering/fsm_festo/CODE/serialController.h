/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialController.h
 * Author: kafa
 *
 * Created on June 19, 2017, 9:35 PM
 */

#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include "channel.h"
#include "thread.h"
#include "MCL_signals.h"
#include "Serial_protocol.h"
#include "Puk.h"
#include <queue>

class Data;

class SerialController : public Stoppable
{
 public:
  SerialController(Data *data);
  virtual ~SerialController();
  void sendSysStatusUpdate(enum MCL_input_signal statusUpdate);
  void transferPuk(Puk *puk);
  Puk *getReceivedPuk();
  void step();
 private:
  void listenAndReact();
  PukData *convertPuk(Puk *puk);
  Puk *convertPukData(PukData *pukData);
  Data *data_;
  PulseTransmitter mclMasterTrans_;
  PulseTransmitter serialTrans_;
  PulseReceiver    serialRecv_;
  Worker * worker_;
  Thread *th_;
  std::queue<Puk*> receivedPuk_;
  std::queue<Header*> headerList_;
  std::queue<PukData*> pukDataList_;
  std::queue<SysUpdate*> sysUpdateList_;
  PukData pud;
  Puk* received_;
};

#endif /* SERIALCONTROLLER_H */

