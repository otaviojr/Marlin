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

static uint16_t DeltaMachineMode::min_spindle_power = SPINDLE_SPEED_POWER_MIN;
static uint16_t DeltaMachineMode::min_laser_power = LASER_SPEED_POWER_MIN;
static uint16_t DeltaMachineMode::max_spindle_power = SPINDLE_SPEED_POWER_MAX;
static uint16_t DeltaMachineMode::max_laser_power = LASER_SPEED_POWER_MAX;

static void DeltaMachineMode::set_mode(const enum DeltaMachineModeValues mode){
    DeltaMachineMode::mode = mode;
}

static char* DeltaMachineMode::current_mode_name() {
  return deltaModeNames[DeltaMachineMode::mode];
}

static uint16_t DeltaMachineMode::get_max_power() {
  if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC){
    return DeltaMachineMode::max_spindle_power;
  } else {
    return DeltaMachineMode::max_laser_power;
  }
}

static uint16_t DeltaMachineMode::get_min_power() {
  if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC){
    return DeltaMachineMode::min_spindle_power;
  } else {
    return DeltaMachineMode::min_laser_power;
  }
}

static uint16_t DeltaMachineMode::get_intercept_power() {
  if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC){
    return SPINDLE_SPEED_POWER_INTERCEPT;
  } else {
    return LASER_SPEED_POWER_INTERCEPT;
  }
}

static uint16_t DeltaMachineMode::get_slope_power() {
  if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC){
    return SPINDLE_SPEED_POWER_SLOPE;
  } else {
    return LASER_SPEED_POWER_SLOPE;
  }
}


static uint16_t DeltaMachineMode::get_startup_power() {
  return DeltaMachineMode::get_min_power();
}

static void DeltaMachineMode::set_spindle_min_power(uint16_t power){
  DeltaMachineMode::min_spindle_power = power;
}

static void DeltaMachineMode::set_laser_min_power(uint16_t power){
  DeltaMachineMode::min_laser_power = power;
}

static void DeltaMachineMode::set_spindle_max_power(uint16_t power){
  DeltaMachineMode::max_spindle_power = power;
}

static void DeltaMachineMode::set_laser_max_power(uint16_t power){
  DeltaMachineMode::max_laser_power = power;
}
