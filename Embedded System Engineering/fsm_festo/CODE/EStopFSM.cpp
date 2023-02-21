/**
 * @brief FSM controlling behaviour if emergency stop has to be resolved
 * @author Lennart Hartmann
 * @version 07.06.2017
 */
#include "EStopFSM.h"
#include "SystemOffFSM.h"
#include "MotorController.h"
#include "WarningLightsController.h"
#include "Pukmanager.h"
#include "SerialManager.h"
#include "serialController.h"
#include <iostream>
#include <string>
#include <ctime>
#include <ratio>


using namespace std;

// Superstate ////////////////////////////////////////////
string
EStopFSM::EStopState::getName ()
{
  return "EStopFSM Superstate";
}
void
EStopFSM::EStopState::reportEStopPressed () {
   cout<<"\n"<< this->getName()<<": reportEStopPressed / - \n";
}
void
EStopFSM::EStopState::reportEStopReleased () {
   cout<<"\n"<< this->getName() <<": reportEStopReleased / -\n";
}
void
EStopFSM::EStopState::reportResetPressed () {
    cout<<"\n"<< this->getName() <<": reportResetPressed / -\n";
}
void
EStopFSM::EStopState::reportEStopAntiPrellTimer () {
    cout<<"\n"<< this->getName()<<": reportEStopPressed / - \n";
}



// State Ok /////////////////////////////////////////////////////////
string
EStopFSM::Ok::getName ()
{
  return "System ok";
}
void
EStopFSM::Ok::reportEStopPressed ()
{
  cout<<"\n"<< this->getName()<<": reportEStopPressed -> EStoppedBeforAntiPrellTimer \n";
  data->motorCntr->reportException ();
  //todo real channel
  cout << "Channel <- E_STOPPED" << endl;
  data->EStopped = true;
  //todo WarningLightsController class
  cout << "warningLightsController->setFlashFast(true)" << endl;
  data->serialMsgMan->sendSysStatusUpdate (ERROR_PENDING_NO_ACK);
  cout << "after sending" << endl;
  data->warningLights->setFlashFast (true);
  cout << "after warninglights" << endl;
  data->timerCtrl->resetTimer (data->antiEstopPrellTimer, ESTOP_ANTI_PRELL_TIMER);
  cout << "after AntiPrellTimer start" << endl;
  new (this) EStoppedBeforAntiPrellTimer;
};

// State EStopped //////////////////////////////////////////////////
string
EStopFSM::EStoppedBeforAntiPrellTimer::getName ()
{
  return "EStoppedBeforAntiPrellTimer";
};

void 
EStopFSM::EStoppedBeforAntiPrellTimer::reportEStopAntiPrellTimer()
{
  cout<<"\n"<< this->getName()<<": reportEStopAntiPrellTimer -> EStopped \n";
  new (this) EStopped;
}

string
EStopFSM::EStopped::getName ()
{
  return "EStopped";
};

void EStopFSM::EStopped::reportEStopReleased(){
	cout<<"\n"<< this->getName()<<": reportEStopReleased -> AcknoledgedBeforAntiPrellTimer \n";
    //cout <<  "warningLightsController->setFlashFast(false)" << endl;
    data->warningLights->setFlashFast(false);
    //cout <<  "warningLightsController->setRed(true)" << endl;
    data->serialMsgMan->sendSysStatusUpdate(ERROR_PENDING_ACK);
    data->timerCtrl->resetTimer (data->antiEstopPrellTimer, ESTOP_ANTI_PRELL_TIMER);
    new (this) AcknoledgedBeforAntiPrellTimer;
}
// STATE AcknoledgedBeforAntiPrellTimer
string
EStopFSM::AcknoledgedBeforAntiPrellTimer::getName ()
{
  return "Error AcknoledgedBeforAntiPrellTimer";
};
void
EStopFSM::AcknoledgedBeforAntiPrellTimer::reportEStopAntiPrellTimer () 
{
  cout<<"\n"<< this->getName()<<": reportEStopAntiPrellTimer -> Acknoledged \n";
  data->warningLights->setRed(true);
  new (this) Acknoledged;
 };

// State Acknoledged ///////////////////////////////////////////////
string
EStopFSM::Acknoledged::getName ()
{
  return "Error Acknoledged";
};
void
EStopFSM::Acknoledged::reportEStopPressed ()
{
  cout<<"\n"<< this->getName()<<": reportEStopPressed -> EStoppedBeforAntiPrellTimer \n";
  //cout <<  "warningLightsController->setRed(false)" << endl;
  data->warningLights->setRed (false);
  //cout <<  "warningLightsController->setFlashFast(true)" << endl;
  data->warningLights->setFlashFast (true); 
  data->timerCtrl->resetTimer (data->antiEstopPrellTimer, ESTOP_ANTI_PRELL_TIMER);
  new (this) EStoppedBeforAntiPrellTimer;
}
void
EStopFSM::Acknoledged::reportResetPressed ()
{
  cout<<"\n"<< this->getName()<<": reportResetPressed -> Ok \n";
  if (!data->pukMngr->isEmpty ())
  {
    data->motorCntr->reportExceptionCleared ();
  }
  //cout <<  "warningLightsController->setRed(false)" << endl;

  data->warningLights->setRed (false);
  data->EStopped = false;
  //todo address real Chanel
  cout << "Channel <- E_STOPP_CLEARED" << endl;
  new (this) Ok;
}



// Public functions ////////////////////////////////////////
EStopFSM::EStopFSM () : statePtr (&stateMember), contextdata ()
{
  statePtr->data = contextdata;
  cout << "EStopFSM instanciated" << endl;
}
EStopFSM::EStopFSM (Data *mydata) : statePtr (&stateMember), contextdata ()
{
  statePtr->data = mydata;
  cout << "EStopFSM instanciated" << endl;
}
EStopFSM::~EStopFSM ()
{
  cout << "EStopFSM destroyed" << endl;
}

//passing function call to fsm
string
EStopFSM::getName ()
{
  return statePtr->getName ();
}
void
EStopFSM::reportEStopPressed ()
{
  statePtr->reportEStopPressed ();
}
void
EStopFSM::reportEStopReleased ()
{
  statePtr->reportEStopReleased ();
}
void
EStopFSM::reportResetPressed ()
{
  statePtr->reportResetPressed ();
}
void
EStopFSM::reportEStopAntiPrellTimer ()
{
  statePtr->reportEStopAntiPrellTimer ();
}
//int main(){
//    cout << "EStopFsm ver 1.0" << endl;
//    EStopFSM *eStopFsm = new EStopFSM();
//    cout <<"\ntest regular" << endl;
//    cout << "\npress EStop" << endl;
//    eStopFsm->reportEStopPressed();
//    cout << "\nrelease EStop" << endl;
//    eStopFsm->reportEStopReleased();
//    cout << "\npress EStop" << endl;
//    eStopFsm->reportEStopPressed();
//    cout << "\npress Reset"<< endl;
//    eStopFsm->reportResetPressed();
//    cout << "\nrelease EStop" << endl;
//    eStopFsm->reportEStopReleased();
//    cout << "\npress Reset"<< endl;
//    eStopFsm->reportResetPressed();
//    delete eStopFsm;
//}
