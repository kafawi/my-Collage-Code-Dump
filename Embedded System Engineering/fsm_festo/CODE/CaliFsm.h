/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CaliFsm.h
 * Author: kafa
 *
 * Created on June 27, 2017, 1:55 PM
 */

#ifndef CALIFSM_H
#define CALIFSM_H
//
//#include "timerController.h"
//
//#include <string>
//#include <iostream>
//
//class Data;
//
//using namespace std;
//
//class CaliFsm
//{
// public:
//  CaliFsm(Data * data);
//  virtual ~CaliFsm();
//  void reportNewPuk();
//  void reportLeavingEntry();
//  void reportEnterProfileDetection();
//  void reportLeavingProfileDetection();
//  void reportEnterMetalDetection();
//  void reportLeavingMetalDetection();
//  void reportReachedExit();
//  void reportLeavingExit();
//  void reportStopPressed();
//  void reportStartPressed();
//  void reportResetPressed(); //RESET_BTN,
//  void reportEStopPressed(); //E_STOP_PRESSED,
//  void reportEStopReleased(); //E_STOP_RELEASED,
// private:
//  Data *contextdata_;
//  struct times
//  {
//    int16_t slowEntry;
//    int16_t slowMiddle;
//    int16_t slowExit;
//    int16_t fastEntry;
//    int16_t fastMiddle;
//    int16_t fastExit;
//  } times_;
//  CalibrationData caliData_;
//
//  struct State
//  {//top-level state
//    virtual string getName();
//    virtual int16_t reportNewPuk();
//    virtual int16_t reportLeavingEntry();
//    virtual int16_t reportEnterProfileDetection();
//    virtual int16_t reportLeavingProfileDetection();
//    virtual int16_t reportEnterMetalDetection();
//    virtual int16_t reportLeavingMetalDetection();
//    virtual int16_t reportReachedExit();
//    virtual int16_t reportLeavingExit();
//    /*
//    void reportStopPressed();
//    void reportStartPressed();
//    void reportResetPressed(); //RESET_BTN,
//    void reportEStopPressed(); //E_STOP_PRESSED,
//    void reportEStopReleased(); //E_STOP_RELEASED,
//     */
//    Data* data; // pointer to data, which physically resides inside the context class (contextdata)
//  } *statePtr; // a pointer to current state. Used for polymorphism.
//
//  struct SlowWaitNewPuk : public State
//  {
//    virtual string getName();
//    virtual int16_t reportNewPuk();
//  };
//
//  struct SlowWaitLeavingEntry : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingEntry();
//  };
//
//  struct SlowWaitEnterProfileDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportEnterProfileDetection();
//  };
//
//  struct SlowWaitLeavingProfileDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingProfileDetection();
//  };
//
//  struct SlowWaitEnterMetalDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportEnterMetalDetection();
//  };
//
//  struct SlowWaitLeavingMetalDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingMetalDetection();
//  };
//
//  struct SlowWaitReachedExit : public State
//  {
//    virtual string getName();
//    virtual int16_t reportReachedExit();
//  };
//
//  struct SlowWaitLeavingExit : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingExit();
//  };
//
//  struct FastWaitNewPuk : public State
//  {
//    virtual string getName();
//    virtual int16_t reportNewPuk();
//  };
//
//  struct FastWaitLeavingEntry : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingEntry();
//  };
//
//  struct FastWaitEnterProfileDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportEnterProfileDetection();
//  };
//
//  struct FastWaitLeavingProfileDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingProfileDetection();
//  };
//
//  struct FastWaitEnterMetalDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportEnterMetalDetection();
//  };
//
//  struct FastWaitLeavingMetalDetection : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingMetalDetection();
//  };
//
//  struct FastWaitReachedExit : public State
//  {
//    virtual string getName();
//    virtual int16_t reportReachedExit();
//  };
//
//  struct FastWaitLeavingExit : public State
//  {
//    virtual string getName();
//    virtual int16_t reportLeavingExit();
//  };
//  SlowWaitNewPuk stateMember;
//};

#endif /* CALIFSM_H */
