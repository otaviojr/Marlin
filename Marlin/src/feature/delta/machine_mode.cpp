#include "../../inc/MarlinConfig.h"
#include "machine_mode.h"

DeltaMachineMode deltaMachineMode;

static char* deltaModeNames[] = {
  "",
  "CNC",
  "Laser",
  "3D Printer"
};

enum DeltaMachineModeValues DeltaMachineMode::mode = DELTA_MACHINE_MODE_CNC;

static void DeltaMachineMode::set_mode(const enum DeltaMachineModeValues mode){
    DeltaMachineMode::mode = mode;
}

static char* DeltaMachineMode::current_mode_name() {
  return deltaModeNames[DeltaMachineMode::mode];
}