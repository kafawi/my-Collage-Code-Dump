/**
 * @brief FSM controlling metal detection and gate operation
 * @author Lennart Hartmann
 * @version 05.06.2017
 */

#include "GateManager.h"
#include "mcl.h"
#include "Pukmanager.h"
#include "PukSequenceTracker.h"
#include "GateController.h"
#include "MotorController.h"
#include "WarningLightsController.h"
#include "HDI_Manager.h"
#include "serialController.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std;

// the context class may be anything, that has internal states
// and behaves differently depending on the internal state.
// this context class has only one signal for clarity.
// having a hole bunch of signals is common.

//Superstate
string GateManager::State::getName() {
	return "Superstate";
}
void
GateManager::State::reportEnterMetalDetection ()
{
  cout << "\n" << this->getName () << ": EnterMetalDetection / -\n";
}
void
GateManager::State::reportLeavingMetalDetection ()
{
  cout << "\n" << this->getName () << ": LeavingMetalDetection / -\n";
}
void
GateManager::State::reportMintimerToMetalDetectionExpired()
{
    cout << "\n" << this->getName () << ": Mintimer expired / -\n";
}
void
GateManager::State::reportMaxtimerToMetalDetectionExpired()
{
    cout << "\n" << this->getName () << ": Maxtimer expired / -\n";
}
void
GateManager::State::reportMetalDetectionTimeout()
{
    cout << "\n" << this->getName () << ": metal detection deadline / -\n";
}
void
GateManager::State::ignoreTiming()
{
    cout << "\n" << this->getName () << ": trying to cancel error state / -\n";
}
void
GateManager::State::rampBlocked()
{
    cout << "\n" << this->getName () << ": ramp blocked / -\n";
}
void
GateManager::State::rampFreed()
{
    cout << "\n" << this->getName () << ": ramp freed / -\n";
}
void
GateManager::State::reportRampObstructionCleared()
{
    cout << "\n" << this->getName () << ": ramp obstruction / -\n";
}


//State Idle
string
GateManager::Idle::getName()
{
    return "Idle";
}
void
GateManager::Idle::reportEnterMetalDetection()
{
    data->timeError=true;
    data->motorCntr->suspend(true);
    data->warningLights->setFlashFast(true);
    data->hdiMngr->printError(UNEXPECTED_OBJECT_IN_METAL_DETECTION);
    new (this) UntrackedWorkpiece;
}
void
GateManager::Idle::reportMintimerToMetalDetectionExpired()
{
    cout << "MintimerToMetalDetectionExpired" << endl;
    new (this) Ready;
}

//State Ready
string
GateManager::Ready::getName ()
{
  return "Ready";
}
void
GateManager::Ready::reportEnterMetalDetection()
{
    cout << "refreshing PukINGate" << endl;
    data->pukMngr->refreshNextPukInGate();
    data->pukInMetalDetection->maxTimer->isSuspended_ = true;
//	data->timerCtrl->resetTimer(data->metalDetectionWindowTimer,METAL_DETECTION_TIMER);
    if(data->rampBlocked){
        data->rampObstructed=true;
        data->hdiMngr->printError(SLIDE_OBSTRUCTED);
        data->serialMsgMan->sendSysStatusUpdate(RAMP_OBSTRUCTED);
    }
    bool rampsOk = !(data->rampBlocked && data->otherRampObstructed);
    if(rampsOk){
        cout << "setting metal detection Window" << endl;
        data->timerCtrl->resetTimer(data->metalDetectionWindowTimer,METAL_DETECTION_TIMER);
        new (this) Processing;
    }else{
        data->rampsBlockedError=true;
        data->warningLights->setFlashFast(true);
        data->motorCntr->suspend(true);
        data->hdiMngr->printError(BOTH_SLIDES_FULL);
        new (this) RampError;
    }
}
void
GateManager::Ready::reportMaxtimerToMetalDetectionExpired()
{
  data->timeError=true;
  data->motorCntr->suspend(true);
  data->warningLights->setFlashFast(true);
  data->hdiMngr->printError(MISSING_WORKPIECE_IN_PROFILE_DETECTION);
  new (this) MissingWorkpiece;
}

//State Processing
string
GateManager::Processing::getName()
{
	return "Processing";
}
void
GateManager::Processing::reportMetalDetectionTimeout()
{
  bool ok=data->sequenceTracker->getExpected(data->pukInMetalDetection);
  if(ok){
    cout << "opening Gate" << endl;
    data->gateCtrl->open();
    data->timerCtrl->resetTimer(data->gateOpenTimer,GATE_TIMER);
    //data->gateOpenTimer->isSuspended_=false;
    new (this) Done;
  }else{
    cout << "leaving Gate closed" << endl;
//    data->pukMngr->deletePukInGate();
//    if(data->pukMngr->isEmpty()){
//    	data->motorCntr->setSpeed(STOP);
//    }
    new (this) Ejecting;
  }
}

//State Done
string
GateManager::Done::getName()
{
  return "Done";
}
void
GateManager::Done::reportLeavingMetalDetection ()
{
  cout << "leaving metal detection" << endl;
  data->timerCtrl->resetTimer(data->pukInMetalDetection->minTimer,TO_EXIT_MIN);
  data->timerCtrl->resetTimer(data->pukInMetalDetection->maxTimer,TO_EXIT_MAX);
  new (this) Idle;
}

//State UntrackedWorkpiece
string
GateManager::UntrackedWorkpiece::getName ()
{
  return "UntrackedWorkpiece";
}
void
GateManager::UntrackedWorkpiece::ignoreTiming()
{
  bool rampsOk = !(data->rampBlocked && data->otherRampObstructed);
  data->pukMngr->insertPukInGate();
  data->timeError=false;
  if(rampsOk){
    data->motorCntr->suspend(false);
    data->warningLights->setFlashFast(false);
    new (this) Processing;
  }else{
    //keep light flashing
    data->rampsBlockedError=true;
    data->hdiMngr->printError(BOTH_SLIDES_FULL);
    new (this) RampError;
  }
}

//State MissingWorkpiece
string
GateManager::MissingWorkpiece::getName ()
{
  return "MissingWorkpiece";
}
void
GateManager::MissingWorkpiece::ignoreTiming(){
  data->pukMngr->removePukInGate();
  data->timeError=false;
  if(!data->pukMngr->isEmpty()){
    data->motorCntr->suspend(false);
  }
  data->warningLights->setFlashFast(false);
  new (this) Idle;
}

string
GateManager::Ejecting::getName() {
  return "Ejecting";
}

void
GateManager::Ejecting::rampBlocked (){
  data->rampBlocked=true;
  data->pukMngr->deletePukInGate();
  if(data->pukMngr->isEmpty()){
    data->motorCntr->suspend(true);
  }
  new (this) Idle;
}

string
GateManager::RampError::getName() {
  return "RampError";
}

void
GateManager::RampError::rampFreed(){
  data->rampBlocked=false;
  data->rampObstructed=false;
  data->warningLights->setFlashFast(false);
  data->warningLights->setFlashSlow(true);
  data->motorCntr->suspend(false);
  cout << "setting metal detection Window" << endl;
  data->timerCtrl->resetTimer(data->metalDetectionWindowTimer,METAL_DETECTION_TIMER);
  new (this) Processing;
}

void
GateManager::RampError::reportRampObstructionCleared(){
  data->warningLights->setFlashFast(false);
  data->warningLights->setFlashSlow(true);
  data->motorCntr->suspend(false);
  cout << "setting metal detection Window" << endl;
  data->timerCtrl->resetTimer(data->metalDetectionWindowTimer,METAL_DETECTION_TIMER);
  new (this) Processing;
}

void
GateManager::RampError::ignoreTiming(){
  data->warningLights->setFlashFast(false);
  data->warningLights->setRed(true);
  new (this) Achnoledged;
}

string
GateManager::Achnoledged::getName(){
  return "Achnoledged";
}

void
GateManager::Achnoledged::rampFreed(){
  data->rampBlocked=false;
  data->rampObstructed=false;
  data->warningLights->setRed(false);
  data->motorCntr->suspend(false);
  cout << "setting metal detection Window" << endl;
  data->timerCtrl->resetTimer(data->metalDetectionWindowTimer,METAL_DETECTION_TIMER);
  new (this) Processing;
}

void
GateManager::Achnoledged::reportRampObstructionCleared(){
  data->warningLights->setRed(false);
  data->motorCntr->suspend(false);
  cout << "setting metal detection Window" << endl;
  data->timerCtrl->resetTimer(data->metalDetectionWindowTimer,METAL_DETECTION_TIMER);
  new (this) Processing;
}

//functions
GateManager::GateManager ()
: statePtr (&stateMember)
//, contextdata ()
{
  statePtr->data = contextdata; // connecting state->data with the context data
  cout << "---------- new GateManager() ----------------" << endl;
}
GateManager::GateManager (Data *data) : statePtr (&stateMember)//, contextdata ()
{
  statePtr->data = data; // connecting state->data with the context data
  cout << "---------- new GateManager(data) ----------------" << endl;
}
string
GateManager::getName ()
{
  return statePtr->getName ();
}
void
GateManager::reportEnterMetalDetection ()
{
  statePtr->reportEnterMetalDetection ();
}
void
GateManager::reportLeavingMetalDetection ()
{
  statePtr->reportLeavingMetalDetection ();
}
void
GateManager::reportMintimerToMetalDetectionExpired()
{
  statePtr->reportMintimerToMetalDetectionExpired ();
}
void
GateManager::reportMaxtimerToMetalDetectionExpired()
{
    statePtr->reportMaxtimerToMetalDetectionExpired();
}
void
GateManager::reportMetalDetectionTimeout()
{
  statePtr->reportMetalDetectionTimeout();
}
void
GateManager::ignoreTiming()
{
  statePtr->ignoreTiming();
}

void GateManager::reportMetalDetected() {
  if (statePtr->data->pukInMetalDetection == nullptr) {
//    cout << "reportMetalDetected(): statePtr->data->pukInMetalDetection == nullptr" << endl;
  } else {
//  cout << "reportMetalDetected(): setting containsMetal=true :::::::statePtr->data->pukInMetalDetection->containsMetal: "
//   << statePtr->data->pukInMetalDetection->containsMetal<< endl;
    statePtr->data->pukInMetalDetection->containsMetal = true;
  }
}

void GateManager::rampBlocked(){
  statePtr->rampBlocked();
  statePtr->data->rampBlocked=true;
}
void GateManager::rampFreed(){
  statePtr->rampFreed();
  statePtr->data->rampBlocked=false;
  statePtr->data->rampObstructed=false;
}

void GateManager::reportRampObstructionCleared(){
  statePtr->reportRampObstructionCleared();
  statePtr->data->otherRampObstructed=false;
}

void
GateManager::reportGateTimeout()
{
  statePtr->data->gateCtrl->close();
}
void GateManager::reportRampTimeout()
{
  cout << "reportRampTimeout: obsolete" << endl;
}
//int main(){
//    cout << "GateDetectionManager v2.1" << endl;
//    Data *data = new Data();
//    cout << "test puk without metal core" << endl;
//    GateManager *gm = new GateManager(data);
//
//    gm->reportEnterMetalDetection();
//    gm->reportLeavingMetalDetection();
//    cout << "test puk with metal core" << endl;
//    gm->reportEnterMetalDetection();
//    gm->reportMetalDetected();
//    gm->reportLeavingMetalDetection();
//}
