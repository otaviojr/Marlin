#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D2: Set Max Spindle RPM
 */
void GcodeSuite::D2() 
{
  if(parser.seen('P') && parser.seenval('P')){
    uint16_t power = parser.value_long();

    if(power > 0){
      DeltaMachineMode::set_spindle_max_power(power);

      SERIAL_ECHO_START();
      SERIAL_ECHOLNPAIR(STR_DELTA3D_SPINDLE_MAX_SET, power);
      SERIAL_EOL();
      return;
    }
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_SPINDLE_MAX_CURRENT, DeltaMachineMode::max_spindle_power);
  SERIAL_EOL();
}
