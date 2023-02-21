/*
 * SerialReceiver.cc
 *
 *  Created on: 08.06.2017
 *      Author: abs430
 */

#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include "serialReceiver.h"
#include "Serial_protocol.h"
#include "sio.h"
#include "replayLogger.h"
SerialReceiver::SerialReceiver ()
: trans_ (*(Sio::getInstance ()->getChEventOut ()))
, strat_ ()
, dev_ (DEVIN)
, fdesc_ (-1)
{
  strat_.config (fdesc_, dev_);
  std::cout << "SerialReceiver ctor" << std::endl;
}
void
SerialReceiver::step ()
{
  static Header h;
  Pulse_t pout;

  int ret;
  ret = strat_.recvPkg (fdesc_, &h, sizeof (Header), FOREVERTIME);
  if (ret != sizeof (Header))
  {
    pout.code = INSTANT_BACK;
    pout.value.i = HEADER_DISCONNECT;
  }
  else
  {
    int8_t ack = PKG_ACK;
    ret = strat_.sendPkg (fdesc_, &ack, sizeof (ack));
    switch (h.type)
    {
      case(SYSUPDATE_PKT):
      {
        SysUpdate su;
        ret = strat_.recvPkg (fdesc_, &su, sizeof (SysUpdate), ACKTIME);
        if (ret != sizeof (SysUpdate))
        {
          pout.code = INSTANT_BACK;
          pout.value.i = SYSUPDATE_DISCONNECT;
        }
        else
        {
          ret = strat_.sendPkg (fdesc_, &ack, sizeof (ack));
          pout.code = SYSUPDATE_INCOMMING;
          //pout.value.p = su;
          pout.value.i = su.signal;
        }
      }
        break;
      case(PUKDATA_PKT):
      {
        PukData pd;
        ret = strat_.recvPkg (fdesc_, &pd, sizeof (PukData), ACKTIME);
        if (ret != sizeof (PukData))
        {
          pout.code = INSTANT_BACK;
          pout.value.i = PUKDATA_DISCONNECT;
        }
        else
        {
          ret = strat_.sendPkg (fdesc_, &ack, sizeof (ack));
          pout.code = PUKDATA_INCOMMING_ID;
          std::cout << pd.puk_id << " " <<  pd.puk_type << " " << pd.height1 << " " << pd.height2 << " " << pd.eject << std::endl;
          pout.value.i = static_cast<int>(pd.puk_id);
          LOG_REPLAY_PULSE (SERIELL, pout)
          trans_.push (pout);
          pout.code = PUKDATA_TYPE;
          pout.value.i = static_cast<int>(pd.puk_type);
          LOG_REPLAY_PULSE (SERIELL, pout)
          trans_.push (pout);
          pout.code = PUKDATA_HEIGHT_1;
          pout.value.i = static_cast<int>(pd.height1);
          LOG_REPLAY_PULSE (SERIELL, pout)
          trans_.push (pout);
          pout.code = PUKDATA_HEIGHT_2;
          pout.value.i = static_cast<int>(pd.height2);
          LOG_REPLAY_PULSE (SERIELL, pout)
          trans_.push (pout);
          pout.code = PUKDATA_END_EJACT;
          pout.value.i = static_cast<int>(pd.eject);
        }
      }
        break;
    }
    LOG_REPLAY_PULSE (SERIELL, pout)
    trans_.push (pout);
  }
}
SerialReceiver::~SerialReceiver ()
{
  // Close File descriptor
  if (close (this->fdesc_) < 0)
  {
    exit (-1);
  }
}
