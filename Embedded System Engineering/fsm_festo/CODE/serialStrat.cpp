/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialStrat.cpp
 * Author: kafa
 * 
 * Created on June 21, 2017, 11:09 AM
 */



#include "serialStrat.h"
#include "Serial_commands.h"
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

#include "channel.h"
#include "thread.h"
#include "Serial_commands.h"
#include "Serial_protocol.h"
#include "mcl.h"
#include "Data.h"
SWChannel<void *> chout (30);
SWChannel<void *> chin (30);
SWChannel<int> chackin(20);
SWChannel<int> chackout(20);
class SerialMock: public Stoppable{
private:
  Thread *th_;
  Worker *wo_;
public: 
  void step(){
    //static Data * data = Mcl::getInstance ()->getData ();
    Header *h;
    h = (Header *)chout.dequeue ();
    chackout.enqueue (PKG_ACK);
    switch(h->type){
      case(SYSUPDATE_PKT): { 
        chout.dequeue (); 
        chackout.enqueue (PKG_ACK);
      }
        break;
      case(PUKDATA_PKT): {
        chout.dequeue (); 
        chackout.enqueue (PKG_ACK);
      }
        break;
    }    
  }
  SerialMock( )
  : th_(nullptr)
  , wo_(nullptr)
  {
    wo_ = new Worker(*(this));
    th_ = new Thread(*(wo_));
  }
  ~SerialMock(){
   terminate();
   th_->join();
   delete (th_);
   delete (wo_);  
  }
};
SerialMock mock();
//bool isConnected = false;
bool isConnected = true;
SerialStrat::SerialStrat ()
{
  std::cout << "SerialStrat ctor" << std::endl;
#if defined(__QNXNTO__)
#else  
#endif
}
SerialStrat::~SerialStrat () 
{
#if defined(__QNXNTO__)
#else
#endif
}
int
SerialStrat::sendPkg (int const &fdesc, void *pkg, size_t size)
{
  int ret = 0;
#if defined(__QNXNTO__)
  if (isConnected){
	  std::cout << "SerialStrat::sendPkg vorher"<< std::endl;
	  if (pkg == nullptr){
		  std::cout << "pkg is nullptr"<< std::endl;
	  }
	  ret = write (fdesc, pkg, size);
	  std::cout << "SerialStrat::sendPkg danach"<< std::endl;
	   if (ret != size)
	   {
	     std::perror ("sending failed");
	   }
	   std::cout << "HIERERERERE" << std::endl;
	   std::cout << "ret   " << ret << std::endl;
  } else {
	  if (size  == sizeof(int8_t)){
	      int ack = (long)pkg;
	      chackout.enqueue (ack);
	    } else {
	       chout << pkg;
	    }
  }

#else 
  if (size  == sizeof(int8_t)){
    int ack = (long)pkg;
    chackout.enqueue (ack);
  } else {
     chout << pkg;
  }
#endif
  return ret;
}
int
SerialStrat::recvPkg (int const &fdesc, void *pkg, size_t size, int maxWaitTime)
{
  int ret = 0;
#if defined(__QNXNTO__)
  if (isConnected){
  ret = readcond (fdesc, pkg, size, size, 0, maxWaitTime);
  if (ret != 0)
  {
    //fail 
  }
  } else {
	  if (size  == sizeof(int8_t)){
	     // int ack = chackin.dequeue ();
	    chackin.dequeue ();
	    } else {
	    pkg << chin;
	    }
  }
#else 
  if (size  == sizeof(int8_t)){
   // int ack = chackin.dequeue ();
  chackin.dequeue ();
  } else {
  pkg << chin;
  }
#endif
  //std::cout << "ich schicke ein packet" << std::endl;
  return ret;
}
void
SerialStrat::config (int &fdesc, const char* dev)
{
#if defined(__QNXNTO__)
  fdesc = open (dev, O_RDWR);
  if (fdesc == -1)
  {
    exit (-1);
  }
  struct termios ts;
  tcflush (fdesc, TCIOFLUSH);
  tcgetattr (fdesc, &ts);
  cfsetispeed (&ts, B19200);
  cfsetospeed (&ts, B19200);
  ts.c_cflag &= ~CSIZE;
  ts.c_cflag &= ~CSTOPB;
  ts.c_cflag &= ~PARENB;
  ts.c_cflag |= CS8;
  ts.c_cflag |= CREAD;
  ts.c_cflag |= CLOCAL;
  tcsetattr (fdesc, TCSANOW, &ts);
#endif

}
