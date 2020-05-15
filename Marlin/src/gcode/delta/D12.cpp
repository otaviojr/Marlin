#include "../gcode.h"

#include "../../MarlinCore.h"

#include "../../feature/delta/machine_mode.h"

/**
 * D12: Set Spindle Active High - D12.1: set to false; D12.2 set to true
 */
void GcodeSuite::D12(const int8_t subcode) 
{
  if(subcode == 1){
    DeltaMachineMode::set_spindle_active_high(false);
  } else if (subcode == 2){
    DeltaMachineMode::set_spindle_active_high(true);
  }

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(STR_DELTA3D_SPINDLE_ACTIVE_HIGH_SET, (DeltaMachineMode::spindle_active_high == true ? "true" : "false"));
  SERIAL_EOL();
}
