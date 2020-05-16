#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D23: Set Laser PWM invert - D13.1: set to false; D13.2 set to true
 */
void GcodeSuite::D23(const int8_t subcode) 
{
  if(subcode == 1){
    DeltaMachineMode::set_laser_pwm_invert(false);
  } else if (subcode == 2){
    DeltaMachineMode::set_laser_pwm_invert(true);
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_LASER_PWM_INVERT_SET, (DeltaMachineMode::laser_pwm_invert == true ? "true" : "false"));
  SERIAL_EOL();
}
