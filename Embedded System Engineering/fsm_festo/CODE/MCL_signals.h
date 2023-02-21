/**
 * @brief Header decribing emums required for pulse messaging to MCL
 * @author Lennart Hartmann
 * @version 15.6.2017
 */

#ifndef MCL_DISPATCHER_H_INCLUDED
#define MCL_DISPATCHER_H_INCLUDED

#define POS_UPDT_OFFSET 100
#define PROPERTY_OFFSET 200
#define BTN_OFFSET 300
#define TIMER_OFFSET 400
#define STATUS_UPDT_OFFSET 500
#define SIGTYPE_OFFSET 600
#define INCOMMING_CODE 1

/**
 * Identifiing event reported by HAL
 */
enum MCL_input_signal{
//signals written to MCL input-channel by HAL
    NEWPUK,                     //calls reportNewPuk
    LEAVING_ENTRY,              //calls reportLeavingEntry
    ENTER_PROFILE_DETECTION,    //calls reportEnterProfileDetection
    REGULAR,                    //calls reportPuktype //Werkstück im Tolleranzbereich!
    LEAVING_PROFILE_DETECTION,  //calls reportLeavingProfileDetection
    ENTER_METAL_DETECTION,      //calls reportEnterMetalDetection
    LEAVING_METAL_DETECTION,    //calls reportLeavingMetalDetection
    METAL_DETECTED,             //calls reportMetalDetected
    REACHED_EXIT,               //calls reportReachedExit
    LEAVING_EXIT,               //calls reportLeavingExit
    //Identifiing reported Button signal
    STOP_BTN,                   //calls reportStopPressed
    START_BTN,                  //calls reportStartPressed
    RESET_BTN,                  //calls reportResetPressed
    E_STOP_PRESSED,             //calls reportEStopPressed
    E_STOP_RELEASED,            //calls reportEStopReleased

//signals written to MCL input-channel by SerialInputController
    RECEIVED_PUK,               //calls reportPukReceived; stream to Puk conversion done
    //Conveyor status updates reportet by other conveyor
    ERROR_CLEARED_ACK,          //calls reportErrorClearedAck
    ERROR_CLEARED_NO_ACK,       //calls reportErrorClearedNoAck
    ERROR_PENDING_ACK,          //calls reportErrorAck
    ERROR_PENDING_NO_ACK,       //calls reportErrorNoAck
    ENTRY_OCCUPIED,             //calls reportEntryOccupied
    ENTRY_CLEAR,                //calls reportEntryClear
    RAMP_OBSTRUCTED,
    RAMP_OBSTRUCTION_CLEARED,
    SERIAL_CONNECTION_FAIL,       //connection severed
//signals written to MCL input-channel by Timers
    TO_PROFILE_DETECTION_MIN,   //calls reportMintimerToProfileDetectionExpired
    TO_PROFILE_DETECTION_MAX,   //calls reportMaxtimerToProfileDetectionExpired
    TO_METAL_DETECTION_MIN,     //calls reportMintimerToMetalDetectionExpired
    TO_METAL_DETECTION_MAX,     //calls reportMaxtimerToMetalDetectionExpired
    TO_EXIT_MIN,                //calls reportMintimerToOutletExpired
    TO_EXIT_MAX,                //calls reportMaxtimerToOutletExpired
    GATE_TIMER,                  //calls reportGateTimeout
    RAMP_TIMER,                 //calls reportRampTimeout
    METAL_DETECTION_TIMER,      //calls reportMetalDetectionTimeout
    PROFILE_DETECTION_TIMER,    //no longer used
//extras for ramp-monitoring
    RAMP_BLOCKED,               //calls rampBlocked
    RAMP_FREED,                 //call rampBlocked
/////////////////////// relevant for serial messenging only! to separate header? /////////////////////////////////////////////////////////////////////
//Puk properties; reportet by ProfileDetectionController
    PROFILE_DETECTED,
//announcing incoming Puk data
    SERIAL_PUK_DATA,
// Just in case (used in Timer)
    UNKNOWN_MCL_SIGNAL,
// This is the anti Prelltimer for the estop
    ESTOP_ANTI_PRELL_TIMER
};

#endif // MCL_DISPATCHER_H_INCLUDED
