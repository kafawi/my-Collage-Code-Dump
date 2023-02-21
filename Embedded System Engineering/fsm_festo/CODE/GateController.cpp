/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GateController.cpp
 * Author: kafa
 * 
 * Created on June 8, 2017, 5:34 AM
 */

#include "GateController.h"
#include "HAL_commands.h"
#include "GateController.h"
#include "mcl.h"
GateController::GateController ()
:trans_(*(Mcl::getInstance ()->getChActorOut ()))
,pout_()
{ pout_.code=GATE; }

void
GateController::open(){
  pout_.value.i = GATE_OPEN;
  trans_.push (pout_);
};

void
GateController::close (){
  pout_.value.i = GATE_CLOSE;
  trans_.push (pout_);
};


GateController::~GateController () { }
