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

static boolean DeltaMachineMode::spindle_active_high = SPINDLE_ACTIVE_HIGH;
static boolean DeltaMachineMode::laser_active_high = LASER_ACTIVE_HIGH;

static boolean DeltaMachineMode::spindle_pwm_invert = SPINDLE_PWM_INVERT;
static boolean DeltaMachineMode::laser_pwm_invert = LASER_PWM_INVERT;

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
  return (DeltaMachineMode::isCNC() ? 
    (DeltaMachineMode::spindle_pwm_invert ? 255 : 0) : (DeltaMachineMode::laser_pwm_invert ? 255 : 0));
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

static float DeltaMachineMode::get_intercept_power() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_SPEED_POWER_INTERCEPT : LASER_SPEED_POWER_INTERCEPT);
}

static float DeltaMachineMode::get_slope_power() {
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

static void DeltaMachineMode::set_laser_pwm_invert(boolean invert) {
  DeltaMachineMode::laser_pwm_invert = invert;
}
static void DeltaMachineMode::set_spindle_pwm_invert(boolean invert) {
  DeltaMachineMode::spindle_pwm_invert = invert;
}
