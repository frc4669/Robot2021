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

    constexpr double kWheelDiameter = 6; //accurate
    constexpr double kPi = 3.14159265359; //accurate
    constexpr double kTicksPerRotation = 4096; //accurate
    constexpr double kWheelCircumference = kWheelDiameter * kPi;
    constexpr double kFirstStageGearRatio = 0.25; // replace with actual number
    constexpr double kSecondStageGearRatio = 0.25; //replace with actual number
    constexpr double kThirdStageGearRatio = 0.25; //replace with actual number
    constexpr double kInchesPerTicks = kWheelCircumference / (kTicksPerRotation * kFirstStageGearRatio * kSecondStageGearRatio * kThirdStageGearRatio);
    constexpr double kTicksPerInches = kTicksPerRotation * kFirstStageGearRatio * kSecondStageGearRatio * kThirdStageGearRatio / kWheelCircumference;
    constexpr auto kTurnTolerance = 5_deg; // replace with actual number
    constexpr auto kTurnRateTolerance = 10_deg_per_s; // replace with actual number
    constexpr bool kGyroReversed = false; //replace with actual number
} // namespace DriveConstants

namespace OperatorConstants {
    constexpr auto kF310 = 0
} // namespace IO constants