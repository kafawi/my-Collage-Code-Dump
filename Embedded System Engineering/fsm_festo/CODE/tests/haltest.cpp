

#include "../hal.h"
#include "../channel.h"
#include "../sPulse.h"
#include "../thread.h"
/*
PulseChannel chDigital;
PulseChannel chAnalog;

void
doMcl ()
{
  bool isRunning = true;
  Pulse_t pin;
  Pulse_t pout;
  
  /*
  while (isRunning)
  {
    pin = chDigital.dequeue ();
    switch (pin.code)
    {
      case(GATE):
        
        break;
    }
  }
   */
//}
/*
void
testHal ()
{
  Hal* hal = Hal::getInstance ();


  hal->setChDigitalSensorOut (&chDigital);
  hal->setChAnalogSensorOut (&chAnalog);
  
  Thread mcl(doMcl);
  hal->init();
  Pulse_t pulse = {0,12};
  
  hal->getChActorIn ()->enqueue (pulse);
  
  pulse.code = 1;
  
  hal->getChActorIn ()->enqueue (pulse);
  
  mcl.join ();
  hal->destroy ();
  
}
*/
