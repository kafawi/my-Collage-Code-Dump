/**
 * @brief FSM controlling entry
 * @author Lennart Hartmann
 * @version 16.06.2017
 */
#include "EntryManager.h"
#include "Data.h"
#include "Pukmanager.h"
#include "MotorController.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>


using namespace std;

string EntryManager::State::getName(){
    return "EntryManager Superstate";
}

void EntryManager::State::reportNewPuk(){
    cout<<"\n"<< this->getName()<<": new Puk / - \n";
}
void EntryManager::State::reportLeavingEntry(){
    cout<<"\n"<< this->getName() <<": leaving entry / -\n";
}

string EntryManager::Ready::getName(){
    return "EntryReady";
}

void EntryManager::Ready::reportNewPuk(){
    //only if not received fron other conveyor
    if(!data->isReceivingEnd){
        data->pukMngr->trackNewPuk();
        //data->pukInEntry=data->pukMngr->getPukInEntry();
    } else {
    	data->pukMngr->receivePuk();
    }
    //PRINTNULLPOINTER
    if (data->pukInEntry == nullptr)
    {
        cout << " EntryManager::Ready::reportNewPuk() -> data->pukInEntry was nullptr ";
    }

    data->motorCntr->suspend(false);
    new (this) Done;// change to state B
}

string
EntryManager::Done::getName(){
    return "EntryDone";
};

void
EntryManager::Done::reportLeavingEntry(){
    cout << "leaving entry (DONE)" << endl;
    //PRINTNULLPOINTER
    if (data->pukInEntry == nullptr)
    {
        cout << " EntryManager::Done::reportLeavingEntry() -> data->pukInEntry was nullptr ";
    }
    data->timerCtrl->resetTimer(data->pukInEntry->minTimer,TO_PROFILE_DETECTION_MIN);
    data->timerCtrl->resetTimer(data->pukInEntry->maxTimer,TO_PROFILE_DETECTION_MAX);
    data->pukInEntry->minTimer->isSuspended_=false;
    data->pukInEntry->maxTimer->isSuspended_=false;
    new (this) Ready;
}


	// assigning start state
    EntryManager::EntryManager(): statePtr (&stateMember), contextdata (),receivingEnd(false){
        statePtr->data = contextdata;

        cout << "---------- new EntryManager() ----------------" << endl;
    }
    EntryManager::EntryManager(Data *data):statePtr (&stateMember),receivingEnd(data->isReceivingEnd){
        statePtr->data = data;
        cout << "---------- new EntryManager(data) ----------------" << endl;
    }

    EntryManager::~EntryManager(){}

    string EntryManager::getName(){
        return statePtr->getName();
     }

    void EntryManager::reportNewPuk(){
        statePtr->reportNewPuk();
    }

    void EntryManager::reportLeavingEntry(){
        statePtr->reportLeavingEntry();
    }

////////////////////////////////////////////////////////////////////////////////////////////

//int main(){
//    cout << "EntryManager v1.3" << endl;
//    EntryManager *em = new EntryManager(new Data());
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportLeavingEntry();
//}

