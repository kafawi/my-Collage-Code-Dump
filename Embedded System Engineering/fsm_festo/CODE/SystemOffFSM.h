#ifndef SYSTEMOFFFSM_H
#define SYSTEMOFFFSM_H
#include "Data.h"
#include <iostream>

class SystemOffFSM
{
private:
    struct IrregularState
    {
        /**
        * get the name of state (debug thing)
        * @return name of state
        */
        virtual std::string getName();

        virtual void reportStopPressed();

        virtual void reportStartPressed();
        Data* data; /** holding important Data */
    } *statePtr;  /** pointer to current state*/

    struct On : public IrregularState
    {
        virtual std::string getName();
        virtual void reportStopPressed();
        virtual void reportStartPressed();
    };

    struct Off : public IrregularState
    {
        virtual std::string getName();
        virtual void reportStartPressed();
        virtual void reportStopPressed();
    };

    //stateMember;//The memory for the state is part of context object
    On stateMember; /* init state **/ //The memory for the state is part of context object
    Data *contextdata; /** store place of data */ //Data is also kept inside the context object

 public:
    /**
    * Constructor
    */
    SystemOffFSM();
    SystemOffFSM(Data *data);
    /**
    * Destructor
    */
    virtual ~SystemOffFSM();
    /**
     * get name of current State
     */
    virtual std::string getName();
    /**
     * transaction for handling stop button
     */
    void reportStopPressed();
    /**
     * transaction for handling start button
     */
    void reportStartPressed();
};

#endif // SYSTEMOFFFSM_H
