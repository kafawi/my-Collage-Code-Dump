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
#include <thread>
#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#endif
void replay();

#define LOG_REPLAY \
ReplayLogger::getLogger().log("")
using namespace std;
static timeval gettime;

enum AREA {
	INIT_LOGGER, SENSOR, HEIGHTMEASURE, SERIELL, TIMER
};

class ReplayLogger {
public:
	static ReplayLogger& getLogger()   // Meyers Singleton.
	{
		static ReplayLogger Instance; // Will be delete at the end.
		return Instance;
	}
	ofstream& log(string s) // return ofstream, so cascading <<..<<..<< is possible.
			{
		gettimeofday(&gettime, NULL);
		unsigned long long utime = gettime.tv_sec * 1000000 + gettime.tv_usec;
		utime = utime * 1000000;
		utime = utime + gettime.tv_usec;
//		unsigned long long sec = gettime.tv_sec;
//		cout << "sec: " << sec << endl;
//		sec = sec * 1000000;
//		cout << "sec*1000000: " << sec << endl;
//		cout << "utime: " << utime << endl;
//		unsigned long long usec = gettime.tv_usec;
//		cout << "sec: " << sec << endl;
//		cout << "usec" << usec << endl;
//		unsigned long long newtime = sec + usec;
//		cout << "newtime: " << newtime << endl;

		logfile_ << utime << s << " "; // time ticks in us.
		return logfile_;
	}

private:
	ReplayLogger() // make these private because of singleton.
	{
		//logfile_.open("Replaylogging.txt", ios::trunc);
		logfile_.open("../root/Replaylogging.txt", ios::trunc);
		logfile_ << "LOGFILE. Build: " << __DATE__ << ", " << __TIME__ << endl;
	}
	~ReplayLogger() {
		logfile_ << "END OF LOGFILE" << endl;
		logfile_.close();
	}
	ofstream logfile_;
};

