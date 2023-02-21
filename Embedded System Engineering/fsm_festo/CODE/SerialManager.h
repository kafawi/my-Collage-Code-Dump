/*
 * SerialSender.h
 *
 *  Created on: 09.06.2017
 *      Author: abs430
 */
#ifndef SERIALMANAGER_H_
#define SERIALMANAGER_H_
#include "serialSender.h"
//#include something

class SerialManager {

public:
	SerialManager();
	~SerialManager();
	void receive_puk_packet(const uint16_t pukId, const uint16_t pukType,
			const bool eject);
	void receive_acknowledge();
	void receive_on_event();
	void receive_off_event();
	void receive_error_pending_event();
	void receive_error_cleared_event();
	void receive_error_unacknowledged_event();
	void receive_error_acknowledged_event();

};

#endif /*SERIALMANAGER_H_ */
