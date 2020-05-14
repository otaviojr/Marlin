#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D3: Set Min Spindle RPM
 */
void GcodeSuite::D3() 
{
  if(parser.seen('P') && parser.seenval('P')){
    uint16_t power = parser.value_long();

    if(power > 0){
      DeltaMachineMode::set_spindle_min_power(power);

      SERIAL_ECHO_START();
      SERIAL_ECHOLNPAIR(STR_DELTA3D_SPINDLE_MIN_SET, power);
      SERIAL_EOL();
      return;
    }
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_SPINDLE_MIN_CURRENT, DeltaMachineMode::min_spindle_power);
  SERIAL_EOL();
}