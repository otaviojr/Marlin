#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D20: Set Max Laser Power
 */
void GcodeSuite::D20() 
{
  if(parser.seen('P') && parser.seenval('P')){
    uint16_t power = parser.value_long();

    if(power > 0){
      DeltaMachineMode::set_laser_max_power(power);

      SERIAL_ECHO_START();
      SERIAL_ECHOLNPAIR(STR_DELTA3D_LASER_MAX_SET, power);
      SERIAL_EOL();
      return;
    }
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_LASER_MAX_CURRENT, DeltaMachineMode::max_laser_power);
  SERIAL_EOL();
}