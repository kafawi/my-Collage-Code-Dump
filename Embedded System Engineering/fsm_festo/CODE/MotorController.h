/**
 * @brief provisional motor controll stub
 * @author Lennart Hartmann
 * @version 31.05.2017
 */
#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H
#include "channel.h"
#include "timerController.h"

class MotorController
{
 public:
  MotorController();
  virtual ~MotorController();
  void suspend(bool susp);
  void setSpeed(Speed sp);
  void reportException();
  void reportExceptionCleared();
 protected:
 private:
  bool running;
  Speed speedBeforeException;
  PulseTransmitter trans_;
  Pulse_t pout_;
};

#endif // MOTORCONTROLLER_H



