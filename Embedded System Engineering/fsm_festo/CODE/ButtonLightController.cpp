#include "ButtonLightController.h"
#include <iostream>
#include "mcl.h"
#include "HAL_commands.h"
using namespace std;

ButtonLightController::ButtonLightController()
:trans_(*(Mcl::getInstance ()->getChActorOut ()))
,pout_()
,onIluminated(false)
,q1Iluminated(false)
,q2Iluminated(false)
{
  //cout << "ButtonLightController instanciated" << endl;
  pout_.code=BUTTON_LIGHTS;
}

ButtonLightController::~ButtonLightController()
{
     //cout << "ButtonLightController destroyed" << endl;
}

void ButtonLightController::reportStartPressed(){
    //todo use real channel
    pout_.value.i = LED_START_ON; 
    //cout << "actorChannel <- LED_START_ON" << endl;
    //cout << "Start button light on" << endl;
    trans_.push (pout_);
}
void ButtonLightController::reportStopPressed(){
    pout_.value.i = LED_START_OFF; 
    //cout << "actorChannel <- LED_START_OFF" << endl;
    //cout << "Start button light off" << endl;
    trans_.push (pout_);
}
void ButtonLightController::reportQ1Pressed(){
    if(q1Iluminated){
        pout_.value.i = LED_Q1_OFF; 
        //cout << "actorChannel <- LED_Q1_OFF" << endl;
        //cout << "Q1 button light off" << endl;
    }else{
        pout_.value.i = LED_Q1_ON; 
        //cout << "actorChannel <- LED_Q1_ON" << endl;
        //cout << "Q1 button light on" << endl;
    }
    trans_.push (pout_);
}
void ButtonLightController::reportQ2Pressed(){
    if(q1Iluminated){
      pout_.value.i = LED_Q2_OFF; 
        //cout << "actorChannel <- LED_Q2_OFF" << endl;
        //cout << "Q2 button light off" << endl;
    }else{
      pout_.value.i = LED_Q2_ON; 
       //cout << "actorChannel <- LED_Q2_ON" << endl;
       // cout << "Q2 button light on" << endl;
    }
    trans_.push (pout_);
}
