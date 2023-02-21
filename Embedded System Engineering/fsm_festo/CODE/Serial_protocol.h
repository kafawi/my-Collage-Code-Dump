/**
 * @brief Header protocol for serial messenging to serial port
 * @author Alexander Mendel
 * @version 08.06.2017
 */
#ifndef SERIAL_PROTOCOL_H_INCLUDED
#define SERIAL_PROTOCOL_H_INCLUDED

#include "Serial_commands.h"
#include "MCL_signals.h"
#include "Puk.h"

typedef struct
{
  size_t packet_size;
  enum PkgType type;
} Header;

typedef struct
{
  enum MCL_input_signal signal;  
} SysUpdate;

typedef struct
{
  uint16_t puk_id;
  enum PukType puk_type; // later as enum PukType
  uint16_t height1;
  uint16_t height2;
  bool eject;  // is this nessessary, because it is not a real thing;
} PukData;

#endif /* SERIAL_PROTOCOL_H_INCLUDED */
