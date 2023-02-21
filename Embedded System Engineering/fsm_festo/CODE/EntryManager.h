/**
 * @brief FSM controlling outlet
 * @author Lennart Hartmann
 * @version 05.06.2017
 */
#ifndef ENTRY_MANAGER_H
#define ENTRY_MANAGER_H

#include "Data.h"

#include <string>

/**
 * @class contains the FSM for the last Section on the machine
 *
 */
class EntryManager
{

private:
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
        virtual std::string getName();
        /**
        * transaction for newPuk
        */
        virtual void reportNewPuk();
        /**
        * transaction for Puk leave Entry
        */
        virtual void reportLeavingEntry();
        Data* data; /** holding important Data */
    } *statePtr;  /** pointer to current state*/

    struct Ready : public State
    {
        virtual std::string getName();
        virtual void reportNewPuk();
    };

    struct Done : public State
    {
        virtual std::string getName();
        virtual void reportLeavingEntry();
    }; /** waiting puk exit Outlet */

    //stateMember;//The memory for the state is part of context object
    Ready stateMember; /* init state **/ //The memory for the state is part of context object

//    Data contextdata; /** store place of data */ //Data is also kept inside the context object
    Data *contextdata; /** store place of data */ //Data is also kept inside the context object

 public:
    /**
    * Constructor
    */
    EntryManager();
    EntryManager(Data *data);
    /**
    * Destructor
    */
    virtual ~EntryManager();
    /**
     * get name of current State
     */
    virtual std::string getName();
    /**
     * transaction for newPuk
     */
    virtual void reportNewPuk();
    /**
     * transaction for Puk leave Entry
     */
    virtual void reportLeavingEntry();

    bool receivingEnd;
};

#endif // ENTRY_MANAGER_H
