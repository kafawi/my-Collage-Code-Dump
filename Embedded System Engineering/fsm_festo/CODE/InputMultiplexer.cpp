/**
 * @brief Converting enum to funtion calls and multiplexing events to responsible state Machines
 * @author Lennart Hartmann
 * @version 17.06.2017
 */

#include "InputMultiplexer.h"
#include "serialController.h"
#include "HDI_Manager.h"
#include "EntryManager.h"
#include "ProfileDetectionManager.h"
#include "GateManager.h"
#include "OutletManager.h"
#include "ErrorMessageHandler.h"
#include "SystemOffFSM.h"
#include "EStopFSM.h"
#include "Pukmanager.h"
#include "MotorController.h"
#include "Data.h"
#include "Puk.h"
//#include "CaliFsm.h"
#include <iostream>

InputMultiplexer::InputMultiplexer(Data *data):
    processingIrregularState(false),
    otherConveyorBlocked(false),
    //serialCtrl(new SerialController(data)),
    entryManager(new EntryManager(data)),
    profileDetectionManager(new ProfileDetectionManager(data)),
    gateManager(new GateManager(data)),
    outletManager(new OutletManager(data)),
    sysOffFsm(new SystemOffFSM(data)),
    eStopFsm(new EStopFSM(data)),
    errMsgHandler(new ErrorMessageHandler(data)),
    caliFsm(nullptr),
    data(data),
    receivingEnd(data->isReceivingEnd)
{
    for(int i=0; i<SYS_STAT_SIZ; i++){
        sysstatus[i]=true;
    }
    funcTable[NEWPUK]                   = &InputMultiplexer::reportNewPuk;
    funcTable[LEAVING_ENTRY]            = &InputMultiplexer::reportLeavingEntry;
    funcTable[ENTER_PROFILE_DETECTION]  = &InputMultiplexer::reportEnterProfileDetection;
    funcTable[REGULAR]                  = &InputMultiplexer::reportPuktype;
    funcTable[LEAVING_PROFILE_DETECTION]= &InputMultiplexer::reportLeavingProfileDetection;
    funcTable[ENTER_METAL_DETECTION]    = &InputMultiplexer::reportEnterMetalDetection;
    funcTable[LEAVING_METAL_DETECTION]  = &InputMultiplexer::reportLeavingMetalDetection;
    funcTable[METAL_DETECTED]           = &InputMultiplexer::reportMetalDetected;
    funcTable[REACHED_EXIT]             = &InputMultiplexer::reportReachedExit;
    funcTable[LEAVING_EXIT]             = &InputMultiplexer::reportLeavingExit;
    funcTable[STOP_BTN]                 = &InputMultiplexer::reportStopPressed;
    funcTable[START_BTN]                = &InputMultiplexer::reportStartPressed;
    funcTable[RESET_BTN]                = &InputMultiplexer::reportResetPressed;
    funcTable[E_STOP_PRESSED]           = &InputMultiplexer::reportEStopPressed;
    funcTable[E_STOP_RELEASED]          = &InputMultiplexer::reportEStopReleased;
    funcTable[RECEIVED_PUK]             =&InputMultiplexer::reportPukReceived;
    funcTable[ERROR_CLEARED_ACK]        =&InputMultiplexer::reportErrorClearedAck;
    funcTable[ERROR_CLEARED_NO_ACK]     =&InputMultiplexer::reportErrorClearedNoAck;
    funcTable[ERROR_PENDING_ACK]        =&InputMultiplexer::reportErrorAck;
    funcTable[ERROR_PENDING_NO_ACK]     =&InputMultiplexer::reportErrorNoAck;
    funcTable[ENTRY_OCCUPIED]           =&InputMultiplexer::reportEntryOccupied;
    funcTable[ENTRY_CLEAR]              =&InputMultiplexer::reportEntryClear;
    funcTable[RAMP_OBSTRUCTED]          =&InputMultiplexer::reportRampObstructed;
    funcTable[RAMP_OBSTRUCTION_CLEARED] =&InputMultiplexer::reportRampObstructionCleared;
    funcTable[SERIAL_CONNECTION_FAIL]   =&InputMultiplexer::reportSerialConnectFail;
    funcTable[TO_PROFILE_DETECTION_MIN] =&InputMultiplexer::reportMintimerToProfileDetectionExpired;
    funcTable[TO_PROFILE_DETECTION_MAX] =&InputMultiplexer::reportMaxtimerToProfileDetectionExpired;
    funcTable[TO_METAL_DETECTION_MIN]   =&InputMultiplexer::reportMintimerToMetalDetectionExpired;
    funcTable[TO_METAL_DETECTION_MAX]   =&InputMultiplexer::reportMaxtimerToMetalDetectionExpired;
    funcTable[TO_EXIT_MIN]              =&InputMultiplexer::reportMintimerToOutletExpired;
    funcTable[TO_EXIT_MAX]              =&InputMultiplexer::reportMaxtimerToOutletExpired;
    funcTable[GATE_TIMER]               =&InputMultiplexer::reportGateTimeout;
    funcTable[RAMP_TIMER]               =&InputMultiplexer::reportRampTimeout;
    funcTable[METAL_DETECTION_TIMER]    =&InputMultiplexer::reportMetalDetectionTimeout;
    funcTable[PROFILE_DETECTION_TIMER]  =&InputMultiplexer::reportProfileDetectionTimeout;
    funcTable[RAMP_BLOCKED]             =&InputMultiplexer::rampBlocked;
    funcTable[RAMP_FREED]               =&InputMultiplexer::rampFreed;
    funcTable[PROFILE_DETECTED]         =&InputMultiplexer::reportProfileDetected;
    funcTable[SERIAL_PUK_DATA]          =&InputMultiplexer::reportSerialPukData;
    funcTable[UNKNOWN_MCL_SIGNAL]       =&InputMultiplexer::reportUnknown;
    funcTable[ESTOP_ANTI_PRELL_TIMER]   =&InputMultiplexer::reportEStopAntiPrellTimer;
}

InputMultiplexer::~InputMultiplexer(){
    //dtor
}

void InputMultiplexer::reportNewPuk(){
    cout << "\nprocessing code: new Puk" << endl;
    //inform other conveyor
    if(receivingEnd){
        data->serialMsgMan->sendSysStatusUpdate(ENTRY_OCCUPIED);
    }
    //eval guards
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        entryManager->reportNewPuk();
    }
}
void InputMultiplexer::reportLeavingEntry(){
    cout << "\nprocessing code: LeavingEntry" << endl;
    //eval guards
     if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        entryManager->reportLeavingEntry();
            //inform other conveyor
        if(receivingEnd){
            data->serialMsgMan->sendSysStatusUpdate(ENTRY_CLEAR);
        }
    }
}
void InputMultiplexer::reportEnterProfileDetection(){
    cout << "\nprocessing code: EnterProfileDetection" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        profileDetectionManager->reportEnterProfileDetection();
    }
}
void
InputMultiplexer::reportPuktype()
{
  cout << "\nprocessing code: reportPuktype" << endl;
  if(data->EStopped){
    cout << "no reaction: System in E-Stop" << endl;
  }else if(data->systemOff){
    cout << "no reaction: System off" << endl;
  }else{
    if (data->pukInProfileDetection == nullptr) {
    cout << "reportPuktype: data->pukInProfileDetection == nullptr" << endl;
//      data->pukMngr->refreshNextPukInProfileDetection();
    } else {
//    cout << "reportPuktype: " << data->pukInProfileDetection->ID
//         << endl;
    }
    profileDetectionManager->reportPuktype();
  }
}
void
InputMultiplexer::reportLeavingProfileDetection()
{
    cout << "\nprocessing code: LeavingProfileDetection" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        profileDetectionManager->reportLeavingProfileDetection();
    }
}
void
InputMultiplexer::reportEnterMetalDetection()
{
    cout << "\nprocessing code: EnterMetalDetection" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
      gateManager->reportEnterMetalDetection();
    }
}
void InputMultiplexer::reportLeavingMetalDetection(){
    cout << "\nprocessing code: LeavingMetalDetection" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        gateManager->reportLeavingMetalDetection();
    }
}
void InputMultiplexer::reportMetalDetected()
{
  cout << "\nprocessing code: MetalDetected" << endl;
  if(data->EStopped){
    cout << "no reaction: System in E-Stop" << endl;
  }else if(data->systemOff){
    cout << "no reaction: System off" << endl;
  }else{
    if (data->pukInMetalDetection == nullptr) {
      cout << "reportMetalDetected: data->pukInProfileDetection == nullptr" << endl;
    //  data->pukMngr->refreshNextPukInGate();
    } else {
      cout << "reportMetalDetected: " << data->pukInMetalDetection->ID
           << endl;
    }
    gateManager->reportMetalDetected();
  }
}
void InputMultiplexer::reportReachedExit(){
    cout << "\nprocessing code: ReachedExit" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        outletManager->reportReachedExit();
    }
}
void InputMultiplexer::reportLeavingExit(){
    cout << "\nprocessing code: LeavingExit" << endl;
    //eval guards
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else if(data->systemOff){
        cout << "no reaction: System off" << endl;
    }else{
        outletManager->reportLeavingExit();
         //check other conveyor
        if(!data->entryClear){
            data->motorCntr->suspend(true);
        }
    }
}
void InputMultiplexer::reportStopPressed(){
    cout << "\nprocessing code: StopPressed" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else{
        sysOffFsm->reportStopPressed();
    }
}
void InputMultiplexer::reportStartPressed(){
    cout << "\nprocessing code: StartPressed" << endl;
    if(data->EStopped){
        cout << "no reaction: System in E-Stop" << endl;
    }else{
        sysOffFsm->reportStartPressed();
    }
}
void InputMultiplexer::reportResetPressed(){
    cout << "\nprocessing code: ResetPressed" << endl;  //RESET_BTN,
    if(!data->EStopped && data->timeError){
        cout << "clearing timing errror";
        profileDetectionManager->ignoreTiming();
        gateManager->ignoreTiming();
        outletManager->ignoreTiming();
    }
    eStopFsm->reportResetPressed();
}
void InputMultiplexer::reportEStopPressed(){
    cout << "\nprocessing code: EStopPressed" << endl;  //E_STOP_PRESSED,
    eStopFsm->reportEStopPressed();
}
void InputMultiplexer::reportEStopReleased(){
    cout << "\nprocessing code: EStopReleased" << endl;  //E_STOP_RELEASED,
    eStopFsm->reportEStopReleased();
}
void InputMultiplexer::reportPukReceived(){
    if(receivingEnd){
        cout << "\nprocessing code: RECEIVED_PUK" << endl;
        //todo: call Pukman to insert Puk

        cout << "data->pukMngr->receivePuk(serialInputManager->getReceivedPuk)" << endl;
        //n
        data->pukMngr->receivePuk();
    }else{
        cout << "\nInstanciated as leading conveyor. Can't receive transfered Puks" << endl;
    }
}

void InputMultiplexer::reportErrorClearedAck(){
    cout << "\nprocessing code: ERROR_CLEARED_ACK" << endl;
    errMsgHandler->reportErrorClearedAck();
}
void InputMultiplexer::reportErrorClearedNoAck(){
    cout << "\nprocessing code: ERROR_CLEARED_NO_ACK" << endl;
    errMsgHandler->reportErrorClearedNoAck();
}
void InputMultiplexer::reportErrorAck(){
    cout << "\nprocessing code: ERROR_PENDING_ACK" << endl;
    errMsgHandler->reportErrorAck();
}
void InputMultiplexer::reportErrorNoAck(){
    cout << "\nprocessing code: ERROR_PENDING_NO_ACK" << endl;
    errMsgHandler->reportErrorNoAck();
}
void InputMultiplexer::reportEntryOccupied(){
    if(receivingEnd){
        cout << "information irrelevant: not receiving conveyor" << endl;
    }else{
        cout << "\nprocessing code: ENTRY_OCCUPIED" << endl;
        data->entryClear=false;
    }
}
void InputMultiplexer::reportEntryClear(){
    if(receivingEnd){
        cout << "information irrelevant: not receiving conveyor" << endl;
    }else{
        cout << "\nprocessing code: ENTRY_CLEAR" << endl;
        data->entryClear=true;
        data->motorCntr->suspend(false); //todo: timer?
    }
}

void InputMultiplexer::reportRampObstructed(){
    cout << "\nprocessing code: RAMP_OBSTRUCTED" << endl;
    cout << "set rampObstructed=true" << endl;
    data->otherRampObstructed=true;
}

void InputMultiplexer::reportRampObstructionCleared(){
    //todo: report to GateManager
    cout << "\nprocessing code: RAMP_OBSTRUCTION_CLEARED" << endl;
    cout << "set rampObstructed=false" << endl;
    data->otherRampObstructed=false;
    gateManager->reportRampObstructionCleared();
}

void InputMultiplexer::reportSerialConnectFail(){
    //todo: flag?
    cout << "Serial connection fail" << endl;
}

void InputMultiplexer::reportMintimerToProfileDetectionExpired(){
     cout << "\nprocessing code: TO_PROFILE_DETECTION_MIN" << endl;
    profileDetectionManager->reportMintimerToProfileDetectionExpired();
}

void InputMultiplexer::reportMaxtimerToProfileDetectionExpired(){
    cout << "\nprocessing code: TO_PROFILE_DETECTION_MAX" << endl;
    profileDetectionManager->reportMaxtimerToProfileDetectionExpired();
}

void InputMultiplexer::reportMintimerToMetalDetectionExpired(){
    cout << "\nprocessing code: TO_METAL_DETECTION_MIN" << endl;
    gateManager->reportMintimerToMetalDetectionExpired();

}

void InputMultiplexer::reportMaxtimerToMetalDetectionExpired(){
    cout << "\nprocessing code: TO_METAL_DETECTION_MAX" << endl;
    gateManager->reportMaxtimerToMetalDetectionExpired();
}

void InputMultiplexer::reportMintimerToOutletExpired(){
    cout << "\nprocessing code: TO_EXIT_MIN" << endl;
    //todo: implementierung in OutletMAnager
    outletManager->reportMintimerToOutletExpired();
}

void InputMultiplexer::reportMaxtimerToOutletExpired(){
    cout << "\nprocessing code: TO_EXIT_MAX" << endl;
    //todo: implementierung in OutletMAnager
    outletManager->reportMaxtimerToOutletExpired();
}        //

void InputMultiplexer::reportGateTimeout(){
    cout << "\nprocessing code: GATE_TIMER" << endl;
    //todo: implementierung in GateManager
    gateManager->reportGateTimeout();
}

void InputMultiplexer::reportRampTimeout(){
     cout << "\nprocessing code: RAMP_TIMER" << endl;
    //todo: implementierung in GateManager
    gateManager->reportRampTimeout();
}

void InputMultiplexer::reportMetalDetectionTimeout(){
    cout << "\nprocessing code: METAL_DETECTION_TIMER" << endl;
    //todo: implementierung in GateManager
    gateManager->reportMetalDetectionTimeout();
}

void InputMultiplexer::reportProfileDetectionTimeout(){
    cout << "\nprocessing code: PROFILE_DETECTION_TIMER" << endl;
    profileDetectionManager->reportProfileDetectionTimeout();

}

void InputMultiplexer::rampBlocked(){
    //todo:report to GateMananger
    cout << "\nprocessing code: RAMP_BLOCKED" << endl;
    data->rampBlocked=true;
    gateManager->rampBlocked();
}


void InputMultiplexer::rampFreed(){
    //todo:report to GateMananger
    cout << "\nprocessing code: RAMP_FREED" << endl;
    data->rampBlocked=false;
    gateManager->rampFreed();
}

void InputMultiplexer::reportProfileDetected(){
    cout << "\nprocessing code: PROFILE_DETECTED" << endl;
    //todo: handling?
}


void InputMultiplexer::reportSerialPukData(){
    cout << "\nprocessing code: SERIAL_PUK_DATA" << endl;
    //todo: handling?
}


void InputMultiplexer::reportUnknown(){
    cout << "\nprocessing code: UNKNOWN_MCL_SIGNAL" << endl;
    //todo: handling?
}

void InputMultiplexer::reportEStopAntiPrellTimer(){
	cout << "\nprocessing code: ESTOP_ANTI_PRELL_TIMER" << endl;
	eStopFsm->reportEStopAntiPrellTimer();
}

int const funcTableSize = 41;

void InputMultiplexer::processCode(MCL_input_signal code){
  if (code < funcTableSize){
//    (*this.*funcTable[(Signal) code])();
    (*this.*funcTable[code])();
  }
}


InputMultiplexer::func
InputMultiplexer::funcTable[funcTableSize];
//InputMultiplexer::funcTable[NEW_PUK]= &InputMultiplexer::reportNewPuk;
//Table for enum to function call conversion
/*
const InputMultiplexer::func hfuncTable[] = {
    &InputMultiplexer::reportNewPuk
  , &InputMultiplexer::reportLeavingEntry
  , &InputMultiplexer::reportEnterProfileDetection
  , &InputMultiplexer::reportPuktype
  , &InputMultiplexer::reportLeavingProfileDetection
  , &InputMultiplexer::reportEnterMetalDetection
  , &InputMultiplexer::reportLeavingMetalDetection
  , &InputMultiplexer::reportMetalDetected
  , &InputMultiplexer::reportReachedExit
  , &InputMultiplexer::reportLeavingExit  //10
  , &InputMultiplexer::reportStopPressed
  , &InputMultiplexer::reportStartPressed
  , &InputMultiplexer::reportResetPressed
  , &InputMultiplexer::reportEStopPressed
  , &InputMultiplexer::reportEStopReleased
  , &InputMultiplexer::reportPukReceived
  , &InputMultiplexer::reportErrorClearedAck
  , &InputMultiplexer::reportErrorClearedNoAck
  , &InputMultiplexer::reportErrorAck
  , &InputMultiplexer::reportErrorNoAck   //20
  , &InputMultiplexer::reportEntryOccupied
  , &InputMultiplexer::reportEntryClear
  , &InputMultiplexer::reportRampObstructed
  , &InputMultiplexer::reportRampObstructionCleared
  , &InputMultiplexer::reportSerialConnectFail
  , &InputMultiplexer::reportMintimerToProfileDetectionExpired
  , &InputMultiplexer::reportMaxtimerToProfileDetectionExpired
  , &InputMultiplexer::reportMintimerToMetalDetectionExpired
  , &InputMultiplexer::reportMaxtimerToMetalDetectionExpired
  , &InputMultiplexer::reportMintimerToOutletExpired  //30
  , &InputMultiplexer::reportMaxtimerToOutletExpired
  , &InputMultiplexer::reportGateTimeout
  , &InputMultiplexer::reportRampTimeout
  , &InputMultiplexer::reportMetalDetectionTimeout
  , &InputMultiplexer::reportProfileDetectionTimeout
  , &InputMultiplexer::rampBlocked
  , &InputMultiplexer::rampFreed
  , &InputMultiplexer::reportProfileDetected
  , &InputMultiplexer::reportSerialPukData
  , &InputMultiplexer::reportUnknown     // 40
  , &InputMultiplexer::reportEStopAntiPrellTimer
};
*/


using namespace std;

//int main(){
//    Data *data = new Data();
//    cout << "InputMultiplexer v1.5\n" << endl;
//    cout << "testing entry\n" << endl;
//    InputMultiplexer *im = new InputMultiplexer(data);
//
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(START_BTN);
//    im->processCode(E_STOP_PRESSED);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(E_STOP_RELEASED);
//    im->processCode(STOP_BTN);
//    im->processCode(RESET_BTN);
//
//    im->processCode(STOP_BTN);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(START_BTN);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(LEAVING_ENTRY);
//
//    cout << "\ntesting unknown profile" << endl;
//    im->processCode(ENTER_PROFILE_DETECTION);
//    im->processCode(LEAVING_PROFILE_DETECTION);
//    cout << "\testing valid profile" << endl;
//    im->processCode(ENTER_PROFILE_DETECTION);
//    im->processCode(REGULAR);
//    im->processCode(LEAVING_PROFILE_DETECTION);
//
//    cout << "\ntesting puk without metal core" << endl;
//    im->processCode(ENTER_METAL_DETECTION);
//    im->processCode(LEAVING_METAL_DETECTION);
//    cout << "\ntesting puk with metal core" << endl;
//    im->processCode(ENTER_METAL_DETECTION);
//    im->processCode(METAL_DETECTED);
//    im->processCode(LEAVING_METAL_DETECTION);
//
//    cout << "\ntesting outlet" << endl;
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);
//}


//int main(){
//    Data *data = new Data();
//    cout << "InputMultiplexer v1.4\n" << endl;
//    cout << "testing entry\n" << endl;
//    InputMultiplexer *im = new InputMultiplexer(data);
//
//    im->processCode(STOP_BTN);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(START_BTN);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(LEAVING_ENTRY);
//
//    cout << "\ntesting unknown profile" << endl;
//    im->processCode(ENTER_PROFILE_DETECTION);
//    im->processCode(LEAVING_PROFILE_DETECTION);
//    cout << "\testing valid profile" << endl;
//    im->processCode(ENTER_PROFILE_DETECTION);
//    im->processCode(REGULAR);
//    im->processCode(LEAVING_PROFILE_DETECTION);
//
//    cout << "\ntesting puk without metal core" << endl;
//    im->processCode(ENTER_METAL_DETECTION);
//    im->processCode(LEAVING_METAL_DETECTION);
//    cout << "\ntesting puk with metal core" << endl;
//    im->processCode(ENTER_METAL_DETECTION);
//    im->processCode(METAL_DETECTED);
//    im->processCode(LEAVING_METAL_DETECTION);
//
//    cout << "\ntesting outlet" << endl;
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);
//}

//int main(){
//
//    Data *data = new Data();
//    cout << "InputMultiplexer v1.2\n" << endl;
//    cout << "testing entry\n" << endl;
//    InputMultiplexer *im = new InputMultiplexer(data);
//
//    im->process(reportNewPuk);
//    im->process(reportLeavingEntry);
//    im->process(reportNewPuk);
//    im->process(reportLeavingEntry);
//    im->process(reportNewPuk);
//    im->process(reportLeavingEntry);
//    im->process(reportNewPuk);
//    im->process(reportLeavingEntry);
//    im->process(reportLeavingEntry);
//
//    cout << "\ntesting unknown profile" << endl;
//    im->process(reportEnterProfileDetection);
//    im->process(reportLeavingProfileDetection);
//    cout << "\testing valid profile" << endl;
//    im->process(reportEnterProfileDetection);
//    im->process(reportPuktype);
//    im->process(reportLeavingProfileDetection);
//
//    cout << "\ntesting puk without metal core" << endl;
//    im->process(reportEnterMetalDetection);
//    im->process(reportLeavingMetalDetection);
//    cout << "\ntesting puk with metal core" << endl;
//    im->process(reportEnterMetalDetection);
//    im->process(reportMetalDetected);
//    im->process(reportLeavingMetalDetection);
//
//    cout << "\ntesting outlet" << endl;
//    im->process(reportReachedExit);
//    im->process(reportLeavingExit);
//    im->process(reportReachedExit);
//    im->process(reportLeavingExit);
//}

//int main(){
//
//    Data *data = new Data();
//
//    cout << "EntryManager v1.3" << endl;
//    EntryManager *em = new EntryManager(data);
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportNewPuk();
//    em->reportLeavingEntry();
//    em->reportLeavingEntry();
//
//    cout << "ProfileDetectionManager v2.1" << endl;
//    ProfileDetectionManager *pdm = new ProfileDetectionManager(data);
//    cout << "test unknown profile" << endl;
//    pdm->reportEnterProfileDetection();
//    pdm->reportLeavingProfileDetection();
//    cout << "test valid profile" << endl;
//    pdm->reportEnterProfileDetection();
//    pdm->reportPuktype();
//    pdm->reportLeavingProfileDetection();
//
//    cout << "GateDetectionManager v2.1" << endl;
//    cout << "test puk without metal core" << endl;
//    GateManager *gm = new GateManager(data);
//
//    gm->reportEnterMetalDetection();
//    gm->reportLeavingMetalDetection();
//    cout << "test puk with metal core" << endl;
//    gm->reportEnterMetalDetection();
//    gm->reportMetalDetected();
//    gm->reportLeavingMetalDetection();
//
//    OutletManager *om = new OutletManager(data);
//    cout << "OutletManager v1.4 - initial state: " << om->getName() << endl;
//    om->reportReachedExit();
//    om->reportLeavingExit();
//    om->reportReachedExit();
//    om->reportLeavingExit();
//}
