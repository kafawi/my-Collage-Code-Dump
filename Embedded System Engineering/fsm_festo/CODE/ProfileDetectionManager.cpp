/**
 * @brief FSM controlling profile detection
 * @author Lennart Hartmann
 * @version 31.05.2017
 */
#include "ProfileDetectionManager.h"
#include "MotorController.h"
#include "WarningLightsController.h"
#include "ProfileDetectionController.h"
#include "Pukmanager.h"
#include "HDI_Manager.h"
#include "MCL_signals.h"
#include <iostream>
#include <string>

using namespace std;

//Superstate
string
ProfileDetectionManager::State::getName ()
{
  return "Superstate";
}
void
ProfileDetectionManager::State::reportEnterProfileDetection ()
{
  cout << "\n" << this->getName () << ": EnterProfileDetection detected / -\n";
}
void
ProfileDetectionManager::State::reportLeavingProfileDetection ()
{
  cout << "\n" << this->getName () << ": LeavingProfileDetection / -\n";
}
void
ProfileDetectionManager::State::reportMintimerToProfileDetectionExpired()
{
  cout << "\n" << this->getName () << ": MintimerToProfileDetectionExpired / -\n";
}
void
ProfileDetectionManager::State::reportMaxtimerToProfileDetectionExpired()
{
  cout << "\n" << this->getName () << ": MaxtimerToProfileDetectionExpired / -\n";
}
void
ProfileDetectionManager::State::reportProfileDetectionTimeout()
{
  cout << "\n" << this->getName () << ": ProfileDetectionTimeout / -\n";
}
void
ProfileDetectionManager::State::ignoreTiming()
{
  cout << "\n" << this->getName () << ": got ignoreTiming / -\n";
}

//State Idle
string
ProfileDetectionManager::Idle::getName()
{
  return "Idle";
}
void
ProfileDetectionManager::Idle::reportEnterProfileDetection()
{
//PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::Idle::reportEnterProfileDetection() -> data->pukInProfileDetection was nullptr ";
  }
  data->timeError=true;
  data->motorCntr->suspend(true);
  data->warningLights->setFlashFast(true);
  data->hdiMngr->printError(UNEXPECTED_OBJECT_IN_PROFILE_DETECTION);
  new (this) UntrackedWorkpiece;
}
void
ProfileDetectionManager::Idle::reportMintimerToProfileDetectionExpired()
{
    //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::Idle::reportMintimerToProfileDetectionExpired() -> data->pukInProfileDetection was nullptr ";
  }
  cout << "timing ok" << endl;
  new (this) Ready;
}

//State UntrackedWorkpiece
string
ProfileDetectionManager::UntrackedWorkpiece::getName()
{
  return "UntrackedWorkpiece";
}
void
ProfileDetectionManager::UntrackedWorkpiece::ignoreTiming()
{
     //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::UntrackedWorkpiece::ignoreTiming() -> data->pukInProfileDetection was nullptr ";
  }
  data->pukMngr->insertPukInGate();
     //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::UntrackedWorkpiece::ignoreTiming() -> data->pukInProfileDetection was nullptr, even after inserted ";
  }
  data->timeError=false;
  data->motorCntr->suspend(false);
  data->warningLights->setFlashFast(false);
  data->profDetCtrl->requestDetection();
  new (this) Processing;
}

//State MissingWorkpiece
string
ProfileDetectionManager::MissingWorkpiece::getName()
{
  return "MissingWorkpiece";
}
void
ProfileDetectionManager::MissingWorkpiece::ignoreTiming()
{
       //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::MissingWorkpiece::ignoreTiming() -> data->pukInProfileDetection was nullptr ";
  }
  data->pukMngr->removePukInProfileDetection();
      //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::MissingWorkpiece::ignoreTiming() -> data->pukInProfileDetection was nullptr after removePukInProf.det. ";
  }
  data->timeError=false;
  if(data->pukMngr->isEmpty()){
    data->motorCntr->suspend(false);
  }
  data->warningLights->setFlashFast(false);
  new (this) Idle;
}

//State Ready
string
ProfileDetectionManager::Ready::getName ()
{
  return "Ready";
}
void
ProfileDetectionManager::Ready::reportMaxtimerToProfileDetectionExpired()
{
        //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::Ready::reportMaxtimerToProfileDetectionExpired() -> data->pukInProfileDetection was nullptr ";
  }
  data->timeError=true;
  data->motorCntr->suspend(true);
  data->warningLights->setFlashFast(true);
  data->hdiMngr->printError(MISSING_WORKPIECE_IN_PROFILE_DETECTION);
  new (this) MissingWorkpiece;
}
void
ProfileDetectionManager::Ready::reportEnterProfileDetection ()
{
          //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::Ready::reportEnterProfileDetection() -> data->pukInProfileDetection was nullptr ";
  }
  data->motorCntr->setSpeed (SLOW);
  data->pukMngr->refreshNextPukInProfileDetection ();
  data->pukInProfileDetection = data->pukMngr->getPukInProfileDetection ();
  data->pukInProfileDetection->maxTimer->isSuspended_=true;
  //data->timerCtrl->resetTimer(data->profileDetectionWindowTimer,PROFILE_DETECTION_TIMER);
  //data->profileDetectionWindowTimer->isSuspended_=false;
  data->profDetCtrl->requestDetection();
  new (this) Processing;
}

//State Processing
string
ProfileDetectionManager::Processing::getName ()
{
  return "Processing";
}
void
ProfileDetectionManager::Processing::reportLeavingProfileDetection ()
{
          //PRINTNULLPOINTER
    if (data->pukInProfileDetection == nullptr)
  {
    cout << " ProfileDetectionManager::Processing::reportLeavingProfileDetection() -> data->pukInProfileDetection was nullptr ";
  }
  data->timerCtrl->resetTimer(data->pukInProfileDetection->minTimer,TO_METAL_DETECTION_MIN);
  data->timerCtrl->resetTimer(data->pukInProfileDetection->maxTimer,TO_METAL_DETECTION_MAX);
//  data->pukInProfileDetection->minTimer->isSuspended_=false;
//  data->pukInProfileDetection->maxTimer->isSuspended_=false;
  data->profDetCtrl->stopDetection();
  data->motorCntr->setSpeed (FAST);
  cout << "leaving profile detection" << endl;
  new (this) Idle;
}

// assigning start state
ProfileDetectionManager::ProfileDetectionManager ()
: statePtr (&stateMember)
, contextdata ()
{
  statePtr->data = contextdata; // connecting state->data with the context data
  cout << "---------- new ProfileDetectionManager() ----------------" << endl;
}
ProfileDetectionManager::ProfileDetectionManager (Data* data)
: statePtr (&stateMember)
, contextdata ()
{
  statePtr->data = data; // connecting state->data with the context data
  cout << "---------- new ProfileDetectionManager(data) ----------------" << endl;
}
ProfileDetectionManager::~ProfileDetectionManager () { }
string
ProfileDetectionManager::getName ()
{
  return statePtr->getName ();
}
void
ProfileDetectionManager::reportEnterProfileDetection ()
{
  statePtr->reportEnterProfileDetection ();
}
void
ProfileDetectionManager::reportLeavingProfileDetection ()
{
  statePtr->reportLeavingProfileDetection ();
}
void
ProfileDetectionManager::reportMintimerToProfileDetectionExpired()
{
  statePtr->reportMintimerToProfileDetectionExpired();
}
void
ProfileDetectionManager::reportMaxtimerToProfileDetectionExpired()
{
  statePtr->reportMaxtimerToProfileDetectionExpired();
}
void
ProfileDetectionManager::ignoreTiming(){
  statePtr->ignoreTiming();
}
void
ProfileDetectionManager::reportProfileDetectionTimeout()
{
  //statePtr->data->profDetCtrl->stopDetection();
}
void
ProfileDetectionManager::reportPuktype()
{
//	if (statePtr->data->pukInProfileDetection == nullptr){
//		cout << "no puk in Profiledetection, DO SOMTHING" <<endl;
//	} else {
//      statePtr->data->pukInProfileDetection->unknownType=false;
//	}
}

//typedef void (ProfileDetectionManager::State::*func)();
//static const func funcTable[];

//int main(){
//    cout << "ProfileDetectionManager v2.1" << endl;
//    Data *data = new Data();
//    ProfileDetectionManager *pdm = new ProfileDetectionManager(data);
//    cout << "test unknown profile" << endl;
//    pdm->reportEnterProfileDetection();
//    pdm->reportLeavingProfileDetection();
//    cout << "test valid profile" << endl;
//    pdm->reportEnterProfileDetection();
//    pdm->reportPuktype();
//    pdm->reportLeavingProfileDetection();
//}
