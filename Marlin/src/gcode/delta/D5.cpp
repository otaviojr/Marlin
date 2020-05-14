#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D5: Set Min Laser Power
 */
void GcodeSuite::D5() 
{
  if(parser.seen('P') && parser.seenval('P')){
    uint16_t power = parser.value_long();

    if(power > 0){
      DeltaMachineMode::set_laser_min_power(power);

      SERIAL_ECHO_START();
      SERIAL_ECHOLNPAIR(STR_DELTA3D_LASER_MIN_SET, power);
      SERIAL_EOL();
      return;
    }
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_LASER_MIN_CURRENT, DeltaMachineMode::min_laser_power);
  SERIAL_EOL();
}