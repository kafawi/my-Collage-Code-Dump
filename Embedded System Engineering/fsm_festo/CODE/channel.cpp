/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/* 
 * File:   Channel.cpp
 * Author: kafa
 * 
 * Created on May 22, 2017, 3:30 AM
 */

#include "channel.h"

#include <unistd.h>
#include <iostream>


PulseChannel::PulseChannel ()
#if defined(__QNXNTO__)
{

	 if ((cid_ = ChannelCreate(0)) == -1){
		 std::perror("ChannelCreate() failed.");
     }


     if ((con_ = ConnectAttach(0, 0, cid_, 0, 0)) == -1){
    	 std::perror("ConnectAttach() failed.");
	 }
}
#else
: sem_size_ ()
, queue_ ()
, mtx_ () { }
#endif 
PulseChannel::~PulseChannel ()
{
#if defined(__QNXNTO__)
  if ((con_ = ConnectDetach(con_)) <0 ){
	  std::perror("ConnectDetach failed ");
  }
  if ((cid_ = ChannelDestroy (cid_))==-1)
  {
    std::perror ("ERROR: ChannelCreate failed");
  }
#else
  sem_size_.destroy ();
#endif 
};


PulseReceiver::PulseReceiver (PulseChannel & ch) : chin_ (&ch) { }
Pulse_t
PulseReceiver::pull ()
{
  Pulse_t ret;
  if(chin_)
  {
    ret =chin_->dequeue ();
  }
  else
  {
     std::cerr << "Receiver is not connected to channel" << std::endl;
  }
  return ret;
}

void
PulseReceiver::connect (PulseChannel & ch)
{
  chin_ = &ch;
}
void
PulseReceiver::disconnect ()
{
  chin_ = nullptr;
}
PulseChannel *
PulseReceiver::getChannel ()
{
  return chin_;
}
// --------------------------------------------------------------- Transmitter
PulseTransmitter::PulseTransmitter (PulseChannel &ch) : chout_ (&ch) {

}
void
PulseTransmitter::push (Pulse_t element)
{
  if (chout_)
  {
    chout_->enqueue (element);
  }
  else
  {
    std::cerr << "Transmitter is not connected to channel" << std::endl;
  }
}
void
PulseTransmitter::connect (PulseChannel & ch)
{
  chout_ = &ch;
}
void
PulseTransmitter::disconnect ()
{
  chout_ = nullptr;
}

PulseChannel *
PulseTransmitter::getChannel ()
{
  return chout_;
}
