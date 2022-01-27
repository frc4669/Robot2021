// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/voltage.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/angular_velocity.h>


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
    constexpr int kLeftMotor1Port = 14;
    constexpr int kLeftMotor2Port = 11;

    constexpr int kRightMotor1Port = 12;
    constexpr int kRightMotor2Port = 13;

    constexpr int kGearShifterForwardChannel = 4;       // The forward channel on the module to control
    constexpr int kGearShifterReverseChannel = 5;       // The reverse channel on the module to control
    
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
    constexpr double kFirstGearRatio = (double) 30/11;  // 30 teeth driven by 11; dont change unless using diff gearbox
    constexpr double kSecondGearRatio = (double) 44/30; // 44 teeth driven by 30; dont change unless using diff gearbox

    // shifter ratios
    constexpr double kLowGearRatio = (double) 50/14;    // 50 teeth driven by 14; dont change unless using diff gearbox
    constexpr double kHighGearRatio = (double) 44/20;   // 44 teeth driven by 20; dont change unless using diff gearbox

    constexpr double kLastGearRatio = (double) 40/34;   // 40 teeth driven by 34; dont change unless using diff gearbox

    // if shifted at 1 (using low gear)
    constexpr double kInchesPerTicksLowGear = kWheelCirc / (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kLowGearRatio * kLastGearRatio);
    constexpr double kTicksPerInchesLowGear = (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kLowGearRatio * kLastGearRatio) / kWheelCirc;

    // if shifted at 2 (using high gear)
    constexpr double kInchesPerTicksHighGear = kWheelCirc / (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kHighGearRatio * kLastGearRatio);
    constexpr double kTicksPerInchesHighGear = (kTicksPerRev * kFirstGearRatio * kSecondGearRatio * kHighGearRatio * kLastGearRatio) / kWheelCirc;

    // misc stuff
    constexpr auto kTurnTolerance = 5_deg;              // start with 5; aim for 2?
    constexpr auto kTurnRateTolerance = 10_deg_per_s; 
    constexpr bool kGyroReversed = false; 
} // namespace DriveConstants

namespace ShooterConstants {
    constexpr int kShooterMasterPort = 8;
    constexpr int kShooterSlavePort = 9;
} // namespace ShooterConstants

namespace OperatorConstants {
    constexpr auto kF310 = 0;
} // namespace IO constants