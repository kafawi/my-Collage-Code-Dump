/**
 * @brief Header decribing emums required for pulse messenging to HAL
 * @author Lennart Hartmann
 * @version 14.05.2017
 */

#ifndef HAL_COMMANDS_H_INCLUDED
#define HAL_COMMANDS_H_INCLUDED

/**
 * Specifies actor for easy multiplexing
 */
enum HalCommandType
{
  MOTOR = 1,
  GATE = 2,
  STATUS_LIGHTS = 3,
  BUTTON_LIGHTS = 4,
  PROFILOMETER = 5,
  HAL_CONTROL = 6
};

/**
 * Signals to motor control
 */
enum MotorCommand
{
  MOTOR_ON,
  MOTOR_OFF,
  MOTOR_SLOW,
  MOTOR_FAST
};

/**
 * Sognals to gate
 */
enum GateCommand
{
  GATE_OPEN,
  GATE_CLOSE
};

/**
 * Signal to status lights
 */
enum StatusLightsCommand
{
  GREEN_OFF, GREEN_ON,
  RED_OFF, RED_ON,
  YELLOW_OFF, YELLOW_ON,
  ALL_LIGHTS_OFF
};

/**
 * Signals to status lighting
 */
enum ButtonLightsCommand
{
  LED_START_OFF, LED_START_ON,
  LED_RESET_OFF, LED_RESET_ON,
  LED_Q1_OFF, LED_Q1_ON,
  LED_Q2_OFF, LED_Q2_ON
};

/**
 * Signals to Profilometer
 */
enum ProfilometerCommand
{
  START_SAMPLING,
  PAUSE_SAMPLING,
  END_SAMPLING,
  CONTINUE_SAMPLING
};

/**
 * Signals for general control of HAL
 */
enum HalControlCommand
{
  KILL_HAL,
  RESET_HAL,
  STOP_IRQ,
  CONTINUE_IRQ
};
#endif // HAL_COMMANDS_H_INCLUDED
