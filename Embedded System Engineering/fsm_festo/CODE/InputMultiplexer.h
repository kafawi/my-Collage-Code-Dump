/**
 * @brief Converting enum to funtion calls and multiplexing events to responsible state Machines
 * @author Lennart Hartmann
 * @version 15.06.2017
 */
#ifndef INPUTMULTIPLEXER_H
#define INPUTMULTIPLEXER_H
#define SYS_STAT_SIZ 6
#define NO_OF_FUNCTIONS 11

#include "MCL_signals.h"
class SerialController;
class EntryManager;
class ProfileDetectionManager;
class GateManager;
class OutletManager;
class ErrorMessageHandler;
class SystemOffFSM;
class EStopFSM;
class CaliFsm;
class Data;

class InputMultiplexer
{
    public:
        InputMultiplexer();
        InputMultiplexer(Data *data);
        virtual ~InputMultiplexer();

         /**
         * converting enum to function call
         */
        void processCode(MCL_input_signal code);

        typedef void (InputMultiplexer::*func)();
        static func funcTable[];
    protected:
    private:
//        void process(Signal s);
        void reportNewPuk();
        void reportLeavingEntry();
        void reportEnterProfileDetection();
        void reportPuktype();
        void reportLeavingProfileDetection();
        void reportEnterMetalDetection();
        void reportLeavingMetalDetection();
        void reportMetalDetected();
        void reportReachedExit();
        void reportLeavingExit();
        void reportStopPressed();
        void reportStartPressed();
        void reportResetPressed();   //RESET_BTN,
        void reportEStopPressed();  //E_STOP_PRESSED,
        void reportEStopReleased(); //E_STOP_RELEASED,
        void reportPukReceived();
        void reportErrorClearedAck();
        void reportErrorClearedNoAck();
        void reportErrorAck();
        void reportErrorNoAck();
        void reportEntryOccupied(); //ENTRY_OCCUPIED
        void reportEntryClear();//ENTRY_CLEAR
        //set flag; referring to local ramp
        void reportRampObstructed();                        //RAMP_OBSTRUCTED,
        void reportRampObstructionCleared();                //RAMP_OBSTRUCTION_CLEARED
        void reportSerialConnectFail();                     //SERIAL_CONNECTION_FAIL,       //connection severed
        void reportMintimerToProfileDetectionExpired();     //TO_PROFILE_DETECTION_MIN,
        void reportMaxtimerToProfileDetectionExpired();     //TO_PROFILE_DETECTION_MAX,
        void reportMintimerToMetalDetectionExpired();       //TO_METAL_DETECTION_MIN,
        void reportMaxtimerToMetalDetectionExpired();       //TO_METAL_DETECTION_MAX,
        void reportMintimerToOutletExpired();               //TO_EXIT_MIN
        void reportMaxtimerToOutletExpired();               //TO_EXIT_MAX
        void reportGateTimeout();                           //GATE_TIMER
        void reportRampTimeout();                           //RAMP_TIMER
        void reportMetalDetectionTimeout();                 //METAL_DETECTION_TIMER
        void reportProfileDetectionTimeout();                 //PROFILE_DETECTION_TIMER,
        //set flag, referring to local ramp
        void rampBlocked();                                 //RAMP_BLOCKED
        void rampFreed();                                   //RAMP_FREED
        void reportProfileDetected();
        void reportSerialPukData();
        void reportUnknown();                               //UNKNOWN_MCL_SIGNAL
        void reportEStopAntiPrellTimer();
        bool processingIrregularState;
        bool otherConveyorBlocked;
        bool sysstatus[SYS_STAT_SIZ];
        SerialController *serialCtrl;
        EntryManager *entryManager;
        ProfileDetectionManager *profileDetectionManager;
        GateManager *gateManager;
        OutletManager *outletManager;
        SystemOffFSM *sysOffFsm;
        EStopFSM *eStopFsm;
        ErrorMessageHandler *errMsgHandler;
        CaliFsm *caliFsm;
        Data *data;
        bool receivingEnd;
};

#endif // INPUTMULTIPLEXER_H
