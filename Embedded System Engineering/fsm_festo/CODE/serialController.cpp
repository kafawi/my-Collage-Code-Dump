/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialController.cpp
 * Author: kafa
 * 
 * Created on June 19, 2017, 9:35 PM
 */

#include "serialController.h"
#include "mcl.h"
#include "Data.h"
#include "Serial_protocol.h"
#include "Serial_commands.h"
#include "timerController.h"
#include "Puk.h"
#include "replayLogger.h"
#include <iostream>
SerialController::SerialController (Data *data)
: data_ (data)
, mclMasterTrans_ (*(Mcl::getInstance ()->getChMasterControlIn ()))
, serialTrans_ (*(Mcl::getInstance ()->getChSerialOut ()))
, serialRecv_ (*(Mcl::getInstance ()->getChSerialIn ()))
, worker_ (nullptr)
, th_ (nullptr)
, receivedPuk_ ()
, headerList_ ()
, pukDataList_ ()
, sysUpdateList_ ()
, pud()
, received_(nullptr)
{
  worker_ = new Worker (*this);
  th_ = new Thread (*(worker_));
  std::cout << "SerialController::ctor" << std::endl;
}
SerialController::~SerialController ()
{
  if (th_->joinable ()) th_->join ();
  delete (th_);
  delete (worker_);
}
PukData *
SerialController::convertPuk (Puk *puk)
{
  PukData *pd = new PukData;
  pd->puk_id = puk->ID;
  pd->puk_type = puk->getType ();
  pd->height1 = puk->height1;
  pd->height2 = puk->height2;
  pd->eject = puk->sceduledForEjection;
  std::cout << "SERIALCONTRLLER::convertPuk" << std::endl;
  return pd;
}
Puk *
SerialController::convertPukData (PukData *pukData)
{
  Puk *p = new Puk (data_->timerCtrl->getTimer (), data_->timerCtrl->getTimer ());
  p->setType (pukData->puk_type);
  p->sceduledForEjection = pukData->eject;
  p->height1 = pukData->height1;
  p->height2 = pukData->height2;
  p->printMe();
  std::cout << "SERIALCONTRLLER::convertPukData" << std::endl;
  return p;
}
void
SerialController::sendSysStatusUpdate (enum MCL_input_signal statusUpdate)
{
  std::cout << "SerialController::sendSysStatusUpdate enter" << std::endl;
  // TODO checking, if statusUpdate is valide
  Header *h = new Header;
  Pulse_t pout;
  // HEADER
  h->type = SYSUPDATE_PKT;
  h->packet_size = sizeof (SysUpdate);
  headerList_.push (h);
  pout.code = HEADER_PTR;
  pout.value.p = h;
  serialTrans_.push (pout);
  // SYSDATA
  SysUpdate *su = new SysUpdate;
  su->signal = statusUpdate;
  sysUpdateList_ .push (su);
  pout.code = SYSUPDATE_PTR;
  std::cout << "sysUpdate/ERROR_PENDING_NO_ACK/su->signal : " << statusUpdate << "/" << ERROR_PENDING_NO_ACK << "/" << su->signal << std::endl;
  pout.value.p = su;
  serialTrans_.push (pout);
  std::cout << "SerialController::sendSysStatusUpdate exit" << std::endl;
}
void
SerialController::transferPuk (Puk *puk)
{
  std::cout << "SerialController::transferPuk enter" << std::endl;

  std::cout << "SerialController::transferPuk enter" << std::endl;
  Header *h = new Header;
  PukData *p = convertPuk (puk);
  Pulse_t pout;
  h->packet_size = sizeof (*p);
  h->type = PUKDATA_PKT;
  headerList_.push (h);
  pout.code = HEADER_PTR;
  pout.value.p = h;
  pukDataList_.push (p);
  serialTrans_.push (pout);
  pout.code = PUK_DATA_PTR;
  pout.value.p = p;
  serialTrans_.push (pout);
  std::cout << "SerialController::transferPuk exit" << std::endl;
}
// listening
void
SerialController::step ()
{
  listenAndReact ();
}
void
SerialController::listenAndReact ()
{
  Pulse_t pin = serialRecv_.pull ();
  Pulse_t pout;
  switch (pin.code)
  {
    case(INSTANT_BACK):
      switch (pin.value.i)
      {
        case(HEADER_SEND_OK): {
          std::cout << "SerialController::listenAndReact got HEADER_SEND_OK " << std::endl;

          if (headerList_.empty())
          {
            std::cout << "headerList_ empty " << std::endl;
          }
          else
          {
        	Header *h = headerList_.front () ;
        	std::cout << "bc headerlistpop" << std::endl;
        	headerList_.pop ();
            delete(h);
            std::cout << "after headerlistpop" << std::endl;
          }
          break;
        }
        case(PUKDATA_SEND_OK):
          std::cout << "SerialController::listenAndReact got PUKDATA_SEND_OK " << std::endl;
          if (pukDataList_.empty()){
            std::cout << "pukDataList_ is empty()" << std::endl;
          } else {
            delete(pukDataList_.front ());
            pukDataList_.pop ();
          }
          break;
        case(SYSUPDATE_SEND_OK):
          std::cout << "SerialController::listenAndReact got SYSUPDATE_SEND_OK " << std::endl;
          if (sysUpdateList_.empty()){
            std::cout << "sysUpdateList_. is empty " << std::endl;
          } else {
          delete(sysUpdateList_.front ());
          sysUpdateList_.pop ();
          }
          break;
        case(HEADER_DISCONNECT):
          std::cout << "SerialController::listenAndReact got HEADER_DISCONNECT " << std::endl;
        case(PUKDATA_DISCONNECT):
        case(SYSUPDATE_DISCONNECT):
          std::cout << "SERIAL: DISCONNECT, DISCONNECT" << std::endl;
          pout.code = INCOMMING_CODE;
          pout.value.i = SERIAL_CONNECTION_FAIL;
          mclMasterTrans_.push (pout);
          break;
      }
      break;
    case(PUKDATA_INCOMMING_ID):
    {
      pud.puk_id = pin.value.i;
      std::cout <<"\n\n\n\n-----\n\n" << pud.puk_id << static_cast<int>(pin.value.i) << std::endl;
    }
      break;
    case( PUKDATA_TYPE):
    {
      pud.puk_type = static_cast<PukType>(pud.puk_type);
      std::cout <<"\n\n\n\n-----\n\n" << pud.puk_type << static_cast<PukType>(pin.value.i) << std::endl;
    }
      break;
    case(PUKDATA_HEIGHT_1):
    {
      pud.height1 = static_cast<int16_t>(pin.value.i);
      std::cout <<"\n\n\n\n-----\n\n" << pud.height1 << static_cast<int16_t>(pin.value.i) << std::endl;
    }
      break;
    case(PUKDATA_HEIGHT_2):
    {
      pud.height2 = static_cast<int16_t>(pin.value.i);
      std::cout <<"\n\n\n\n-----\n\n" << pud.height2 << static_cast<int16_t>(pin.value.i) << std::endl;
    }
      break;
    case(PUKDATA_END_EJACT):
    {
      pud.eject = pin.value.i;
      std::cout <<"\n\n\n\n-----\n\n"<< pud.eject << static_cast<bool>(pin.value.i)<< std::endl;
      std::cout << "\n -------------------\n" ;
      std::cout << pud.puk_id << " " << pud.puk_type << " " << pud.height1 << " " << pud.height2 << " " << pud.eject << std::endl;
      pout.code = INCOMMING_CODE;
      pout.value.i = RECEIVED_PUK;
      Puk * p = nullptr;
      p = convertPukData (&pud);
      std::cout  << "Puk Received: "<< p->ID << p->height1 << p->height2 << std::endl;

      receivedPuk_ .push (p);
     if ( receivedPuk_.empty()) {
    	 std::cout << "right after push it is empty" << std::endl;
     }
     received_=p;
      mclMasterTrans_.push (pout);
    }
      break;
    case(SYSUPDATE_INCOMMING):
    {
      std::cout << "SysUpdate_incopmmming" << std::endl;
      pout.code = INCOMMING_CODE;
      pout.value.i = pin.value.i;
      std::cout << "before mclMasterpush" << std::endl;
      mclMasterTrans_.push (pout);
    }
      break;
    default:
      std::cout << "SERIAL WRONG ENUM PKT TYPE" << std::endl;
      break;
  }
}
Puk *
SerialController::getReceivedPuk ()
{
  Puk *puk = nullptr;
  if (receivedPuk_.empty()){
	  std::cout<<"mal wieder empty" << std::endl;
	  puk = received_;
	  if (received_ == nullptr){
		  std::cout << "also this is fucked uop" << std::endl;
	  }
  } else{
  std::cout<<"DOCH NICHT LEER" << std::endl;
  puk = receivedPuk_.front ();
  if (nullptr == puk){
	  std::cout<<"FICKEN" << std::endl;
  }
  receivedPuk_.pop ();
}
  data_->receivedPuk = puk;
  return puk;
}
