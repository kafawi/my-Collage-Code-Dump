/**
 * @brief Header protocol for serial messenging to serial port
 * @author Alexander Mendel
 * @version 09.06.2017
 */

#include <iostream>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include "SerialManager.h"


SerialManager::SerialManager()
//for receivfing pulses?
//: receiver_ (*(SerialManager::getInstance() ->getSerialInChannel ()))
//, serialInChannel_()
{
  std::cout << "serial manager ctor" << std::endl;
}
/*
PulseChannel *
	SerialManager::getSerialInChannel() {
	return &serialInChannel_;
}

SerialManager*
SerialManager::getInstance()
{
	if (nullptr == instance_) {
		initMtx_.acquire(); //do i need this
			if(nullptr == instance_) {
				instance_ = new SerialManager();
			}
			initMtx_.release();
	}
	return instance_;

}
*/
void receive_puk_packet(const uint16_t pukId, const uint16_t pukType,
		const bool eject) {

}
void receive_acknowledge() {

}
void receive_on_event() {

}
void receive_off_event() {

}
void receive_error_pending_event() {

}
void receive_error_cleared_event() {

}
void receive_error_unacknowledged_event() {

}
void receive_error_acknowledged_event() {

}




SerialManager::~SerialManager(){
	//blubb
}
