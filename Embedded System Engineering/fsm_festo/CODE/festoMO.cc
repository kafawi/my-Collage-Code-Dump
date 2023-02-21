//#include "mgt.h"
//#include "channel.h"
//#include "thread.h"
//
//#include <cstdlib>
//#include <iostream>
//#include <thread>
//#if defined(__QNXNTO__)
//#include <hw/inout.h>
//#include <sys/neutrino.h>
//#endif
//#include <chrono>
//
//#include "replayLogger.h"
//
//
//// See Manual M104-DIO-48S.A1i, Cap. 5: Programming
//#define CTRL_REG_GROUP0     0x303
//#define DEFAULT_PORTS_SETTINGS 0x8A
//
//#include "hal.h"
//#include "mcl.h"
//#include "channel.h"
//#include "sio.h"
//#include "hdi.h"
//
//
//using namespace std;
//
//int main(int argc, char** argv) {
//
//
//	std::cout << "TESTEST " <<std::endl;
//#if defined(__QNXNTO__)
//	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
//		std::cout << "Can't get Hardware access, therefore can't do anything."
//			<< std::endl;
//	return EXIT_FAILURE;
//	}
//#endif
//  Mcl *mcl = Mcl::getInstance ();
//  Hal *hal = Hal::getInstance ();
//  Sio *sio = Sio::getInstance();
//  Hdi *hdi = Hdi::getInstance ();
//  hal->setChDigitalSensorOut(mcl->getChMasterControlIn ());
//  hal->setChAnalogSensorOut (mcl->getChAnalogSensorIn ());
//  mcl->setChActorOut (hal->getChActorIn ());
//  sio->setChEventOut (mcl->getChSerialIn ());
//  mcl->setChSerialOut (sio->getChCmdIn ());
//  hdi->setChEventOut (mcl->getChHidIn ());
//  mcl->setChHidOut (hdi->getChCmdIn ());
//
// if (mcl->getChAnalogSensorIn () == nullptr){
//	 std::cout << "hilfehilfe" << std::endl;
// }
// if (mcl->getChAnalogSensorIn () == hal->getChAnalogSensorOut()){
//	 std::cout << "GROOVIE" << std::endl;
// }
//
//  cout << endl <<"Is this machine the first in queue?" << endl;
//  cout << "Write 'y' for YES or 'n' for NO and confirm with enter:";
//  bool accepted = false;
//  bool isReceivingEnd = false;
//  while (!accepted){
//    string s;
//    cin  >> s;
//    if (s.compare ("y")==0){
//      isReceivingEnd = false;
//      accepted=true;
//    } else if (s.compare ("n")==0){
//      isReceivingEnd = true;
//      accepted=true;
//    } else {
//      cout << "I do not understand" << endl;
//    }
//  }
//  mcl->init (isReceivingEnd);
//  hal->init ();
//  sio->init ();
//
//  cout << endl <<"Do you want to replay last run?(HW in Loop)" << endl;
//  cout << "Write 'y' for YES or 'n' for NO and confirm with enter:";
//  accepted = false;
//  while (!accepted){
//    string s;
//    cin  >> s;
//    if (s.compare ("y")==0){
//      cout << endl <<"Please enter logfilename" << endl;
//      while(!accepted){
//        cin >> s;
//          ReplayLogger::getLogger (DEFAULT_NAME).replay (s);
//          ReplayLogger::getLogger (DEFAULT_NAME).rpTh_->join();
//          accepted = true;
//      }
//    } else if (s.compare ("n")==0){
//      LOG_REPLAY_INIT;
//      accepted=true;
//    } else {
//      cout << "I do not understand" << endl;
//    }
//  }
//  // TESTS
//  cout << "-------------waiting--------------" << endl;
//  //replaytest();
//
//
//  //hid->init ();
//  //hid->destroy ();
//  sio->destroy ();
//  hal->destroy ();
//  mcl->destroy ();
//  std::cout << "done!" << std::endl;
//  return 0;
//}
