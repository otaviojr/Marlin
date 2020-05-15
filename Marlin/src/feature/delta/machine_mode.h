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
  static uint16_t max_spindle_power;
  static uint16_t max_laser_power;
  static uint16_t min_spindle_power;
  static uint16_t min_laser_power;

  static boolean spindle_active_high;
  static boolean laser_active_high;

public:
  static void set_mode(const DeltaMachineModeValues mode);
  static char* current_mode_name();

  /*
    Check the machine mode and return the right power settings
  */
  static uint16_t get_startup_power();
  static uint16_t get_max_power();
  static uint16_t get_min_power();
  static uint16_t get_intercept_power();
  static uint16_t get_slope_power();

  static boolean get_active_high();

  static uint8_t get_enable_pin();
  static uint8_t get_pwm_pin();
  static uint8_t get_pwm_off();

  static boolean isCNC();

  static void set_spindle_min_power(uint16_t power);
  static void set_laser_min_power(uint16_t power);
  static void set_spindle_max_power(uint16_t power);
  static void set_laser_max_power(uint16_t power);

  static void set_laser_active_high(boolean active);
  static void set_spindle_active_high(boolean active);
};

extern DeltaMachineMode deltaMachineMode;