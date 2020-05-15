#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D22: Set Laser Active High - D22.1: set to false; D22.2 set to true
 */
void GcodeSuite::D22(const int8_t subcode) 
{
  if(subcode == 1){
    DeltaMachineMode::set_laser_active_high(false);
  } else if (subcode == 2){
    DeltaMachineMode::set_laser_active_high(true);
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_LASER_ACTIVE_HIGH_SET, (DeltaMachineMode::laser_active_high == true ? "true" : "false"));
  SERIAL_EOL();
}
