/**
 * @brief FSM controlling behaviour if emergency stop has to be resolved
 * @author Lennart Hartmann
 * @version 06.06.2017
 */
#ifndef ESTOPFSM_H
#define ESTOPFSM_H

#include<iostream>
#include "Data.h"

class EStopFSM{
private:
    struct EStopState
    {
        /**
        * get the name of state (debug thing)
        * @return name of state
        */
        virtual std::string getName();
        virtual void reportEStopPressed();
        virtual void reportEStopReleased();
        virtual void reportResetPressed();
        virtual void reportEStopAntiPrellTimer();
        Data* data; /** holding important Data */
    } *statePtr;  /** pointer to current state*/

    struct Ok : public EStopState
    {
        virtual std::string getName();
        virtual void reportEStopPressed();
    };
    struct EStopped : public EStopState{
      virtual std::string getName();
      virtual void reportEStopReleased();
      
    };
    struct EStoppedBeforAntiPrellTimer : public EStopState
    {
        virtual std::string getName();
        virtual void reportEStopAntiPrellTimer();
    };
    
    struct AcknoledgedBeforAntiPrellTimer : public EStopState
    {
        virtual std::string getName();
        virtual void reportEStopAntiPrellTimer();
    };
    
    struct Acknoledged : public EStopState
    {
        virtual std::string getName();
        virtual void reportEStopPressed();
        virtual void reportResetPressed();
    };

    //stateMember;//The memory for the state is part of context object
    Ok stateMember; /* init state **/ //The memory for the state is part of context object
    Data *contextdata; /** store place of data */ //Data is also kept inside the context object
 public:
    /**
    * Constructor
    */
    EStopFSM();
    EStopFSM(Data *data);
    /**
    * Destructor
    */
    virtual ~EStopFSM();
    /**
     * get name of current State
     */
    virtual std::string getName();
    /**
     * transaction for pressing EStop button
     */
    void reportEStopPressed();
    /**
     * transaction for releasing EStop button
     */
    void reportEStopReleased();
    /**
     * transaction for pressing Reset button
     */
    void reportResetPressed();
    /**
     *  transaction for expired Anitprelltimer
     */
    void reportEStopAntiPrellTimer();
};





#endif // ESTOPFSM_H
