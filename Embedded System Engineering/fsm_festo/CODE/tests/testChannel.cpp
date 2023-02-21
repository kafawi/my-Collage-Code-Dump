/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * @file  testChannel.cpp
 * 
 * Testing the basic function of the Channel
 * 
 * @author kafa
 * 
 * Created on May 21, 2017, 5:15 PM
 */

#include <cstdlib>
#include <iostream>

//#include "./HAL/hal.h"
//#include "./SIO/sio.h"
#include "../mgt.h"
#include "../channel.h"
#include "../thread.h"
//#include "./MCL/mcl.h"
//#include "./HDI/hdi.h"
using namespace std;

using namespace std;


class Prod: public Runnable{

private:
    PulseTransmitter &pt_;
public:
Prod(PulseTransmitter & pt):pt_(pt){};

void connect(PulseChannel & pc){
    pt_.connect(pc);
}

virtual void run(){
  pt_.push(Pulse_t{12,99});
  //mgt::threadSleep(1);
  pt_.push(Pulse_t{12,44});
}

void operator()(){
  pt_.push(Pulse_t{12,99});
}
};

class Cons: public Runnable{

private:
    PulseReceiver &pr_;
public:
Cons(PulseReceiver & pr):pr_(pr)
{
};

void connect(PulseChannel & pc){
    pr_.connect(pc);
}

virtual void run(){
  Pulse_t pp;
  pp = pr_.pull();
  cout << "code: "<< static_cast<int>(pp.code) << " value: " << pp.value << endl;
  //mgt::threadSleep(1);

  pp = pr_.pull();
  cout << "code: "<< static_cast<int>(pp.code) << " value: " << pp.value << endl;
}

void operator()(){
  Pulse_t pp;
  pp = pr_.pull();
  cout << "code: "<< static_cast<int>(pp.code) << " value: " << pp.value << endl;
}
};
/*
 *
 */

int maintest(int argc, char** argv) {


	std::cout << "Channel " <<std::endl;
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		std::cout << "Can't get Hardware access, therefore can't do anything."
			<< std::endl;
	return EXIT_FAILURE;
	}

    PulseChannel ppp;

    PulseReceiver plr(ppp);
    PulseTransmitter plt(ppp);
    Cons co( plr );
    Prod pr( plt );

    std::cout << " start worker " << std::endl;
    thread thpr( (Worker(pr)) );
    thread thco( (Worker(co)) );


    thco.join();
    thpr.join();

    std::cout << "press a button to end " << std::endl;
    //std::cin.get();
    return 0;
}

