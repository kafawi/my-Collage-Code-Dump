/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */

/*
 * @file gpio.h
 * @brief Provides access to hardware
 *
 * Ports are defined and other useful things.
 *
 *
 *  Created on: 19.04.2017
 * @author Eddy,Lennart
 * @author kafa
 */

#ifndef HAL_LIB_GPIO_H_
#define HAL_LIB_GPIO_H_

#define CTRL_GROUP0 0x303
#define PORTA_ADDR 0x300
#define PORTB_ADDR 0x301
#define PORTC_ADDR 0x302
// digital masks
/*
 * Port A
 */
#define MOTOR_RIGHT_BIT_POS  0
#define MOTOR_LEFT_BIT_POS   1
#define MOTOR_SLOW_BIT_POS   2
#define MOTOR_STOP_BIT_POS   3
#define GATE_OPEN_BIT_POS    4
#define WS_GREEN_BIT_POS     5
#define WS_YELLOW_BIT_POS    6
#define WS_RED_ON_BIT_POS    7
#define MOTOR_RIGHT_HI_OUT  (1<<MOTOR_RIGHT_BIT_POS)
#define MOTOR_LEFT_HI_OUT   (1<<MOTOR_LEFT_BIT_POS)
#define MOTOR_SLOW_HI_OUT   (1<<MOTOR_SLOW_BIT_POS)
#define MOTOR_STOP_HI_OUT   (1<<MOTOR_STOP_BIT_POS)
#define GATE_OPEN_HI_OUT    (1<<GATE_OPEN_BIT_POS)
#define WS_GREEN_ON_HI_OUT  (1<<WS_GREEN_BIT_POS)
#define WS_YELLOW_ON_HI_OUT (1<<WS_YELLOW_BIT_POS)
#define WS_RED_ON_HI_OUT    (1<<WS_RED_ON_BIT_POS)
/*
 * port B
 */
#define POSITION_ENTRY_BIT_POS  0
#define POSITION_PD_BIT_POS     1
#define PD_ACCEPT_BIT_POS       2
#define POSITION_GATE_BIT_POS   3
#define METAL_DETECTION_BIT_POS 4
#define GATE_IS_OPEN_BIT_POS    5
#define POSITION_SLITE_BIT_POS  6
#define POSITION_OUTLET_BIT_POS 7
#define POSITION_ENTRY_LO_IN  (1<<POSITION_ENTRY_BIT_POS)
#define POSITION_PD_LO_IN     (1<<POSITION_PD_BIT_POS)
#define PD_ACCEPT_LO_IN       (1<<PD_ACCEPT_BIT_POS)
#define POSITION_GATE_LO_IN   (1<<POSITION_GATE_BIT_POS)
#define METAL_DETECTION_HI_IN (1<<METAL_DETECTION_BIT_POS)
#define GATE_IS_OPEN_HI_IN    (1<<GATE_IS_OPEN_BIT_POS)
#define POSITION_SLITE_LO_IN  (1<<POSITION_SLITE_BIT_POS)
#define POSITION_OUTLET_LO_IN (1<<POSITION_OUTLET_BIT_POS)
/*
 * port C
 */
#define LED_START_BIT_POS    0
#define LED_RESET_BIT_POS    1
#define LED_Q1_BIT_POS       2
#define LED_Q2_BIT_POS       3
#define BUTTON_START_BIT_POS 4
#define BUTTON_STOP_BIT_POS  5
#define BUTTON_RESET_BIT_POS 6
#define BUTTON_ESTOP_BIT_POS 7
#define LED_START_HI_OUT    (1<<LED_START_BIT_POS)
#define LED_RESET_HI_OUT    (1<<LED_RESET_BIT_POS)
#define LED_Q1_HI_OUT       (1<<LED_Q1_BIT_POS)
#define LED_Q2_HI_OUT       (1<<LED_Q2_BIT_POS)
#define BUTTON_START_HI_IN  (1<<BUTTON_START_BIT_POS)
#define BUTTON_STOP_LO_IN   (1<<BUTTON_STOP_BIT_POS)
#define BUTTON_RESET_HI_IN  (1<<BUTTON_RESET_BIT_POS)
#define BUTTON_ESTOP_LO_IN  (1<<BUTTON_ESTOP_BIT_POS)





// ANALOG PORT ()
// TODO ANALOG PORT
#define CR_WP (0x10) /**< control code Write protect */
#define ANALOG_BASEADDR (0x320)
#define ANALOG_LOBIT_IN_OFFSET (0x2)
#define ANALOG_HIBIT_IN_OFFSET (0x3)
#define ANALOG_CR_ADDR_OFFSET (0x2)


// IR needet things others
// IRQ NEEDET THINGS

#define IRQ_MASK 11 /**< this mask 11 is free to use */

#endif /* HAL_LIB_GPIO_H_ */
