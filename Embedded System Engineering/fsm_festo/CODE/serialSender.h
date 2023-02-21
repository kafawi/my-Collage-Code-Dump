/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialSender.h
 * Author: kafa
 *
 * Created on June 21, 2017, 1:18 PM
 */

#ifndef SERIALSENDER_H
#define SERIALSENDER_H

#include "serialStrat.h"
#include "channel.h"
#include "Serial_protocol.h"

class SerialSender
{
 public:
  SerialSender();
  virtual ~SerialSender();
  void sendHeader(void *header);
  void sendPukData(void *pukData);
  void sendSysStatus(void *sysUpdate);
 private:
  PulseTransmitter toMclTrans_;
  SerialStrat strat_;
  const char* dev_;
  int fdesc_;
  
};

#endif /* SERIALSENDER_H */
/*
#ifndef SERIALSENDER_H_
#define SERIALSENDER_H_

#define EMPTY_PACKAGE 1
#include "Serial_protocol.h"
#include "SerialManager.h"

#define DEVSER1 "/dev/ser1"

class SerialSender {
private:
	const char* dev_;
	int fdesc_;

public:
	SerialSender();
	~SerialSender();
	void config(void); //should this be here?
	void send_puk_packet(const uint16_t pukId, const uint16_t pukType, const bool eject);
	void send_acknowledge();
	void send_on_event();
	void send_off_event();
	void send_error_pending_event();
	void send_error_cleared_event();
	void send_error_unacknowledged_event();
	void send_error_acknowledged_event();



private:
	//Serial(const Serial& other);
	//Serial& operator=(const Serial& other);
};
*/
