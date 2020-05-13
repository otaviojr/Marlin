#pragma once

#include "../../inc/MarlinConfigPre.h"

enum DeltaMachineModeValues : uint8_t {
    DELTA_MACHINE_MODE_CNC=1,
    DELTA_MACHINE_MODE_LASER=2,
    DELTA_MACHINE_MODE_3DPRINTER=3
};

extern char* deltaModeNames[];

class DeltaMachineMode {
public:
  static enum DeltaMachineModeValues mode;
  static void set_mode(const DeltaMachineModeValues mode);
  static char* current_mode_name();
};

extern DeltaMachineMode deltaMachineMode;