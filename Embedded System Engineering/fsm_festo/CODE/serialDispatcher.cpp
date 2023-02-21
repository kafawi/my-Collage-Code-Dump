/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "serialDispatcher.h"
#include "channel.h"
#include "Serial_commands.h"
#include "sio.h"

#include <iostream>
#include <unistd.h>
SerialDispatcher::SerialDispatcher ()
: receiver_ (*(Sio::getInstance ()->getChCmdIn ()))
, sSender_ ()
, sReceiver_ ()
, th_ (nullptr)
, worker_ (nullptr)
{
  worker_ = new Worker(sReceiver_);
  th_ = new Thread(*(worker_));
  std::cout << "ctor SerialDispatcher" << std::endl;
}
SerialDispatcher::~SerialDispatcher ()
{
  if(th_->joinable ()) th_->join ();
  delete (th_);
  delete (worker_);
  std::cout << "dtor SerialDispatcher" << std::endl;
}
void
SerialDispatcher::step ()
{
  Pulse_t pin = receiver_.pull ();
  switch (pin.code)
  {
    case(HEADER_PTR):
		std::cout << "SerialDispatcher::step HEADER_PTR enter"<< std::endl;
      sSender_.sendHeader (pin.value.p);
      break;
    case(SYSUPDATE_PTR):
    		std::cout << "SerialDispatcher::step SYSUPDATA_PTR enter"<< std::endl;
      sSender_.sendSysStatus (pin.value.p);
      break;
    case(PUK_DATA_PTR):
		std::cout << "SerialDispatcher::step PUK_DATA_PTR enter"<< std::endl;
      sSender_.sendPukData (pin.value.p);
      break;
  }
  std::cout << "SerialDispatcher::step exit"<< std::endl;
};
