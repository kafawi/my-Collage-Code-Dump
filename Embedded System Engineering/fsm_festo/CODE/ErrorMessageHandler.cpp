/**
 * @brief duplicates behaviour of other conveyor to this instance according to
 *        call received
 * @author Lennart Hartmann
 * @version 15.06.2017
 */
#include "ErrorMessageHandler.h"
#include "WarningLightsController.h"
#include "MotorController.h"
#include "Pukmanager.h"
#include <iostream>

using namespace std;

ErrorMessageHandler::ErrorMessageHandler(Data *data):data(data)
{
    cout << "ErrorMessageHandler instanciated" << endl;
}

ErrorMessageHandler::~ErrorMessageHandler()
{
    cout << "ErrorMessageHandler destroyed" << endl;
}
void ErrorMessageHandler::reportErrorClearedAck(){
    data->warningLights->setFlashSlow(false);
    data->warningLights->setFlashFast(false);
    data->warningLights->setRed(false);
    if(!data->EStopped&&!data->systemOff&&!data->pukMngr->isEmpty()) data->motorCntr->suspend(false);
}
void ErrorMessageHandler::reportErrorClearedNoAck(){
    data->warningLights->setFlashSlow(true);
    data->warningLights->setFlashFast(false);
    data->warningLights->setRed(false);
    if(!data->EStopped&&!data->systemOff&&!data->pukMngr->isEmpty()) data->motorCntr->suspend(false);
}
void ErrorMessageHandler::reportErrorNoAck(){
    data->warningLights->setFlashSlow(false);
    data->warningLights->setFlashFast(true);
    data->warningLights->setRed(false);
    data->motorCntr->suspend(true);
}
void ErrorMessageHandler::reportErrorAck(){
    data->warningLights->setFlashSlow(false);
    data->warningLights->setFlashFast(false);
    data->warningLights->setRed(true);
    data->motorCntr->suspend(true);
}
