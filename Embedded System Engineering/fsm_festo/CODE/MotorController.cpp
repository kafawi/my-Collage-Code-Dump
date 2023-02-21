/**
 * @brief provisional motor controll stub
 * @author Lennart Hartmann
 * @version 31.05.2017
 */
#include <iostream>
#include "MotorController.h"
#include "mcl.h"
#include "HAL_commands.h"
#include "timerController.h"

using namespace std;
//Stub
MotorController::MotorController()
: running(false)
, speedBeforeException(FAST)
, trans_(*(Mcl::getInstance ()->getChActorOut ()))
, pout_()
{
  pout_.code= MOTOR;

}
MotorController::~MotorController(){}
void MotorController::suspend(bool susp){
    if(susp){
      pout_.value.i=MOTOR_OFF;
      TimerController::speedUpdate (STOP);
        cout << "stopping conveyor" << endl;
        cout << "stopping timers" << endl;
    }else{
      pout_.value.i=MOTOR_ON;
      TimerController::speedUpdate (speedBeforeException);
        cout << "resuming operation at previous speed" << endl;
        cout << "resuming timers" << endl;
    }
    trans_.push (pout_);
}
void
MotorController::setSpeed(enum Speed sp)
{
  cout << "MotorController::setSpeed to sp " << sp << " speedBeforeException " << speedBeforeException << endl;
  speedBeforeException=sp;
  cout << "MotorController::setSpeed to sp " << sp << " speedBeforeException " << speedBeforeException << endl;
  switch(sp){
    case (SLOW):
      pout_.value.i=MOTOR_SLOW;
      TimerController::speedUpdate (SLOW);
      cout << "set speed to slow" << endl;
      break;
    case (FAST):
      pout_.value.i=MOTOR_FAST;
      TimerController::speedUpdate (FAST);
      cout << "set speed to fast" << endl;
      break;
    case(STOP):
      pout_.value.i=MOTOR_OFF;
      TimerController::speedUpdate (STOP);
      cout << "stopping motor" << endl;
      break;
    default: 
      cout << "i do not understand motor" << endl;  
    }
  trans_.push (pout_);
}
void MotorController::reportException(){
    cout << "exception detected" << endl;
    suspend(true);
}
void MotorController::reportExceptionCleared(){
    cout << "exception cleared" << endl;
    suspend(false);
}

