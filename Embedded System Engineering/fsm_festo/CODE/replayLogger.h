//============================================================================
// Name        : Logger.h
// Author      : Nils Egge
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

using namespace std;
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sys/time.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
//#include <thread>
#include "thread.h"
#include "channel.h"
#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#endif

#define DEFAULT_NAME "Replaylogging"
#if defined(__QNXNTO__)
#define PATH "../root/"
#else
#define PATH "./"
#endif

#define LOG_REPLAY(s) \
ReplayLogger::getLogger(DEFAULT_NAME).log(s)

#define ISREPLAYING \
(ReplayLogger::getLogger(DEFAULT_NAME).isReplay)

using namespace std;

enum AREA
{
  INIT_LOGGER, SENSOR, HEIGHTMEASURE, SERIELL, TIMER
};

#define LOG_REPLAY_INIT \
LOG_REPLAY("") <<  static_cast<int>(INIT_LOGGER) << endl; 

#define LOG_REPLAY_PULSE(area, pulse) \
if (!ISREPLAYING) \
LOG_REPLAY("") << static_cast<int>(area) \
<< " " << static_cast<int>(pulse.code) << " " \
<< static_cast<int>(pulse.value.i) << endl;  \
if (!ISREPLAYING)


class ReplayLogger : public Runnable
{
 public:
  static ReplayLogger& getLogger(string fileName); // Meyers Singleton.
  ofstream& log(string s); // return ofstream, so cascading <<..<<..<< is possible.
  void run();
  void replay(string fileName);
 private:
  ReplayLogger(string fileName); // make these private because of singleton.
  ~ReplayLogger();
  ofstream logfile_;
  string fileName_;
  PulseTransmitter mclTrans_;
  PulseTransmitter heightTrans_;
  PulseTransmitter serialTrans_;
  Pulse_t pout_;
  Worker *worker_;
 public:
    Thread *rpTh_;
  bool isReplay;

};

int replaytest();
