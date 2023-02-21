///*
// * ReplayLogger.cc
// *
// *  Created on: 12.06.2017
// *      Author: abx975
// */
//
//#include "logAndReplayLogger.h"
//#include <iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <fstream>
//#include <unistd.h>
//#include <thread>
//#include <sys/neutrino.h>
//
//using namespace std;
//
///**
// Replay is the thread, which is reading the Loggingfile and write the Events in the Channels.
// */
//void replay() {
//	/**
//	 Open the File to read
//	 */
//	std::ifstream input("../root/Replaylogging.txt");
//	if (!input) {
//		std::cerr << "Fehler beim Oeffnen der Datei " << "Replaylogging.txt"
//				<< endl;
//	}
//
//	string line;
//	char values[1024];
//	int usleepExecutionTime = 1995;
//
//	getline(input, line);
//	cout << "Start the Replay with the " << line << endl;
//
//	// put the Values of the line in
//	char * pEnd;
//	long int utime, oldTime;
//	int area, event, waitTime;
//	while (getline(input, line)) {
//		// put the values in the variables
//		strcpy(values, line.c_str());
//		oldTime = utime;
//		utime = strtol(values, &pEnd, 0);
//		cout << "utime: " << utime << endl;
//		area = strtol(pEnd, &pEnd, 17);
//		event = strtol(pEnd, NULL, 19);
//		waitTime = (utime - oldTime);
//
//		if (waitTime < usleepExecutionTime) {
//			waitTime = -1;
//		} else {
//			waitTime = waitTime - usleepExecutionTime;
//		}
//
//		cout << "utime: " << utime << " area: " << area << " event: " << event
//				<< " waitTime: " << waitTime << endl;
//		switch (area) {
//		case SENSOR: {
//			usleep(waitTime);
//			cout << "Event in den Sensor Channel schreiben.\n";
////TODO? check
////            Pulse_t pout;
////            pout.code = pulse.code; //INCOMMING_CODE
////            pout.value = pulse.value.sival_int;
////            transmitter_.push (pout);
//			break;
//		}
//		case HEIGHTMEASURE: {
//			usleep(waitTime);
//			cout << "Event in den H�henSensor Channel schreiben.\n";
////TODO
//
//			break;
//		}
//		case SERIELL: {
//			usleep(waitTime);
//			cout << "Event in den Seriellen Channel schreiben.\n";
////TODO
//
//			break;
//		}
//		case TIMER: {
//			usleep(waitTime);
//			cout << "Event in den Timer Channel (MCL) schreiben.\n";
////TODO
//			break;
//		}
//		case INIT_LOGGER:
//			if (oldTime == 0) {
//				oldTime = utime;
//			}
//			break;
//		}
//	}
//}
//
////int main()
////{
////    LOG_REPLAY << INIT_LOGGER << endl;
////    usleep(100000);
////    LOG_REPLAY << SENSOR << " " << 1 << endl;
////    usleep(200000);
////    LOG_REPLAY << HEIGHTMEASURE << " " << 2 << endl;
////    usleep(500000);
////    LOG_REPLAY << SERIELL << " " << 4 << endl;
////    usleep(2000000);
////    LOG_REPLAY << TIMER << " " << 3 << endl;
////
////    //Launch a thread
////    std::thread replaythread(replay);
////
////    //Join the thread with the main thread
////    replaythread.join();
////    return 0;

//
#include "replayLogger.h"
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

/**
 Replay is the thread, which is reading the Loggingfile and write the Events in the Channels.
 */
/*
void replay() {
	 //Open the File to read
	std::ifstream input("../root/Replaylogging.txt");
	if (!input) {
		std::cerr << "Fehler beim Oeffnen der Datei " << "Replaylogging.txt"
				<< endl;
	}

	string line;
	char values[2048];

	getline(input, line);
	cout << "Start the Replay with the " << line << endl;

	// put the Values of the line in
	char * pEnd;
	unsigned long int  utime = 0, oldTime = 0;
	int area = 0, event = 0, waitTime = 0;
	while (getline(input, line)) {
		// put the values in the variables
		strcpy(values, line.c_str());
		cout << "values: " << values << endl;
		oldTime = utime;
		cout << "oldTime: " << oldTime << "\t";
		utime = strtoll(values, &pEnd,0);
		cout << "utime: " << utime << "\t";
		area = strtol(pEnd, &pEnd, 17);
		cout << "area: " << area << "\t";
		event = strtol(pEnd, NULL, 19);
		cout << "event: " << event << "\t";
		waitTime = (utime - oldTime);

		switch (area) {
		case SENSOR: {
			usleep(waitTime);
			cout << "Event in den Sensor Channel schreiben.\n";
//TODO? check
//            Pulse_t pout;
//            pout.code = pulse.code; //INCOMMING_CODE
//            pout.value = pulse.value.sival_int;
//            transmitter_.push (pout);
			break;
		}
		case HEIGHTMEASURE: {
			usleep(waitTime);
			cout << "Event in den H�henSensor Channel schreiben.\n";
//TODO

			break;
		}
		case SERIELL: {
			usleep(waitTime);
			cout << "Event in den Seriellen Channel schreiben.\n";
//TODO

			break;
		}
		case TIMER: {
			usleep(waitTime);
			cout << "Event in den Timer Channel (MCL) schreiben.\n";
//TODO
			break;
		}
		case INIT_LOGGER:
			if (oldTime == 0) {
				oldTime = utime;
			}
			break;
		}
	}
}
*/
//
//int main()
//{
//    LOG_REPLAY << INIT_LOGGER << endl;
//    usleep(100000);
//    LOG_REPLAY << SENSOR << " " << 1 << endl;
//    usleep(200000);
//    LOG_REPLAY << HEIGHTMEASURE << " " << 2 << endl;
//    usleep(500000);
//    LOG_REPLAY << SERIELL << " " << 4 << endl;
//    usleep(2000000);
//    LOG_REPLAY << TIMER << " " << 3 << endl;
//
//    //Launch a thread
//    std::thread replaythread(replay);
//
//    //Join the thread with the main thread
//    replaythread.join();
//
//    return 0;
//}
//
