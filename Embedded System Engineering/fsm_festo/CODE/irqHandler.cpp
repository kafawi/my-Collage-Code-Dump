/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "irqHandler.h"
#include "digitalPortStrat.h"
#include "hal.h"

#include <iostream>
#include <cstdlib>
#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <hw/inout.h>
#endif
#include <chrono>
#include <string>

#include "MCL_signals.h"
#include "gpio.h"
#include "mgt.h"


#if defined(__QNXNTO__)
#define PORTC_SEN_MASK 0b11110000
int isrChann = 0;
int isrConnect = 0;
int isrId = 0;
typedef struct
{
  int EventEnum;
  int massage;
  int id;
} Event;
struct sigevent isrEvent;

unsigned char portB_value_old = 0;
unsigned char portc_value_old = 0;
bool portb_isSet[8];
bool portc_isSet[8];

void 
getPortSet(bool port_isSet[], unsigned char portValue)
{
  for (int i =0; i < 8; i++)
  {
    port_isSet[i] = (((portValue<<i)&1)==1);
  }
}

const struct sigevent*
ISR_DIO (void* arg, int id)
{
  struct sigevent* event = (struct sigevent*)arg;
  out8 (0x30F, 0);
  // next 3 lines should be atomic
  unsigned char portb_value = in8 (PORTB_ADDR);
  unsigned char changed_valueb = portb_value ^ portB_value_old;
  portB_value_old = portb_value;
  // next 3 lines should be atomic
  unsigned char portc_value = in8 (PORTC_ADDR) & PORTC_SEN_MASK;
  unsigned char changed_valuec = portc_value ^ portc_value_old;
  portc_value_old = portc_value;
  // guarateee, that if uninterseting message, we dont report the mcl
  event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE +1;
  
  if ( changed_valueb ){
    switch (changed_valueb)
    {
    case (POSITION_ENTRY_LO_IN):
      if (!(portb_value & POSITION_ENTRY_LO_IN))
      {
//        if(portb_isSet[POSITION_ENTRY_BIT_POS]){
//          portb_isSet[POSITION_ENTRY_BIT_POS] = false;
          event->sigev_value.sival_int = NEWPUK;
          event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
//        }
      }
      else
      {
//        if(!portb_isSet[POSITION_ENTRY_BIT_POS]){
//          portb_isSet[POSITION_ENTRY_BIT_POS] = true;
          event->sigev_value.sival_int = LEAVING_ENTRY;
          event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
//        }
      }
      break;
    case (POSITION_PD_LO_IN):
      if (!(portb_value & POSITION_PD_LO_IN))
      {
//        if(portb_isSet[POSITION_PD_BIT_POS]){
//          portb_isSet[POSITION_PD_BIT_POS] = false;
          event->sigev_value.sival_int = ENTER_PROFILE_DETECTION;
          event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
//        }
      }
      else
      {
//        if(portb_isSet[POSITION_PD_BIT_POS]){
//          portb_isSet[POSITION_PD_BIT_POS] = true;
          event->sigev_value.sival_int = LEAVING_PROFILE_DETECTION;
          event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
//        }
      }
      break;
    case (PD_ACCEPT_LO_IN):
      if (!(portb_value & PD_ACCEPT_LO_IN))
         {
           event->sigev_value.sival_int = REGULAR;
           event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
         }
      break;
    case (POSITION_GATE_LO_IN):
      if (!(portb_value & POSITION_GATE_LO_IN))
      {
        event->sigev_value.sival_int = ENTER_METAL_DETECTION;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
        event->sigev_value.sival_int = LEAVING_METAL_DETECTION;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      break;
    case (METAL_DETECTION_HI_IN):
      if (portb_value & METAL_DETECTION_HI_IN)
      {
        event->sigev_value.sival_int = METAL_DETECTED;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
      }
      break;
    case (GATE_IS_OPEN_HI_IN):
//      if (portb_value & GATE_IS_OPEN_HI_IN)
//      {
//        event->sigev_value.sival_int = GATE_OPENED;
//      }
//      else
//      {
//        event->sigev_value.sival_int = GATE_CLOSED;
//      }
      break;
    case (POSITION_SLITE_LO_IN):
      if (!(portb_value & POSITION_SLITE_LO_IN))
      {
        event->sigev_value.sival_int = RAMP_BLOCKED;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
        event->sigev_value.sival_int = RAMP_FREED;
    	event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      break;
    case (POSITION_OUTLET_LO_IN):
      if (!(portb_value & POSITION_OUTLET_LO_IN))
      {
        event->sigev_value.sival_int = REACHED_EXIT;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
        event->sigev_value.sival_int = LEAVING_EXIT;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      break;
    }
  } else if ( changed_valuec ){

    switch (changed_valuec)
  {
    case (BUTTON_START_HI_IN):
      if (portc_value & BUTTON_START_HI_IN)
      {
        event->sigev_value.sival_int = START_BTN;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
      }
      break;
    case (BUTTON_STOP_LO_IN):
      if (!(portc_value & BUTTON_STOP_LO_IN))
      {
        event->sigev_value.sival_int = STOP_BTN;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
      }
      break;
    case (BUTTON_RESET_HI_IN):
      if (portc_value & BUTTON_RESET_HI_IN)
      {
        event->sigev_value.sival_int = RESET_BTN;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      break;
    case (BUTTON_ESTOP_LO_IN):
      if (!(portc_value & BUTTON_ESTOP_LO_IN))
      {
        event->sigev_value.sival_int = E_STOP_PRESSED;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      else
      {
        event->sigev_value.sival_int = E_STOP_RELEASED;
        event->__sigev_un2.__st.__sigev_code = INCOMMING_CODE;
      }
      break;
    }
  }
  return event;
}

#endif
void
IrqHandler::signIn (void)
{
#if defined(__QNXNTO__)
  out8 (0x30F, 0);
  out8 (0x30B, 0b111001); //Writing a "zero" enables the port;
  SIGEV_PULSE_INIT (&isrEvent, isrConnect, SIGEV_PULSE_PRIO_INHERIT, 0, 0);
  // TODO 11 -> ISR_NO
  isrId = InterruptAttach (11, ISR_DIO, &isrEvent, sizeof (isrEvent), 0);
  if (isrId == -1)
  {
    exit (EXIT_FAILURE);
  }
  portB_value_old = in8 (PORTB_ADDR);
  portc_value_old = in8 (PORTC_ADDR) & PORTC_SEN_MASK;
  getPortSet(portb_isSet, portB_value_old);
  getPortSet(portc_isSet, portc_value_old);
#endif
}

void
IrqHandler::signOut(void)
{
#if defined(__QNXNTO__)
  if (InterruptDetach (isrId) == -1)
  {
    exit (EXIT_FAILURE);
  }
  out8 (0x30B, 0b11111111);
  out8 (0x30F, 0);
#endif
}
IrqHandler::IrqHandler ()
: transmitter_ (*(Hal::getInstance ()->getChDigitalSensorOut ()))
, portStrat_ ()
, irqChid_ (0)
, irqChcon_ (0)
{
#if defined(__QNXNTO__)
  if ((isrChann = ChannelCreate (0)) == -1)
  {
    exit (EXIT_FAILURE);
  }

  if ((isrConnect = ConnectAttach (0, 0, isrChann, 0, 0)) == -1)
  {
    exit (EXIT_FAILURE);
  }
  irqChid_ = isrChann;
  irqChcon_ = isrConnect;

  out8 (0x30F, 0);
  out8 (0x30B, 0b111001); //Writing a "zero" enables the port;
  SIGEV_PULSE_INIT (&isrEvent, isrConnect, SIGEV_PULSE_PRIO_INHERIT, 0, 0);
  isrId = InterruptAttach (11, ISR_DIO, &isrEvent, sizeof (isrEvent), 0);
  if (isrId == -1)
  {
    exit (EXIT_FAILURE);
  }
  portB_value_old = in8 (PORTB_ADDR);
  portc_value_old = in8 (PORTC_ADDR) & PORTC_SEN_MASK;
  getPortSet(portb_isSet, portB_value_old);
  getPortSet(portc_isSet, portc_value_old);
#endif
}
IrqHandler::~IrqHandler ()
{
#if defined(__QNXNTO__)
  if (InterruptDetach (isrId) == -1)
  {
    exit (EXIT_FAILURE);
  }
  out8 (0x30B, 0b11111111);
  out8 (0x30F, 0);

  if (ConnectDetach (isrConnect) == -1)
  {
    exit (EXIT_FAILURE);
  }

  if (ChannelDestroy (isrChann) == -1)
  {
    exit (EXIT_FAILURE);
  }
#endif
}
#include "replayLogger.h"

void
IrqHandler::loop ()
{
  // TODO from intern Channel to transmitter
#if defined(__QNXNTO__)
  struct _pulse pulse;
  MsgReceivePulse (isrChann, &pulse, sizeof (pulse), NULL);
  if (pulse.code ==INCOMMING_CODE)
  {
	std::cout << "irq: MCL_SIG:" << pulse.value.sival_int << std::endl;
    Pulse_t pout;
    pout.code = pulse.code; //INCOMMING_CODE
    pout.value.i = pulse.value.sival_int;
    LOG_REPLAY_PULSE(SENSOR,pout)
      transmitter_.push (pout);
  }
#else
  // do somthing spezial
//  Pulse_t pout;
//  pout.code = INCOMMING_CODE;
//  pout.value.i = NEWPUK;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value.i = LEAVING_ENTRY;
//  transmitter_.push (pout);
//
//  pout.value.i = TO_PROFILE_DETECTION_MIN;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value.i = ENTER_PROFILE_DETECTION;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value.i = LEAVING_PROFILE_DETECTION;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = ENTER_PROFILE_DETECTION;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = REGULAR;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = LEAVING_PROFILE_DETECTION;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = ENTER_METAL_DETECTION;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = LEAVING_METAL_DETECTION;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = METAL_DETECTED;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = REACHED_EXIT;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
//  pout.value = LEAVING_EXIT;
//  transmitter_.push (pout);
//  mgt::threadSleep (1000);
 // this->terminate ();
  #endif
}