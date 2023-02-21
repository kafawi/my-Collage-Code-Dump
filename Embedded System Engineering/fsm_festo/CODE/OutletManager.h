/**
 * @brief FSM controlling outlet
 * @author Lennart Hartmann
 * @author kafa
 * @version 05.06.2017
 */
#ifndef OUTLETMANAGER_H
#define OUTLETMANAGER_H



#include "Data.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @class contains the FSM for the last Section on the machine
 */
class OutletManager
{

private:

    bool receivingEnd;

    /**
    * Default state of this section
    * @return
    */
    struct State
    {
        /**
        * get the name of state (debug thing)
        * @return name of state
        */
        virtual string getName();
        /**
        * transaction for newPuk
        */
        virtual void reportNewPuk();
        /**
        * transaction for Puk leave Entry
        */
        virtual void reportLeavingEntry();
        /**
        * transaction for Puk enters the ProfileDetection
        */
        virtual void reportEnterProfileDetection();
        /**
         * transaction Puktype?
         */
        virtual void reportPuktype();
        /**
         * transaction a Puk leaves the ProfileDetection
         */
        virtual void reportLeavingProfileDetection();
        /**
         * transaction Puk enters the metal detection
         */
        virtual void reportEnterMetalDetection();
        /**
         * transaction Puk leaves the metal detection
         */
        virtual void reportLeavingMetalDetection();
        /**
         * transaction Metal was detected
         */
        virtual void reportMetalDetected();
        /**
         * transaction Puk enters Exit
         */
        virtual void reportReachedExit();
        /**
         * transaction a Puk leaves Exit (exits the machine)
         */
        virtual void reportLeavingExit();
        /**
         * transaction button Stop pressed
         */
        virtual void reportStopPressed();
        /**
         * transaction button Start pressed
         */
        virtual void reportStartPressed();

        virtual void reportMintimerToOutletExpired();

        virtual void reportMaxtimerToOutletExpired();

        virtual void ignoreTiming();

        Data* data; /** holding important Data */
    } *statePtr;  /** pointer to current state*/

    struct Idle : public State {
	virtual string getName();
	virtual void reportReachedExit();
	virtual void reportMintimerToOutletExpired();
    };

    struct UntrackedWorkpiece : public State {
        virtual string getName();
        virtual void ignoreTiming();
    };

    struct MissingWorkpiece : public State {
        virtual string getName();
        virtual void ignoreTiming();
    };


    struct Ready : public State
    {
        virtual string getName();
        virtual void reportReachedExit();
        virtual void reportMaxtimerToOutletExpired();
    }; /** waiting puk enters Outlet */

    struct Expecting : public State
    {
        virtual string getName();
        virtual void reportLeavingExit();

    }; /** waiting puk exit Outlet */

      //stateMember;//The memory for the state is part of context object
    Idle stateMember; /* init state **/ //The memory for the state is part of context object
    Data *contextdata; /** store place of data */ //Data is also kept inside the context object

 public:
    /**
    * Constructor
    */
    OutletManager();
    OutletManager(Data *data);
    /**
    * Destructor
    */
    virtual ~OutletManager();
    /**
     * get name of current State
     */
    virtual string getName();
    /**
     * transaction for newPuk
     */
    virtual void reportNewPuk();
    /**
     * transaction for Puk leave Entry
     */
    virtual void reportLeavingEntry();
    /**
     * transaction for Puk enters the ProfileDetection
     */
    virtual void reportEnterProfileDetection();
    /**
     * transaction Puktype?
     */
    virtual void reportPuktype();
    /**
     * transaction a Puk leaves the ProfileDetection
     */
    virtual void reportLeavingProfileDetection();
    /**
     * transaction Puk enters the metal detection
     */
    virtual void reportEnterMetalDetection();
    /**
     * transaction Puk leaves the metal detection
     */
    virtual void reportLeavingMetalDetection();
    /**
     * transaction Metal was detected
     */
    virtual void reportMetalDetected();
    /**
     * transaction Puk enters Exit
     */
    virtual void reportReachedExit();
    /**
     * transaction a Puk leaves Exit (exits the machine)
     */
    virtual void reportLeavingExit();
    /**
     * transaction button Stop pressed
     */
    virtual void reportStopPressed();
    /**
     * transaction button Start pressed
     */
    virtual void reportStartPressed();
    /**
     * transaction for timeout of minimum duration of reaching end of conveyor
     */
    virtual void reportMintimerToOutletExpired();
    /**
     * transaction for timeout of maximum duration of reaching end of conveyor
     */
    virtual void reportMaxtimerToOutletExpired();
    /**
     * clear timing error
     */
    virtual void ignoreTiming();
};

#endif // OUTLETMANAGER_H
