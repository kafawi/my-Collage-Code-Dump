/**
 * @brief   Controlling warning lights by addressing HAL
 * @author  Lennart Hartmann
 * @version 07.06.2017
 */
#include "WarningLightsController.h"
#include "thread.h"
#include "HAL_commands.h"
#include "mcl.h"
#include "mgt.h"
#include <iostream>
#include <unistd.h>

using namespace std;
WarningLightsController::WarningLightsController ()
: flashPeriod_ (0)
, flashCol_ (YELLOW)
, flashCountDown_ (0)
, redOn_ (false)
, yellowOn_ (false)
, greenOn_ (false)
, trans_ (*(Mcl::getInstance ()->getChActorOut ()))
, pout_ ()
, th_ (nullptr)
, worker_ (nullptr)
{
  pout_.code = STATUS_LIGHTS;
  worker_ = new Worker (*(this));
  stop ();
  th_ = new Thread ((*worker_));
  //stop();
}
WarningLightsController::~WarningLightsController ()
{
  terminate ();
  th_->join ();
  delete (th_);
  delete (worker_);
}
void
WarningLightsController::setGreen (bool on)
{
  greenOn_ = on;
  if (on)
  {
    pout_.value.i = GREEN_ON;
    trans_.push (pout_);
    cout << "actorChannel <- GREEN_ON" << endl;
  }
  else
  {
    pout_.value.i = GREEN_OFF;
    trans_.push (pout_);
    cout << "actorChannel <- GREEN_OFF" << endl;
  }
}
void
WarningLightsController::setRed (bool on)
{
  setFlashFast(false);
  setFlashSlow(false);
  redOn_ = on;
  if (on)
  {

    pout_.value.i = RED_ON;
    trans_.push (pout_);
    cout << "actorChannel <- RED_ON" << endl;
  }
  else
  {
    pout_.value.i = RED_OFF;
    trans_.push (pout_);
    cout << "actorChannel <- RED_OFF" << endl;
  }
}
void
WarningLightsController::setYellowFlash (bool on)
{
  setYellowFlash(false);
  if (on)
  {
    flashCol_ = YELLOW;
    flashPeriod_ = PERIOD1000MS;
    flashCountDown_ = FLASHTIMESYELLOW;
    conti ();
    //todo use real Channel & Thread
    cout << "workerSlow: resume | actorChannel <- YELLOW_OFF/YELLOW_ON" << endl;
  }
  else
  {
    stop ();
    //todo use real Channel & Thread
    cout << "workerSlow: suspend" << endl;
  }
}
void
WarningLightsController::setFlashFast (bool on)
{
  if (on)
  {
    flashCol_ = RED;
    flashPeriod_ = PERIOD500MS;
    conti ();
    //todo use real & Thread
    cout << "workerFast: resume | actorChannel <- RED_OFF/RED_ON" << endl;
  }
  else
  {
    stop ();
    //todo use real Channel & Thread
    cout << "workerFast: suspend" << endl;
  }
}
void
WarningLightsController::setFlashSlow (bool on)
{
  if (on)
  {
    flashCol_ = RED;
    flashPeriod_ = PERIOD1000MS;
    conti ();
    //todo use real Channel & Thread
    cout << "workerSlow: resume | actorChannel <- RED_OFF/RED_ON" << endl;
  }
  else
  {
    stop ();
    //todo use real Channel & Thread
    cout << "workerSlow: suspend" << endl;
  }
}
void
WarningLightsController::step ()
{
  Pulse_t p;
  p.code =STATUS_LIGHTS;

  if (flashCol_ == RED)
  {
    p.value.i = RED_ON;
  }
  else if (flashCol_ == YELLOW)
  {
    p.value.i = YELLOW_ON;
  }
  trans_.push (p);
  mgt::threadSleep (flashPeriod_ / 2);
  if (flashCol_ == RED)
  {
    p.value.i = RED_OFF;
  }
  else if (flashCol_ == YELLOW)
  {
    p.value.i = YELLOW_OFF;
  }
  trans_.push (p);
  mgt::threadSleep (flashPeriod_ / 2);
  if (flashCol_ == YELLOW)
  {
    flashCountDown_--;
    if (flashCountDown_ <= 0)
    {
      stop ();
    }
  }
}
void
WarningLightsController::stop ()
{
  //usleep(10);
  if (redOn_)
  {
    pout_.value.i = RED_ON;
    trans_.push (pout_);
  }
  else if (yellowOn_)
  {
    pout_.value.i = YELLOW_ON;
    trans_.push (pout_);
  }
  else if (greenOn_)
  {
    pout_.value.i = GREEN_ON;
    trans_.push (pout_);
  }
  isStopped_=true;
}
