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

uint16_t DeltaMachineMode::min_spindle_power = SPINDLE_SPEED_POWER_MIN;
uint16_t DeltaMachineMode::min_laser_power = LASER_SPEED_POWER_MIN;
uint16_t DeltaMachineMode::max_spindle_power = SPINDLE_SPEED_POWER_MAX;
uint16_t DeltaMachineMode::max_laser_power = LASER_SPEED_POWER_MAX;

boolean DeltaMachineMode::spindle_active_high = SPINDLE_ACTIVE_HIGH;
boolean DeltaMachineMode::laser_active_high = LASER_ACTIVE_HIGH;

boolean DeltaMachineMode::spindle_pwm_invert = SPINDLE_PWM_INVERT;
boolean DeltaMachineMode::laser_pwm_invert = LASER_PWM_INVERT;

void DeltaMachineMode::init() {
  #if defined(LASER_ONOFF_PIN)
    OUT_WRITE(LASER_ONOFF_PIN, HIGH); // OFF
  #endif
}

void DeltaMachineMode::set_mode(const enum DeltaMachineModeValues mode){
    DeltaMachineMode::mode = mode;
    if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_LASER){
      WRITE(LASER_ONOFF_PIN, LOW);
    } else {
      WRITE(LASER_ONOFF_PIN, HIGH);
    }
}

char* DeltaMachineMode::current_mode_name() {
  return deltaModeNames[DeltaMachineMode::mode];
}

boolean DeltaMachineMode::isCNC() {
  return (DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC);
}

uint8_t DeltaMachineMode::get_spindle_pwm_off() {
  return (DeltaMachineMode::spindle_pwm_invert ? 255 : 0);
}

uint8_t DeltaMachineMode::get_laser_pwm_off() {
  return (DeltaMachineMode::laser_pwm_invert ? 255 : 0);
}

uint8_t DeltaMachineMode::get_pwm_off() {
  return (DeltaMachineMode::isCNC() ? 
    (DeltaMachineMode::spindle_pwm_invert ? 255 : 0) : (DeltaMachineMode::laser_pwm_invert ? 255 : 0));
}

boolean DeltaMachineMode::get_spindle_active_high() {
  return DeltaMachineMode::spindle_active_high;
}

boolean DeltaMachineMode::get_laser_active_high() {
  return DeltaMachineMode::laser_active_high;
}

boolean DeltaMachineMode::get_active_high() {
  return (DeltaMachineMode::isCNC() ? 
    DeltaMachineMode::spindle_active_high : DeltaMachineMode::laser_active_high);
}

uint8_t DeltaMachineMode::get_enable_pin() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_ENA_PIN : LASER_ENA_PIN);
}

uint8_t DeltaMachineMode::get_pwm_pin() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_PWM_PIN : LASER_PWM_PIN);
}

uint16_t DeltaMachineMode::get_max_power() {
  return (DeltaMachineMode::isCNC() ? 
    DeltaMachineMode::max_spindle_power : DeltaMachineMode::max_laser_power);
}

uint16_t DeltaMachineMode::get_min_power() {
  return (DeltaMachineMode::isCNC() ? 
    DeltaMachineMode::min_spindle_power : DeltaMachineMode::min_laser_power);
}

float DeltaMachineMode::get_intercept_power() {
  return (DeltaMachineMode::isCNC() ? 
    SPINDLE_SPEED_POWER_INTERCEPT : LASER_SPEED_POWER_INTERCEPT);
}

float DeltaMachineMode::get_slope_power() {
  return DeltaMachineMode::get_max_power()/255;
}


uint16_t DeltaMachineMode::get_startup_power() {
  return DeltaMachineMode::get_min_power();
}

void DeltaMachineMode::set_spindle_min_power(uint16_t power){
  DeltaMachineMode::min_spindle_power = power;
}

void DeltaMachineMode::set_laser_min_power(uint16_t power){
  DeltaMachineMode::min_laser_power = power;
}

void DeltaMachineMode::set_spindle_max_power(uint16_t power){
  DeltaMachineMode::max_spindle_power = power;
}

void DeltaMachineMode::set_laser_max_power(uint16_t power){
  DeltaMachineMode::max_laser_power = power;
}

void DeltaMachineMode::set_laser_active_high(boolean active) {
  DeltaMachineMode::laser_active_high = active;
}
void DeltaMachineMode::set_spindle_active_high(boolean active) {
  DeltaMachineMode::spindle_active_high = active;
}

void DeltaMachineMode::set_laser_pwm_invert(boolean invert) {
  DeltaMachineMode::laser_pwm_invert = invert;
}
void DeltaMachineMode::set_spindle_pwm_invert(boolean invert) {
  DeltaMachineMode::spindle_pwm_invert = invert;
}
