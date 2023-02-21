/*
 * AnalogPortStrat.h
 *
 *  Created on: Jun 1, 2017
 *      Author: kafa
 */

#ifndef _ANALOGPORTSTRAT_H_
#define _ANALOGPORTSTRAT_H_

#include "gpio.h"
#include <stdint.h>

struct AnalogPort
{
  AnalogPort(uint16_t addr,
             uint16_t loB,
             uint16_t hiB,
             uint16_t crof,
             uint16_t crop,
             uint16_t bitmask)
  :addr(addr)
  ,loB_in_offset(loB)
  ,hiB_in_offset(hiB)
  ,cr_out_offset(crof)
  ,cr_out_op(crop)
  ,onlyNBitmask(bitmask)
  {}
  
  const uint16_t addr = 0;
  const uint16_t loB_in_offset;
  const uint16_t hiB_in_offset;
  const uint16_t cr_out_offset;
  const uint16_t cr_out_op;
  const uint16_t onlyNBitmask;
};

class AnalogPortStrat
{
 public:
  AnalogPortStrat(AnalogPort port);
  const AnalogPort port;
  uint16_t getValue();
  //uint16_t firfilter(uint16_t [] hMinus);
};



#endif /* _ANALOGPORTSTRAT_H_ */
