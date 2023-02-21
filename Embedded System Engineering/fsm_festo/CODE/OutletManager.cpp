/**
 * @brief FSM controlling outlet
 * @author Lennart Hartmann
 * @author kafa
 * @version 17.06.2017
 */
#include "OutletManager.h"
#include "Data.h"

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

string
OutletManager::State::getName ()
{
  return "Superstate";
};
void
OutletManager::State::reportNewPuk ()
{
  cout << "\n" << this->getName ()<< ": new Puk / - \n";
}
void
OutletManager::State::reportLeavingEntry ()
{
  cout << "\n" << this->getName () << ": leaving entry OUTLET/ -\n";
}
void
OutletManager::State::reportEnterProfileDetection ()
{
  cout << "\n" << this->getName () << ": EnterProfileDetection detected / -\n";
}
void
OutletManager::State::reportPuktype ()
{
  cout << "\n" << this->getName () << ": Puktype / -\n";
}
void
OutletManager::State::reportLeavingProfileDetection ()
{
  cout << "\n" << this->getName () << ": LeavingProfileDetection / -\n";
}
void
OutletManager::State::reportEnterMetalDetection ()
{
  cout << "\n" << this->getName () << ": EnterMetalDetection / -\n";
}
void
OutletManager::State::reportLeavingMetalDetection ()
{
  cout << "\n" << this->getName () << ": LeavingMetalDetection / -\n";
}
void
OutletManager::State::reportMetalDetected ()
{
  cout << "\n" << this->getName () << ": MetalDetected / - \n";
}
void
OutletManager::State::reportReachedExit ()
{
  cout << "\n" << this->getName () << ": ReachedExit / -\n";
}
void
OutletManager::State::reportLeavingExit ()
{
  cout << "\n" << this->getName () << ": LeavingExit / -\n";
}
void
OutletManager::State::reportStopPressed ()
{
  cout << "\n" << this->getName () << ": reportStopPressed / -\n";
}
void
OutletManager::State::reportStartPressed ()
{
  cout << "\n" << this->getName () << ": StartPressed / -\n";
}
void
OutletManager::State::reportMintimerToOutletExpired()
{
  cout << "\n" << this->getName() << ": MintimerToOutletExpired / -\n";
}
void
OutletManager::State::reportMaxtimerToOutletExpired ()
{
  cout << "\n" << this->getName () << ": MaxtimerToOutletDetectionExpired / -\n";
}
void
OutletManager::State::ignoreTiming ()
{
  cout << "\n" << this->getName () << ": trying to cancel error state / -\n";
}
//ready
string
OutletManager::Ready::getName ()
{
  return "OutletReady";
}
void
OutletManager::Ready::reportReachedExit ()
{
  //PRINTNULLPOINTER
  data->pukMngr->refreshNextPukInExit();
  if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::Ready::reportReachedExit() -> data->pukInExit was nullptr ";
  }
  data->pukInExit->maxTimer->isSuspended_ = true; //or false?
  cout << "wait for puk clearing" << endl;
  new (this) Expecting; // change to state B
}
void
OutletManager::Ready::reportMaxtimerToOutletExpired ()
{
    data->timeError=true;
    data->motorCntr->suspend(true);
    data->warningLights->setFlashFast(true);
    data->hdiMngr->printError(MISSING_WORKPIECE_IN_OUTLET);
    new (this) UntrackedWorkpiece;
}


string
OutletManager::Expecting::getName ()
{
  return "Expecting";
};
void
OutletManager::Expecting::reportLeavingExit ()
{
  //PRINTNULLPOINTER
  if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::Expecting::reportLeavingExit() -> data->pukInExit was nullptr, before refresh ";
  }
  data->pukMngr->refreshNextPukInExit ();
  data->pukMngr->transferPuk ();
  //PRINTNULLPOINTER
  if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::Expecting::reportLeavingExit() -> data->pukInExit was nullptr, after refresh, transfered ";
  }
  cout << "leaving outlet" << endl;
  if (data->pukMngr->isEmpty ())
  {
    data->motorCntr->suspend (true);
  }
  if (!(data->entryClear))
  {
    data->motorCntr->suspend(true);
  }
//  new (this) Ready;
  new (this) Idle;
}
//State Idle
string
OutletManager::Idle::getName()
{
    return "Idle";
}
void
OutletManager::Idle::reportReachedExit()
{
    data->timeError=true;
    data->motorCntr->suspend(true);
    data->warningLights->setFlashFast(true);
    data->hdiMngr->printError(UNEXPECTED_OBJECT_IN_OUTLET);
    new (this) UntrackedWorkpiece;
}

void
OutletManager::Idle::reportMintimerToOutletExpired()
{
    //PRINTNULLPOINTER
    if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::Idle::reportMintimerToOutletExpired() -> data->pukInExit was nullptr ";
  }
    cout << "timing ok" << endl;
    new (this) Ready;
}

//State UntrackedWorkpiece
string
OutletManager::UntrackedWorkpiece::getName ()
{
  return "UntrackedWorkpiece";
}
void
OutletManager::UntrackedWorkpiece::ignoreTiming()
{
    //PRINTNULLPOINTER
    if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::UntrackedWorkpiece::ignoreTiming() -> data->pukInExit was nullptr ";
  }
  data->pukMngr->insertPukInGate();
   //PRINTNULLPOINTER
    if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::UntrackedWorkpiece::ignoreTiming() -> data->pukInExit was nullptr, even after puk inserted ";
  }
  data->timeError=false; //ture or false?
  data->motorCntr->suspend(false);
  data->warningLights->setFlashFast(false);
  new (this) Expecting;
}

//State MissingWorkpiece
string
OutletManager::MissingWorkpiece::getName ()
{
  return "MissingWorkpiece";
}
void
OutletManager::MissingWorkpiece::ignoreTiming(){
 //PRINTNULLPOINTER
    if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::MissingWorkpiece::ignoreTiming() -> data->pukInExit was nullptr ";
  }
  data->pukMngr->removePukInExit();
 //PRINTNULLPOINTER
    if (data->pukInExit == nullptr)
  {
    cout << " OutletManager::MissingWorkpiece::ignoreTiming() -> data->pukInExit was nullptr, even after puk inserted ";
  }
  data->timeError=false;
    if(data->pukMngr->isEmpty()){
        data->motorCntr->suspend(false);
    }
  data->warningLights->setFlashFast(false);
  //hdi -> printerror MISSING_WORKPIECE_IN_OUTLET
  new (this) Idle;
}


OutletManager::OutletManager () :receivingEnd(false), statePtr (&stateMember), contextdata (){
    statePtr->data = contextdata; // connecting state->data with the context data
    cout << "---------- new OutletManager() ----------------" << endl;
}
OutletManager::OutletManager (Data *data) : receivingEnd(data->isReceivingEnd),statePtr (&stateMember), contextdata (){
    statePtr->data = data; // connecting state->data with the context data
    cout << "---------- new OutletManager(data) ----------------" << endl;
}
OutletManager::~OutletManager (){
}



std::string
OutletManager::getName(){return statePtr->getName();}

void
OutletManager::reportNewPuk(){statePtr->reportNewPuk();}

void
OutletManager::reportLeavingEntry(){statePtr->reportLeavingEntry();}

void
OutletManager::reportEnterProfileDetection(){statePtr->reportEnterProfileDetection();}

void
OutletManager::reportPuktype(){statePtr->reportPuktype();}

void
OutletManager::reportLeavingProfileDetection(){statePtr->reportLeavingProfileDetection();}

void
OutletManager::reportEnterMetalDetection(){statePtr->reportEnterMetalDetection();}

void
OutletManager::reportLeavingMetalDetection(){statePtr->reportLeavingMetalDetection();}

void
OutletManager::reportMetalDetected(){statePtr->reportMetalDetected();}

void
OutletManager::reportReachedExit(){statePtr->reportReachedExit();}

void
OutletManager::reportLeavingExit(){statePtr->reportLeavingExit();}

void
OutletManager::reportStopPressed(){statePtr->reportStopPressed();}

void
OutletManager::reportStartPressed(){statePtr->reportStartPressed();}

void
OutletManager::reportMintimerToOutletExpired(){statePtr->reportMintimerToOutletExpired();}

void
OutletManager::reportMaxtimerToOutletExpired(){statePtr->reportMaxtimerToOutletExpired();}

void
OutletManager::ignoreTiming(){statePtr->ignoreTiming();}

////////////////////////////////////////////////////////////////////////////////
//const OutletManager::func
//OutletManager::funcTable[] = {
//    &OutletManager::State::reportNewPuk
//  , &OutletManager::State::reportLeavingEntry
//  , &OutletManager::State::reportEnterProfileDetection
//  , &OutletManager::State::reportPuktype
//  , &OutletManager::State::reportLeavingProfileDetection
//  , &OutletManager::State::reportEnterMetalDetection
//  , &OutletManager::State::reportLeavingMetalDetection
//  , &OutletManager::State::reportMetalDetected
//  , &OutletManager::State::reportReachedExit
//  , &OutletManager::State::reportLeavingExit
//  , &OutletManager::State::reportStopPressed
//  , &OutletManager::State::reportStartPressed
//};
////////////////////////////////////////////////////////////////////////////////7
//int main(){
//    Data *data = new Data();
//    OutletManager *om = new OutletManager(data);
//    cout << "OutletManager v1.4 - initial state: " << om->getName() << endl;
//    om->reportReachedExit();
//    om->reportLeavingExit();
//    om->reportReachedExit();
//    om->reportLeavingExit();
//}
