#include "../gcode.h"
#include "../../MarlinCore.h"
#include "../../feature/delta/machine_mode.h"

/**
 * D1: Set machine mode: D1.1 - CNC; D1.2 - Laser; D1.3 - 3D Printer
 */
void GcodeSuite::D1(const int8_t subcode) 
{
  if(subcode >= DELTA_MACHINE_MODE_CNC && subcode <= DELTA_MACHINE_MODE_3DPRINTER){
    DeltaMachineMode::set_mode(subcode);
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR(STR_DELTA3D_MODE_SET, DeltaMachineMode::current_mode_name(),"(",subcode,")");
    SERIAL_EOL();
  } else if(subcode == 0) {
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR(STR_DELTA3D_MODE, DeltaMachineMode::current_mode_name(),"(",DeltaMachineMode::mode,")");
    SERIAL_EOL();
  }
}
