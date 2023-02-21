/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#include "digitalPortStrat.h"
#include "gpio.h"

DigitalPortStrat::DigitalPortStrat (void)
{
#if defined(__QNXNTO__)

  //out8 (CTRL_GROUP0, DEFAULT_PORTS_SETTINGS);
  if (ThreadCtl (_NTO_TCTL_IO_PRIV, 0) == -1)
  {
    std::cout
            << "Can't get Hardware access, therefore can't do anything."
            << std::endl;
  }

#else
  std::cout << "DigitalPortStrat ctor" << std::endl;
#endif
}
DigitalPortStrat::~DigitalPortStrat () { };


bool
DigitalPortStrat::isOn(const struct DigitalPort& port, uint8_t mask)
{
  unsigned char value = 0;
#if defined(__QNXNTO__)
  value = in8(port.addr);
#endif
  return ((value & mask) != 0);
}


const struct DigitalPort
DigitalPortStrat::portA (PORTA_ADDR, 0b11111111, 0b11111111);
const struct DigitalPort
DigitalPortStrat::portB (PORTB_ADDR, 0b00000000, 0b00110000);
const struct DigitalPort
DigitalPortStrat::portC (PORTC_ADDR, 0b00001111, 0b01011111);
