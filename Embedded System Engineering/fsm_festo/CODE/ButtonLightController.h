#ifndef BUTTONLIGHTCONTROLLER_H
#define BUTTONLIGHTCONTROLLER_H


#include "channel.h"
class ButtonLightController
{
 public:
  ButtonLightController();
  virtual ~ButtonLightController();
  void reportStartPressed();
  void reportStopPressed();
  void reportQ1Pressed();
  void reportQ2Pressed();
  void reportEStopOn();
  void reportEstopOff();
 protected:
 private:
  PulseTransmitter trans_;
  Pulse_t pout_;
  bool onIluminated;
  bool q1Iluminated;
  bool q2Iluminated;
};

#endif // BUTTONLIGHTCONTROLLER_H
