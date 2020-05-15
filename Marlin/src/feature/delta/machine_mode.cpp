#include "../../inc/MarlinConfig.h"
#include "machine_mode.h"

DeltaMachineMode deltaMachineMode;

#define SPINDLE_PWM_OFF ((SPINDLE_PWM_INVERT) ? 255 : 0)
#define LASER_PWM_OFF ((LASER_PWM_INVERT) ? 255 : 0)

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

static boolean DeltaMachineMode::spindle_active_high = SPINDLE_ACTIVE_HIGH;
static boolean DeltaMachineMode::laser_active_high = LASER_ACTIVE_HIGH;


static void DeltaMachineMode::set_mode(const enum DeltaMachineModeValues mode){
    DeltaMachineMode::mode = mode;
}

static char* DeltaMachineMode::current_mode_name() {
  return deltaModeNames[DeltaMachineMode::mode];
}

static boolean DeltaMachineMode::isCNC() {
  return (DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC);
}

static uint8_t DeltaMachineMode::get_pwm_off() {
  return (DeltaMachineMode::isCNC() ? SPINDLE_PWM_OFF : LASER_PWM_OFF);
}

static boolean DeltaMachineMode::get_active_high() {
  return (DeltaMachineMode::isCNC() ? 
    DeltaMachineMode::spindle_active_high : DeltaMachineMode::laser_active_high);
}

static uint8_t DeltaMachineMode::get_enable_pin() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_ENA_PIN : LASER_ENA_PIN);
}

static uint8_t DeltaMachineMode::get_pwm_pin() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_PWM_PIN : LASER_PWM_PIN);
}

static uint16_t DeltaMachineMode::get_max_power() {
  return (DeltaMachineMode::isCNC() ? 
    DeltaMachineMode::max_spindle_power : DeltaMachineMode::max_laser_power);
}

static uint16_t DeltaMachineMode::get_min_power() {
  return (DeltaMachineMode::isCNC() ? 
    DeltaMachineMode::min_spindle_power : DeltaMachineMode::min_laser_power);
}

static uint16_t DeltaMachineMode::get_intercept_power() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_SPEED_POWER_INTERCEPT : LASER_SPEED_POWER_INTERCEPT);
}

static uint16_t DeltaMachineMode::get_slope_power() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_SPEED_POWER_SLOPE : LASER_SPEED_POWER_SLOPE);
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

static void DeltaMachineMode::set_laser_active_high(boolean active) {
  DeltaMachineMode::laser_active_high = active;
}
static void DeltaMachineMode::set_spindle_active_high(boolean active) {
  DeltaMachineMode::spindle_active_high = active;
}
