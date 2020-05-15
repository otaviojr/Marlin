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
#pragma once

/**
 * feature/spindle_laser.h
 * Support for Laser Power or Spindle Power & Direction
 */

#include "../inc/MarlinConfig.h"

#include "spindle_laser_types.h"

/*Delta3D - Machine Mode*/
#include "./delta/machine_mode.h"

#if ENABLED(LASER_POWER_INLINE)
  #include "../module/planner.h"
#endif

class SpindleLaser {
public:
  static cutter_power_t power;
  static cutter_power_t isOn;
  #if HAS_LCD_MENU
    static cutter_power_t menuLaserPower;
    static inline uint8_t powerPercent(const uint8_t pp) { return ui8_to_percent(pp); } // for display
  #endif
  static void init();

  // Modifying this function should update everywhere
  static inline bool enabled(const cutter_power_t pwr) { return pwr > 0; }
  static inline bool enabled() { return enabled(power); }
  
  static void apply_power(const cutter_power_t inpow);

  FORCE_INLINE static void refresh() { apply_power(power); }
  FORCE_INLINE static void set_power(const cutter_power_t pwr) { power = pwr; refresh(); }

  static inline void set_enabled(const bool enable) { set_power(enable ? (power ?: DeltaMachineMode::get_startup_power()) : 0); }

  #if ENABLED(LASER_PWM) || ENABLED(SPINDLE_PWM)
    static void set_ocr(const uint8_t ocr);
    static inline void set_ocr_power(const uint8_t pwr) { power = pwr; set_ocr(pwr); }
    static uint8_t translate_power(const cutter_power_t pwr); // Used by update output for power->OCR translation
  #endif

  // Wait for spindle to spin up or spin down
  static inline void power_delay(const bool on) {
    if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_CNC){
      safe_delay(on ? SPINDLE_POWERUP_DELAY : SPINDLE_POWERDOWN_DELAY);
    } 
    #if DISABLED(LASER_POWER_INLINE)
    else if(DeltaMachineMode::mode == DELTA_MACHINE_MODE_LASER) {
        safe_delay(on ? LASER_POWERUP_DELAY : LASER_POWERDOWN_DELAY);
    }
    #endif
  }

  #if ENABLED(SPINDLE_CHANGE_DIR)
    static void set_direction(const bool reverse);
  #else
    static inline void set_direction(const bool) {}
  #endif

  static inline void disable() { isOn = false; set_enabled(false); }
  #if HAS_LCD_MENU
    static inline void enable_forward() { isOn = true; menuLaserPower ? power = menuLaserPower : (power = DeltaMachineMode::get_startup_power(), menuLaserPower = DeltaMachineMode::get_startup_power()); set_direction(false); set_enabled(true); }
    static inline void enable_reverse() { isOn = true; menuLaserPower ? power = menuLaserPower : (power = DeltaMachineMode::get_startup_power(), menuLaserPower = DeltaMachineMode::get_startup_power()); set_direction(true); set_enabled(true); }
  #endif
  #if ENABLED(LASER_POWER_INLINE)
    // Force disengage planner power control
    static inline void inline_disable() { planner.laser.status = 0; planner.laser.power = 0; isOn = false;}

    // Inline modes of all other functions; all enable planner inline power control
    static inline void inline_enabled(const bool enable) { enable ? inline_power(translate_power(DeltaMachineMode::get_startup_power())) : inline_ocr_power(0); }

    static void inline_power(const cutter_power_t pwr) {
      #if ENABLED(LASER_PWM)
        inline_ocr_power(translate_power(pwr));
      #else
        planner.laser.status = enabled(pwr) ? 0x03 : 0x01;
        planner.laser.power = pwr;
      #endif
    }

    static inline void inline_direction(const bool reverse) { UNUSED(reverse); } // TODO is this ever going to be needed

    #if ENABLED(LASER_PWM)
      static inline void inline_ocr_power(const uint8_t pwr) {
        planner.laser.status = pwr ? 0x03 : 0x01;
        planner.laser.power = pwr;
      }
    #endif
  #endif
};

extern SpindleLaser cutter;
