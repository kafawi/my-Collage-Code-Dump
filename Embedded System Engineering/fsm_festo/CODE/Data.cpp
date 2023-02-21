/**
 * @brief Data struct for sharing memory
 * @author Lennart Hartmann
 * @version 06.06.2017
 */
#include "Data.h"

#include "MotorController.h"
#include "Pukmanager.h"
#include "PukSequenceTracker.h"
#include "ButtonLightController.h"
#include "GateController.h"
#include "WarningLightsController.h"
#include "serialController.h"
#include "timerController.h"
#include "ProfileDetectionController.h"
#include "HDI_Manager.h"
#include "Puk.h"
#include "timer.h"
#include <iostream>

////for debug only
//Data::Data()
//:metalExpected(false)
//,systemOff(false)
//,EStopped(false)
//,rampsBlockedError(false)
//,otherEntryBlocked(false)
//,rampObstructed(false)
//,otherRampObstructed(false)
//,rampBlocked(false)
//,timeError(false)
//,entryClear(true)
//,isReceivingEnd(false)
//,motorCntr(new MotorController())
//,pukMngr(new Pukmanager(this))
//,sequenceTracker(new PukSequenceTracker(this))
//,bttnCtrl(new ButtonLightController())
//,gateCtrl(new GateController())
//,warningLights(new WarningLightsController())
//,serialMsgMan(new SerialController(this))
//,timerCtrl(new TimerController())
//,profDetCtrl(new ProfileDetectionController(this))
//,hdiMngr(new HDI_Manager())
//,receivedPuk(nullptr)
//,pukInEntry(nullptr)
//,pukInProfileDetection(nullptr)
//,pukInMetalDetection(nullptr)
//,pukInExit(nullptr)
//,metalDetectionWindowTimer(timerCtrl->getTimer())
//,gateOpenTimer(timerCtrl->getTimer())
//,rampObstructionTimer(timerCtrl->getTimer())
//,profileDetectionWindowTimer(timerCtrl->getTimer())
//,antiEstopPrellTimer(timerCtrl->getTimer())
//{
//    std::cout << "////////////////// new Data() ////////////////////" << std::endl;
//}

Data::Data(bool isReceivingEnd)
:metalExpected(false)
,systemOff(false)
,EStopped(false)
,rampsBlockedError(false)
,otherEntryBlocked(false)
,rampObstructed(false)
,otherRampObstructed(false)
,rampBlocked(false)
,timeError(false)
,entryClear(true)
,isReceivingEnd(isReceivingEnd)
,motorCntr(new MotorController())
,pukMngr(new Pukmanager(this))
,sequenceTracker(new PukSequenceTracker(this))
,bttnCtrl(new ButtonLightController())
,gateCtrl(new GateController())
,warningLights(new WarningLightsController())
,serialMsgMan(new SerialController(this))
,timerCtrl(new TimerController())
,profDetCtrl(new ProfileDetectionController(this))
,hdiMngr(new HDI_Manager())
,receivedPuk(nullptr)
,pukInEntry(nullptr)
,pukInProfileDetection(nullptr)
,pukInMetalDetection(nullptr)
,pukInExit(nullptr)
,metalDetectionWindowTimer(timerCtrl->getTimer())
,gateOpenTimer(timerCtrl->getTimer())
,rampObstructionTimer(timerCtrl->getTimer())
,profileDetectionWindowTimer(timerCtrl->getTimer())
,antiEstopPrellTimer(timerCtrl->getTimer())
{
    if(isReceivingEnd){
        std::cout << "------------------ new Data() receiver -------------------------" << std::endl;
    }else{
        std::cout << "------------------ new Data() provider -------------------------" << std::endl;
    }
}


Data::~Data()
{
  delete (motorCntr);
  delete (pukMngr);
  delete (sequenceTracker);
  delete (bttnCtrl);
  delete (gateCtrl);
  delete (motorCntr);
  delete (warningLights);
  delete (pukInProfileDetection);
  delete (pukInMetalDetection);
  delete (pukInExit);
//  delete (metalDetectionWindowTimer);
//  delete (gateOpenTimer);
//  delete (rampObstructionTimer);
//  delete (profileDetectionWindowTimer);
}

//int main(){
//    OutletManager outman = OutletManager(new Data());
//    outman.reportReachedExit();
//    outman.reportLeavingExit();
//}
