#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "channel.h"

class Controller
{
  public:
    Controller(int code, PulseChannel *ch);
    virtual ~Controller();
  private:
    PulseTransmitter toActor_;
    Pulse_t pout_;
}

class WarningLightsCtrl: public Controller
{
  public:
    
    WarningLightsCtrl();
    virtual ~WarningLightsCtrl();
}

class ButtonLightsCtrl: public Controller
{
  public:
    
    WarningLightsCtrl();
    virtual ~WarningLightsCtrl();
}

class GateCtrl; public Controller
{
  public:
    
    GateCtrl();
    virtual ~GateCtrl();
}

class ConveyorCtrl : public Controller
{
  public:
    
    ConveyorCtrl();
    virtual ~ConveyorCtrl();
}



#endif /* _CONTROLLER_H */