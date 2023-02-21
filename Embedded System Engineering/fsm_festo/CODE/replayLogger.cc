/**
 * ReplayLogger.cc
 *
 *  Created on: 12.06.2017
 *      Author: abx975
 */

#include "replayLogger.h"
#include "mcl.h"
#include "MCL_signals.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <thread>
#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#endif
using namespace std;
ReplayLogger::ReplayLogger (string fileName)
: logfile_ ()
, fileName_ (fileName)
, mclTrans_ (*(Mcl::getInstance ()->getChMasterControlIn ()))
, heightTrans_ (*(Mcl::getInstance ()->getChAnalogSensorIn ()))
, serialTrans_ (*(Mcl::getInstance ()->getChSerialIn ()))
, pout_ ()
, worker_ (nullptr)
, rpTh_ (nullptr)
, isReplay(false)
{
  worker_ = new Worker (*this);
  char  name[300] = {PATH DEFAULT_NAME __TIME__ ".txt"};
  logfile_.open (name, ios::trunc);
  logfile_ << "LOGFILE. Build: " << __DATE__ << ", " << __TIME__ << endl;
}
ReplayLogger::~ReplayLogger ()
{
  delete (worker_);
  logfile_ << "END OF LOGFILE" << endl;
  logfile_.close ();
}

static timeval gettime;
ofstream &
ReplayLogger::log (string s) // return ofstream, so cascading <<..<<..<< is possible.
{
  gettimeofday (&gettime, NULL);
  unsigned long long utime = gettime.tv_sec * 1000000 + gettime.tv_usec;
  //utime = utime * 1000000;
  //utime = utime + gettime.tv_usec;
  logfile_ << utime << s << " "; // time ticks in us.
  return logfile_;
}
ReplayLogger&
ReplayLogger::getLogger (string fileName = DEFAULT_NAME) // Meyers Singleton.
{
  static ReplayLogger Instance (fileName); // Will be delete at the end.
  return Instance;
}
void
ReplayLogger::run ()
{
  std::ifstream input (PATH + fileName_);
  if (!input)
  {
    std::cerr << "Fehler beim Oeffnen der Datei " << fileName_
            << endl;
  }
  string line;
  char values[2048];

  getline (input, line);
  cout << "Start the Replay with the " << line << endl;

  // put the Values of the line in
  char * pEnd;
  unsigned long long utime = 0, oldTime = 0;
  int area = 0, waitTime = 0;
  int8_t code = -1;
  int32_t value = -1;
  while (getline (input, line))
  {
    // put the values in the variables
    strcpy (values, line.c_str ());
    oldTime = utime;
    utime = strtoll (values, &pEnd, 0);
    area = static_cast<enum AREA>(strtol (pEnd, &pEnd, 10));
    code = static_cast<int8_t>(strtol (pEnd, &pEnd, 10));
    pout_.code = code;
    value = static_cast<int32_t>(strtol (pEnd, NULL, 10));
    pout_.value.i = value;
    waitTime = (utime - oldTime);
    // end 
    /*
    cout << endl;
    cout << "values: " << values << endl;
    cout << "oldTime: " << oldTime << " - ";
    cout << "utime: " << utime << " - ";
    cout << "area: " << area << " - ";
    cout << "value: " << value << " - ";
     cout << "code: " << static_cast<int32_t>(code) << " - ";
    cout << endl;
     */
    switch (area)
    {
      case SENSOR:
      {
        usleep (waitTime);
        //cout << "Event in den Sensor Channel schreiben.\n";
        mclTrans_.push (pout_);
        break;
      }
      case HEIGHTMEASURE:
      {
        usleep (waitTime);
        //cout << "Event in den HoehenSensor Channel schreiben.\n";
        heightTrans_.push (pout_);
        break;
      }
      case SERIELL:
      {
        usleep (waitTime);
        //cout << "Event in den Seriellen Channel schreiben.\n";
        serialTrans_.push (pout_);
        break;
      }
      case TIMER:
      {
        usleep (waitTime);
        //cout << "Event in den Timer Channel (MCL) schreiben.\n";
        mclTrans_.push (pout_);
        break;
      }
      case INIT_LOGGER:
        if (oldTime == 0)
        {
          oldTime = utime;
        }
        break;
    }
  }
  sleep (2);
  isReplay = false;
  cout << "ENDE" <<endl;
  
}
/**
 Replay is the thread, which is reading the Loggingfile and write the Events in the Channels.
 */
void
ReplayLogger::replay (string fileName)
{
  isReplay = true;
  if (fileName != fileName_){
    fileName_ = fileName;
  //  logfile_.close ();
  //  logfile_.open (PATH + fileName, ios::trunc);
  }
  rpTh_ = new Thread (*(worker_));
  //rpTh_->detach ();
}
//
int
replaytest ()
{
  Pulse_t p;
  LOG_REPLAY_INIT;
  usleep (100000);
  p.code = 1;
  p.value.i = 0;
  LOG_REPLAY_PULSE (SENSOR, p);
  usleep (200000);
  p.code = 3;
  p.value.i = 5685;
  LOG_REPLAY_PULSE (HEIGHTMEASURE, p);
  usleep (500000);
  p.code = 2;
  p.value.i = 284097;
  LOG_REPLAY_PULSE (SERIELL, p);
  usleep (2000000);
  p.code = 1;
  p.value.i = 2345;
  LOG_REPLAY_PULSE (TIMER, p);

  //Launch a thread
  ReplayLogger::getLogger ().replay (DEFAULT_NAME);
  //Join the thread with the main thread
  sleep (2);
  return 0;
}
