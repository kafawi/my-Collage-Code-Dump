/** @file digitalPortStrat.h
 *  @brief Defines strategies / methods to work with an Digital Port
 *
 *
 *  @author kafawi
 *
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */

#ifndef DIGITAL_PORT_STRAT_H_
#define DIGITAL_PORT_STRAT_H_
#if defined(__QNXNTO__)
#include <hw/inout.h>
#include <sys/neutrino.h>
#else
#include <iostream>
#endif
#include "gpio.h"
#include "lock.h"

/**
 * @struct gather important information for a digital port
 */
struct DigitalPort
{

  /**
   * CTOR
   */
  explicit
  DigitalPort(int a, uint8_t m, uint8_t h)
  : addr(a)
  , outMask(m)
  , highActiveMask(h)
  , mtx()
  {
  };

  /**
   * DTOR
   */
  ~DigitalPort()
  {
  };
  const int addr; /**< Address pointer for hardware access */
  const uint8_t outMask; /**< mask to identify the in an outs */
  const uint8_t highActiveMask; /**< mask to distinguish hi/lo active bits */
  mutable Mutex mtx; /**< guarantees thread safeness */
};

/**
 * @class Define an Interface of the reaction of an Actor
 */
class DigitalPortStrat
{
 public:

  /**
   * @details turn bit to high at this port
   *  @param port destination digital Port
   *  @param mask bit to turn on
   */
  inline void toggleBitOn(const struct DigitalPort& port, uint8_t mask)
  {
    port.mtx.acquire();
#if defined(__QNXNTO__)
    unsigned char value = in8(port.addr);
    out8(port.addr, value | mask);
#else
    printf("ON - Port: %X Bit: %o\n", port.addr, mask);
#endif
    port.mtx.release();
  }

  /**
   * @details turn bit to low at this port
   *  @param port destination Digital Port
   *  @param mask bit to turn off
   */
  inline void toggleBitOff(const struct DigitalPort& port, uint8_t mask)
  {
    port.mtx.acquire();
#if defined(__QNXNTO__)
    unsigned char value = in8(port.addr);
    out8(port.addr, value&~mask);
#else
    printf("OFF- Port: %X Bit: %o\n", port.addr, mask);
#endif
    port.mtx.release();
  }
  
  /**
   * test, if bit is set
   * @param port
   * @param mask
   * @return 
   */
  static bool isOn(const struct DigitalPort& port, uint8_t mask);
 
  /**
   * ctor
   */
  DigitalPortStrat(void);

  virtual ~DigitalPortStrat();

  static const struct DigitalPort portA;
  static const struct DigitalPort portB;
  static const struct DigitalPort portC;
};
#endif /* DIGITAL_PORT_STRAT_H_ */


