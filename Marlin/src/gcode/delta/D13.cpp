#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D13: Set Spindle PWM invert - D13.1: set to false; D13.2 set to true
 */
void GcodeSuite::D13(const int8_t subcode) 
{
  if(subcode == 1){
    DeltaMachineMode::set_spindle_pwm_invert(false);
  } else if (subcode == 2){
    DeltaMachineMode::set_spindle_pwm_invert(true);
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_SPINDLE_PWM_INVERT_SET, (DeltaMachineMode::spindle_pwm_invert == true ? "true" : "false"));
  SERIAL_EOL();
}
