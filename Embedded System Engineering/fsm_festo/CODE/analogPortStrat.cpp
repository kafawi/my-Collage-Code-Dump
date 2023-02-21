/*
 * analogPortStrat.cpp
 *
 *  Created on: 09.06.2017
 *      Author: abx932
 */

#include "analogPortStrat.h"

#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <hw/inout.h>
#endif
#include <iostream>
#include <stdint.h>
#include <unistd.h>

AnalogPortStrat::AnalogPortStrat(AnalogPort port)
:port(port)
{
}



uint16_t 
AnalogPortStrat::getValue (){
  uint16_t val = 0;
#if defined(__QNXNTO__)
    out8 (port.addr + port.cr_out_offset, port.cr_out_op);
    //wait for conversion to complete
    usleep (10);
    //read low bytes
    val = in8 (port.addr + port.loB_in_offset);
    //read high bytes
    val |= (uint16_t)in8 (port.addr + port.hiB_in_offset) << 8;
    // height sensor value is only 12 bit
    val &= port.onlyNBitmask;
#else
    usleep (10);
//    val = std::rand ();
#endif
    return val;
}
