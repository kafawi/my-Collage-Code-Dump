/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.h
 * Author: kafa
 *
 * Created on June 26, 2017, 6:37 AM
 */

#ifndef TEST_H
#define TEST_H
// MCL
#include "ButtonLightController.h"
#include "Data.h"
#include "EStopFSM.h"
#include "EntryManager.h"
#include "ErrorMessageHandler.h"
#include "GateController.h"
#include "GateManager.h"
#include "HAL_commands.h"
#include "HDI_commands.h"
#include "HDI_Manager.h"
#include "IManager.h"
#include "InputMultiplexer.h"
#include "MCL_signals.h"
#include "MotorController.h"
#include "OutletManager.h"
#include "ProfileDetectionController.h"
#include "ProfileDetectionManager.h"
#include "ProfileDetection_signals.h"
#include "Puk.h"
#include "PukSequenceTracker.h"
#include "Pukmanager.h"
#include "SerialManager.h"
#include "Serial_commands.h"
#include "Serial_protocol.h"
#include "SystemOffFSM.h"
#include "WarningLightsController.h"
#include "actor.h"
#include "analogPortStrat.h"
#include "analogSensor.h"
#include "channel.h"
#include "debugLogger.h"
#include "digitalPortStrat.h"
#include "gpio.h"
#include "hal.h"
#include "halDispatcher.h"
#include "hdi.h"
#include "irqHandler.h"
#include "lock.h"
#include "mcl.h"
#include "mclDispatcher.h"
#include "mgt.h"
#include "sPulse.h"
#include "sensor.h"
#include "serialController.h"
#include "serialDispatcher.h"
#include "serialReceiver.h"
#include "serialSender.h"
#include "serialStrat.h"
#include "sio.h"
#include "thread.h"
#include "timer.h"
#include "timerController.h"


// Layercommunication


void testSerialMcl();
void testMcl();
void testAnalogSensorMcl();
void testHalSW();
void testHalHW();
void testSerialHW();
void testTimer();

// Automatetests
void testEntryManager();
void testErrorMessageHandler();


#endif /* TEST_H */

