/*
 * halDipatcher.cpp
 *
 *  Created on: Jun 1, 2017
 *      Author: kafa
 */
#include <iostream>

#include "halDispatcher.h"
#include "hal.h"
#include "HAL_commands.h"
#include "actor.h"
void
HalDispatcher::loop ()
{
  Pulse_t pin;
  pin = receiver_.pull ();
  switch (pin.code)
  {
    case(MOTOR):
      switch (pin.value.i)
      {
        case(MOTOR_ON):
          portStrat_.toggleBitOn (portStrat_.portA, MOTOR_RIGHT_HI_OUT);
          portStrat_.toggleBitOff (portStrat_.portA, MOTOR_STOP_HI_OUT);
          break;
        case(MOTOR_OFF):
          portStrat_.toggleBitOff (portStrat_.portA,
                                   MOTOR_RIGHT_HI_OUT | MOTOR_LEFT_HI_OUT);
          portStrat_.toggleBitOn (portStrat_.portA, MOTOR_STOP_HI_OUT);
          break;
        case(MOTOR_SLOW):
          portStrat_.toggleBitOn (portStrat_.portA, MOTOR_SLOW_HI_OUT);
          break;
        case(MOTOR_FAST):
          portStrat_.toggleBitOff (portStrat_.portA, MOTOR_SLOW_HI_OUT);
          break;
      }
      break;
    case(GATE):
      switch (pin.value.i)
      {
        case(GATE_OPEN):
          portStrat_.toggleBitOn (portStrat_.portA, GATE_OPEN_HI_OUT);
          break;
        case(GATE_CLOSE):
          portStrat_.toggleBitOff (portStrat_.portA, GATE_OPEN_HI_OUT);
          break;
      }
      break;
    case(STATUS_LIGHTS):
      switch (pin.value.i)
      {
        case(GREEN_OFF):
          portStrat_.toggleBitOff (portStrat_.portA, WS_GREEN_ON_HI_OUT);
          break;
        case(GREEN_ON):
          portStrat_.toggleBitOn (portStrat_.portA, WS_GREEN_ON_HI_OUT);
          break;
        case(RED_OFF):
          portStrat_.toggleBitOff (portStrat_.portA, WS_RED_ON_HI_OUT);
          break;
        case(RED_ON):
          portStrat_.toggleBitOn (portStrat_.portA, WS_RED_ON_HI_OUT);
          break;
        case(YELLOW_OFF):
          portStrat_.toggleBitOff (portStrat_.portA, WS_YELLOW_ON_HI_OUT);
          break;
        case(YELLOW_ON):
          portStrat_.toggleBitOn (portStrat_.portA, WS_YELLOW_ON_HI_OUT);
          break;
        case(ALL_LIGHTS_OFF):
          portStrat_.toggleBitOff (
                                   portStrat_.portA,
                                   WS_GREEN_ON_HI_OUT | WS_YELLOW_ON_HI_OUT | WS_RED_ON_HI_OUT
                                   );
          break;
      }
      break;
    case(BUTTON_LIGHTS):
      switch (pin.value.i)
      {
        case(LED_START_OFF):
          portStrat_.toggleBitOff (portStrat_.portC, LED_START_HI_OUT);
          break;
        case(LED_START_ON):
          portStrat_.toggleBitOn (portStrat_.portC, LED_START_HI_OUT);
          break;
        case(LED_RESET_OFF):
          portStrat_.toggleBitOff (portStrat_.portC, LED_RESET_HI_OUT);
          break;
        case(LED_RESET_ON):
          portStrat_.toggleBitOn (portStrat_.portC, LED_RESET_HI_OUT);
          break;
        case(LED_Q1_OFF):
          portStrat_.toggleBitOff (portStrat_.portC, LED_Q1_HI_OUT);
          break;
        case(LED_Q1_ON):
          portStrat_.toggleBitOn (portStrat_.portC, LED_Q1_HI_OUT);
          break;
        case(LED_Q2_OFF):
          portStrat_.toggleBitOff (portStrat_.portC, LED_Q2_HI_OUT);
          break;
        case(LED_Q2_ON):
          portStrat_.toggleBitOn (portStrat_.portC, LED_Q2_HI_OUT);
          break;
      }
      break;
    case(PROFILOMETER):
      switch (pin.value.i)
      {
        case(START_SAMPLING):
		std::cout << "\n\n\n\n SESNOR STart\n\n\n -------------------- \n\n\n";
          sensor_.startAnalog ();
          break;
        case(PAUSE_SAMPLING):
          sensor_.pauseAnalog ();
          break;
        case(END_SAMPLING):
          std::cout << "\n\n\n\n SESNOR STOIPPED\n\n\n -------------------- \n\n\n";
          sensor_.stopAnalog ();
          break;
        case(CONTINUE_SAMPLING):
          sensor_.continueAnalog ();
          break;
      }
      break;
    case(HAL_CONTROL):
      switch (pin.value.i)
      {
        case(KILL_HAL):
          std::cout << "Schoenen Tag noch!" << std::endl;
          sensor_.terminate ();
          this->terminate ();
          break;
        case(RESET_HAL):
          // TODO set all Values to default
          break;
        case(STOP_IRQ):
          sensor_.stopIRQ ();
          break;
        case(CONTINUE_IRQ):
          sensor_.startIRQ ();
      }
      break;
  }
}
HalDispatcher::HalDispatcher ()
: receiver_ (*(Hal::getInstance ()->getChActorIn ()))
, portStrat_ ()
, sensor_ ()
{ // TODO Auto-generated constructor stub
  std::cout << "hal dispatcher ctor" << std::endl;
}
HalDispatcher::~HalDispatcher () {
  // TODO Auto-generated destructor stub
}

