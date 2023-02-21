/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialSender.cpp
 * Author: kafa
 * 
 * Created on June 21, 2017, 1:18 PM
 */

#include "serialSender.h"
#include "sio.h"
#include "replayLogger.h"
#include <iostream>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
SerialSender::SerialSender ()
: toMclTrans_ (*(Sio::getInstance ()->getChEventOut ()))
, strat_ ()
, dev_ (DEVOUT)
, fdesc_ (-1)
{
  strat_.config (fdesc_, dev_);
  std::cout << "SerialSender ctor" << std::endl;
}
SerialSender::~SerialSender () 
{
  if (close (this->fdesc_) < 0)
  {
    exit (-1);
  }
}
void
SerialSender::sendHeader (void *header) 
{
int ret = -1;
  Pulse_t pout;
  pout.code = INSTANT_BACK;
  ret = strat_.sendPkg (fdesc_,header, sizeof (Header));
  cout << "sent header" << endl;
  if (ret != sizeof(Header))
  {
    pout.value.i = HEADER_DISCONNECT;
  }
  else
  {
    int8_t ack = -1;
    cout << "HEADER_DISCONNECT" << endl;
    ret = strat_.recvPkg (fdesc_, &ack, sizeof (ack), ACKTIME);
    if (ack != PKG_ACK || ret != sizeof (ack))
    {
      pout.value.i = HEADER_DISCONNECT;
    }
    else
    {
    	cout << " HEADER_SEND_OK" << endl;
      pout.value.i = HEADER_SEND_OK;
    }
  }
  LOG_REPLAY_PULSE(SERIELL, pout)
  toMclTrans_.push (pout);
  cout << " toMclTrans" << endl;
}
void
SerialSender::sendPukData (void *pukData)
{
  int ret = -1;
  Pulse_t pout;
  pout.code = INSTANT_BACK;
  ret = strat_.sendPkg (fdesc_, pukData, sizeof (PukData));
  if (ret != sizeof(PukData))
  {
    pout.value.i = PUKDATA_DISCONNECT;
  }
  else
  {
    int8_t ack = -1;
    ret = strat_.recvPkg (fdesc_, &ack, sizeof (ack), ACKTIME);
    if (ack != PKG_ACK || ret != sizeof (ack))
    {
      pout.value.i = PUKDATA_DISCONNECT;
    }
    else
    {
      pout.value.i = PUKDATA_SEND_OK;
    }
  }
  LOG_REPLAY_PULSE(SERIELL, pout)
  toMclTrans_.push (pout);
}
void
SerialSender::sendSysStatus (void *sysUpdate)
{
  int ret = -1;
  Pulse_t pout;
  pout.code = INSTANT_BACK;
  cout << " vor send sysData" << endl;
  ret = strat_.sendPkg (fdesc_, sysUpdate, sizeof (SysUpdate));
  cout << "sent sys status" << endl;
  if (ret != sizeof (SysUpdate))
  {
    pout.value.i = SYSUPDATE_DISCONNECT;
  }
  else
  {
    int8_t ack = -1;
    ret = strat_.recvPkg (fdesc_, &ack, sizeof (ack), ACKTIME);
    if (ack != PKG_ACK || ret != sizeof (ack))
    {
      pout.value.i = SYSUPDATE_DISCONNECT;
    }
    else
    {
      pout.value.i = SYSUPDATE_SEND_OK;
    }
  }
  LOG_REPLAY_PULSE(SERIELL, pout)
  toMclTrans_.push (pout);
}
