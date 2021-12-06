// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>

#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Drive(double speed, double rotation);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Add our phoenix motor controllers WITH OUR PORTS
  WPI_TalonSRX m_rightMotor{DriveConstants::kRightMotorPort};
  WPI_TalonSRX m_leftMotor{DriveConstants::kLeftMotorPort};

  frc::DifferentialDrive m_drive{m_leftMotor, m_rightMotor};
};
