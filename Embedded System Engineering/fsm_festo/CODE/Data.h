/**
 * @brief Data struct for sharing memory
 * @author Lennart Hartmann
 * @version 16.06.2017
 */
#ifndef DATA_H
#define DATA_H
#include "timerController.h"

class MotorController;
class Pukmanager;
class PukSequenceTracker;
class ButtonLightController;
class GateController;
class WarningLightsController;
class SerialController;
class TimerController ;
class HDI_Manager;
class ProfileDetectionController;
class Puk;

class Data
{
    public:
        Data();
        Data(bool isReceivingEnd);
        virtual ~Data();
        bool metalExpected;
        bool systemOff;
        bool EStopped;
        bool rampsBlockedError;
        bool otherEntryBlocked;
        bool rampObstructed;
        bool otherRampObstructed;
        bool rampBlocked;
        bool timeError;
        bool entryClear;
        bool isReceivingEnd;
        MotorController *motorCntr;
        Pukmanager *pukMngr;
        PukSequenceTracker *sequenceTracker;
        ButtonLightController *bttnCtrl;
        GateController *gateCtrl;
        WarningLightsController *warningLights;
        SerialController *serialMsgMan;
        TimerController *timerCtrl;
        ProfileDetectionController *profDetCtrl;
        HDI_Manager *hdiMngr;
        Puk *receivedPuk;
        Puk *pukInEntry;
        Puk *pukInProfileDetection;
        Puk *pukInMetalDetection;
        Puk *pukInExit;
        Timer *metalDetectionWindowTimer;
        Timer *gateOpenTimer;
        Timer *rampObstructionTimer;
        Timer *profileDetectionWindowTimer;
        Timer *antiEstopPrellTimer;
    protected:
    private:
};

#endif // DATA_H


