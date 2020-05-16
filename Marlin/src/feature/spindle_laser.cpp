/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * feature/spindle_laser.cpp
 */

#include "../inc/MarlinConfig.h"

#if HAS_CUTTER

#include "spindle_laser.h"

SpindleLaser cutter;

cutter_power_t SpindleLaser::power; // = 0
cutter_power_t SpindleLaser::isOn = false;
#if HAS_LCD_MENU
  cutter_power_t SpindleLaser::menuLaserPower; // = 0
#endif

//
// Init the cutter to a safe OFF state
//
void SpindleLaser::init() {
  if(DeltaMachineMode::isCNC()){
    OUT_WRITE(SPINDLE_ENA_PIN, !DeltaMachineMode::get_active_high()); // Init spindle to off
    #if ENABLED(SPINDLE_CHANGE_DIR)
      OUT_WRITE(SPINDLE_DIR_PIN, SPINDLE_INVERT_DIR ? 255 : 0);   // Init rotation to clockwise (M3)
    #endif
  } else {
    OUT_WRITE(LASER_ENA_PIN, !DeltaMachineMode::get_active_high()); // Init spindle to off
  }

  #if ENABLED(LASER_PWM) || ENABLED(SPINDLE_PWM)
    if(DeltaMachineMode::isCNC()){
      SET_PWM(SPINDLE_PWM_PIN);
      analogWrite(pin_t(SPINDLE_PWM_PIN), DeltaMachineMode::get_pwm_off());  // set to lowest speed
    } else {
      SET_PWM(LASER_PWM_PIN);
      analogWrite(pin_t(LASER_PWM_PIN), DeltaMachineMode::get_pwm_off());  // set to lowest speed
    }
  #endif
  #if ENABLED(HAL_CAN_SET_PWM_FREQ) && defined(SPINDLE_LASER_FREQUENCY)
    set_pwm_frequency(pin_t(DeltaMachineMode::get_pwm_pin()), SPINDLE_LASER_FREQUENCY);
  #endif
}

#if ENABLED(LASER_PWM) || ENABLED(SPINDLE_PWM)

  //
  // Set the cutter PWM directly to the given ocr value
  //
  void SpindleLaser::set_ocr(const uint8_t ocr) {
    if(DeltaMachineMode::isCNC()){
      WRITE(SPINDLE_ENA_PIN, DeltaMachineMode::get_active_high()); // turn spindle on
      analogWrite(pin_t(SPINDLE_PWM_PIN), ocr ^ DeltaMachineMode::get_pwm_off());
    } else {
      WRITE(LASER_ENA_PIN, DeltaMachineMode::get_active_high()); // turn spindle on
      analogWrite(pin_t(LASER_PWM_PIN), ocr ^ DeltaMachineMode::get_pwm_off());
    }
  }
  //
  // Translate power from the configured value range to a PWM value
  //
  uint8_t SpindleLaser::translate_power(const cutter_power_t pwr) {
      float inv_slope = RECIPROCAL(DeltaMachineMode::get_slope_power()),
                      min_ocr = (DeltaMachineMode::get_min_power() - (DeltaMachineMode::get_intercept_power())) * inv_slope,  // Minimum allowed
                      max_ocr = (DeltaMachineMode::get_max_power() - (DeltaMachineMode::get_intercept_power())) * inv_slope;  // Maximum allowed
      int16_t ocr_val;
           if (pwr <= DeltaMachineMode::get_min_power()) ocr_val = min_ocr;                                 // Use minimum if set below
      else if (pwr >= DeltaMachineMode::get_max_power()) ocr_val = max_ocr;                                 // Use maximum if set above
      else ocr_val = (pwr - (DeltaMachineMode::get_intercept_power())) * inv_slope;                         // Use calculated OCR value
      return ocr_val & 0xFF;                                                                                // ...limited to Atmel PWM max
  }

#endif

//
// Set cutter ON state (and PWM) to the given cutter power value
//
void SpindleLaser::apply_power(const cutter_power_t inpow) {
  static cutter_power_t last_power_applied = 0;
  if (inpow == last_power_applied) return;
  last_power_applied = inpow;
  #if ENABLED(LASER_PWM) || ENABLED(SPINDLE_PWM)
    if (enabled())
      set_ocr(translate_power(inpow));
    else {                                                                                      // Convert RPM to PWM duty cycle
      if(DeltaMachineMode::isCNC()){
        WRITE(SPINDLE_ENA_PIN, !DeltaMachineMode::get_active_high());                           // Turn spindle off
        analogWrite(pin_t(SPINDLE_PWM_PIN), DeltaMachineMode::get_pwm_off());                   // Only write low byte
      } else {
        WRITE(LASER_ENA_PIN, !DeltaMachineMode::get_active_high());                             // Turn laser off
        analogWrite(pin_t(LASER_PWM_PIN), DeltaMachineMode::get_pwm_off());                     // Only write low byte
      }
    }
  #else
    if(DeltaMachineMode::isCNC()){
      WRITE(SPINDLE_ENA_PIN, (DeltaMachineMode::get_active_high()) ? enabled() : !enabled());
    } else {
      WRITE(LASER_ENA_PIN, (DeltaMachineMode::get_active_high()) ? enabled() : !enabled());
    }
  #endif
}

#if ENABLED(SPINDLE_CHANGE_DIR)

  //
  // Set the spindle direction and apply immediately
  // Stop on direction change if SPINDLE_STOP_ON_DIR_CHANGE is enabled
  //
  void SpindleLaser::set_direction(const bool reverse) {
    const bool dir_state = (reverse == SPINDLE_INVERT_DIR); // Forward (M3) HIGH when not inverted
    #if ENABLED(SPINDLE_STOP_ON_DIR_CHANGE)
      if (enabled() && READ(SPINDLE_DIR_PIN) != dir_state) disable();
    #endif
    WRITE(SPINDLE_DIR_PIN, dir_state);
  }

#endif

#endif // HAS_CUTTER
