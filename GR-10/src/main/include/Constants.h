// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/units.h>


/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace DriveConstants {
    constexpr int kLeftMotor1Port = 5;
    constexpr int kLeftMotor2Port = 1;

    constexpr int kRightMotor1Port = 8;
    constexpr int kRightMotor2Port = 3;

    constexpr auto ks = 1_V;
    constexpr auto kv = 0.8_V * 1_s / 1_m;
    constexpr auto ka = 0.15_V * 1_s * 1_s / 1_m;

    constexpr double kp = 1;

    constexpr auto kMaxSpeed = 3_mps;
    constexpr auto kMaxAcceleration = 3_mps_sq;

    constexpr double kWheelDiameter = 6;                // Wheel diameter; dont change unless using different wheels
    constexpr double kPi = 3.14159265359;               // Value of PI; dont change unless bending rules of mathematics
    constexpr double kTicksPerRev = 4096;               // Ticks per revolution; dont change
    constexpr double kWheelCirc = kWheelDiameter * kPi; // Wheel circumference; dont change unless bending rules of mathematics

    // before shifter
    constexpr double kFirstGearRatio = 30/11;           // 30 teeth driven by 11; dont change unless using diff gearbox
    constexpr double kSecondGearRatio = 44/30;          // 44 teeth driven by 30; dont change unless using diff gearbox

    // shifter ratios
    constexpr double kFirstShiftedGearRatio = 50/14;    // 50 teeth driven by 14; dont change unless using diff gearbox
    constexpr double kSecondShiftedGearRatio = 44/20;   // 44 teeth driven by 20; dont change unless using diff gearbox

    constexpr double kLastGearRatio = 40/34;            // 40 teeth driven by 34; dont change unless using diff gearbox

    // if shifted at 1 (using first gear)
    constexpr double kInchesPerTicks = kWheelCirc / (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kFirstShiftedGearRatio * kLastGearRatio);
    constexpr double kTicksPerInches = (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kFirstShiftedGearRatio * kLastGearRatio) / kWheelCirc;

    // if shifted at 2 (using second gear)
    constexpr double kInchesPerTicks = kWheelCirc / (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kSecondShiftedGearRatio * kLastGearRatio);
    constexpr double kTicksPerInches = (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kSecondShiftedGearRatio * kLastGearRatio) / kWheelCirc;

    // misc stuff
    constexpr auto kTurnTolerance = 5_deg;              // start with 5; aim for 2?
    constexpr auto kTurnRateTolerance = 10_deg_per_s; 
    constexpr bool kGyroReversed = false; 
} // namespace DriveConstants

namespace OperatorConstants {
    constexpr auto kF310 = 0
} // namespace IO constants