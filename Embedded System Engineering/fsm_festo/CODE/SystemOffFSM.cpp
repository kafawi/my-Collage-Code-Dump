/**
 * @brief FSM controlling behaviour if system is switched to standby
 * @author Lennart Hartmann
 * @version 07.05.2017
 */

#include "SystemOffFSM.h"
#include "MotorController.h"
#include "WarningLightsController.h"
#include "ButtonLightController.h"
#include <string>
#include <iostream>
#include "Pukmanager.h"

using namespace std;

// Superstate ////////////////////////////////////////////
string SystemOffFSM::IrregularState::getName() {
	return "SystemOffFSM Superstate";
}
void SystemOffFSM::IrregularState::reportStopPressed() {
	cout << "\n" << this->getName() << ": StopPressed / - \n";
}
void SystemOffFSM::IrregularState::reportStartPressed() {
	cout << "\n" << this->getName() << ": StartPressed IRS/ -\n";
}

// State On ///////////////////////////////////////////////
string SystemOffFSM::On::getName() {
	return "System on";
}

void SystemOffFSM::On::reportStopPressed() {
//	if (!data->pukMngr->isEmpty()) {
//		data->motorCntr->suspend(true);
//	}
	data->motorCntr->suspend(true);
	cout << "warningLights->setGreen(false)" << endl;
	data->warningLights->setGreen(false);
	data->bttnCtrl->reportStopPressed();
	data->systemOff = true;
	new (this) Off;

}

void SystemOffFSM::On::reportStartPressed() {
	if (!data->pukMngr->isEmpty()) {
		data->motorCntr->reportExceptionCleared();
	}
	data->warningLights->setGreen(true);
	data->bttnCtrl->reportStartPressed();
	data->systemOff = false;
	new (this) On;

}

// State Off ///////////////////////////////////////////////
string SystemOffFSM::Off::getName() {
	return "System off";
}
;

void SystemOffFSM::Off::reportStartPressed() {
	if (!data->pukMngr->isEmpty()) {
		data->motorCntr->reportExceptionCleared();
	}

	data->warningLights->setGreen(true);
	data->bttnCtrl->reportStartPressed();
	data->systemOff = false;
	new (this) On;

}

void SystemOffFSM::Off::reportStopPressed() {
//	if (!data->pukMngr->isEmpty()) {
//		data->motorCntr->reportExceptionCleared();
//	}
	data->motorCntr->suspend(true);
	data->warningLights->setGreen(false);
	data->bttnCtrl->reportStopPressed();
	data->systemOff = true;
	cout << "stop pressed twice" << endl;
	new (this) Off;

//	data->warningLights->setGreen(false);
//	data->bttnCtrl->reportStopPressed();
//	data->systemOff = true;
//	new (this) Off;
}


// Public functions ////////////////////////////////////////
SystemOffFSM::SystemOffFSM() :
		statePtr(&stateMember), contextdata() {
	statePtr->data = contextdata;
	cout << "SystemOffFSM instaciated" << endl;
}

SystemOffFSM::SystemOffFSM(Data *mydata) :
		statePtr(&stateMember), contextdata() {
	statePtr->data = mydata;
	cout << "SystemOffFSM instanciated" << endl;
}

SystemOffFSM::~SystemOffFSM() {
	cout << "SystemOffFSM destroyed" << endl;
}

//passing function call to fsm
string SystemOffFSM::getName() {
	return statePtr->getName();
}
void SystemOffFSM::reportStopPressed() {
	statePtr->reportStopPressed();
}
void SystemOffFSM::reportStartPressed() {
	statePtr->reportStartPressed();
}

//int main(){
//    cout << "ver 1.1" << endl;
//    SystemOffFSM *sysOffFsm = new SystemOffFSM();
//    sysOffFsm->reportStartPressed();
//    sysOffFsm->reportStopPressed();
//    sysOffFsm->reportStartPressed();
//    delete sysOffFsm;
//}
