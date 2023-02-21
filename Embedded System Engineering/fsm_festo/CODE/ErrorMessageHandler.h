/**
 * @brief duplicates behaviour of other conveyor to this instance according to
 *        call received
 * @author Lennart Hartmann
 * @version 15.06.2017
 */
#ifndef ERRORMESSAGEHANDLER_H
#define ERRORMESSAGEHANDLER_H
#include "Data.h"

class ErrorMessageHandler
{
    public:
        ErrorMessageHandler(Data *data);
        virtual ~ErrorMessageHandler();
        void reportErrorClearedAck();
        void reportErrorClearedNoAck();
        void reportErrorNoAck();
        void reportErrorAck();
    protected:

    private:
        Data *data;
};

#endif // ERRORMESSAGEHANDLER_H
