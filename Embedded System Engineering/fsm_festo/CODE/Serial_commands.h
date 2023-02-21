/**
 * @brief Header decribing emums required for pulse messenging to serial I/O
 * @author Lennart Hartmann
 * @version 09.06.2017
 */
#ifndef SERIAL_COMMANDS_H_INCLUDED
#define SERIAL_COMMANDS_H_INCLUDED

#define INCOMMING_COMMAND 1

/**
 * Describing the type of serial message
 */
enum PkgType{
  SYSUPDATE_PKT,
  PUKDATA_PKT
};

enum SerialCodeDown {
    HEADER_PTR = 1
  , SYSUPDATE_PTR 
  , PUK_DATA_PTR
};

//#define SERIAL_CODE_UP 1
enum SerialCodeUp{
  INSTANT_BACK =1,
  PUKDATA_INCOMMING_ID,
  PUKDATA_TYPE,
  PUKDATA_HEIGHT_1,
  PUKDATA_HEIGHT_2,
  PUKDATA_END_EJACT,
  SYSUPDATE_INCOMMING
};
enum SerialInstantBack{
  HEADER_SEND_OK,
  PUKDATA_SEND_OK,
  SYSUPDATE_SEND_OK,
  HEADER_DISCONNECT,
  PUKDATA_DISCONNECT,
  SYSUPDATE_DISCONNECT
};

#endif // SERIAL_COMMANDS_H_INCLUDED
