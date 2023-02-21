/*
 * SerialSender.cc
 *
 *  Created on: 08.06.2017
 *      Author: abs430
 */
/*
#include <iostream>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include "SerialSender.h"

SerialSender::SerialSender() {
	this->dev_ = "/dev/ser1";
	this->fdesc_ = open(this->dev_, O_RDWR);
	if (this->fdesc_ == -1) {
		exit(-1);
	}

	// Configure Serial Interface
	this->config();
}

//shouldnt be here?
void SerialSender::config(void) {
	struct termios ts;
	tcflush(this->fdesc_, TCIOFLUSH);
	tcgetattr(this->fdesc_, &ts);
	cfsetispeed(&ts, B19200);
	cfsetospeed(&ts, B19200);
	ts.c_cflag &= ~CSIZE;
	ts.c_cflag &= ~CSTOPB;
	ts.c_cflag &= ~PARENB;
	ts.c_cflag |= CS8;
	ts.c_cflag |= CREAD;
	ts.c_cflag |= CLOCAL;
	tcsetattr(this->fdesc_, TCSANOW, &ts);
}

void SerialSender::send_puk_packet(const uint16_t pukId, const uint16_t pukType,
		const bool eject) {
	Header header;
	Data data;
	header.packet_size = sizeof(data);
	header.type = PUK_TRANSFER;

	data.puk_id = pukId;
	data.puk_type = pukType;
	data.eject = eject;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
	//send data
	int sendData = write(this->fdesc_, &data, header.packet_size);
	if (sendData <= 0) {
		std::perror("sending data failed");
	} else { //reset send
		sendData = 0;
	}
}

void SerialSender::send_acknowledge() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = ACKNOWLEDGE;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}

}

void SerialSender::send_on_event() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = ON_EVENT;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
}

void SerialSender::send_off_event() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = OFF_EVENT;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
}

void SerialSender::send_error_pending_event() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = ERROR_PENDING_EVENT;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
}

void SerialSender::send_error_cleared_event() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = ERROR_CLEARED_EVENT;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
}

void SerialSender::send_error_unacknowledged_event() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = ERROR_UNACKNOWLEDGED_EVENT;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
}

void SerialSender::send_error_acknowledged_event() {
	Header header;
	header.packet_size = EMPTY_PACKAGE;	//magic
	header.type = ERROR_ACKNOWLEDGED_EVENT;

	//send header
	int sendHeader = write(this->fdesc_, &header, sizeof(header));
	if (sendHeader <= 0) {
		std::perror("sending header failed");
	} else { //reset send
		sendHeader = 0;
	}
}

SerialSender::~SerialSender() {
	// Close File descriptor
	if (close(this->fdesc_) < 0) {
		exit(-1);
	}
}
int main() {

	SerialSender ser;

	// Sender beginnt als erstes Daten zu senden.
	uint16_t pukId = 1;
	uint16_t pukType = 1;
	bool eject = true;
	while (pukId < 10) {
		ser.send_puk_packet(pukId, pukType, eject);
		std::cout << "Send: " << pukId << " and " << pukType << std::endl;
		pukId++;
		usleep(1000000);
		ser.send_acknowledge();
		usleep(1000000);
		ser.send_on_event();
		usleep(1000000);
		ser.send_off_event();
		usleep(1000000);
		ser.send_error_pending_event();
		usleep(1000000);
		ser.send_error_cleared_event();
		usleep(1000000);
		ser.send_error_unacknowledged_event();
		usleep(1000000);
		ser.send_error_acknowledged_event();
		usleep(1000000);
	}

}
*/