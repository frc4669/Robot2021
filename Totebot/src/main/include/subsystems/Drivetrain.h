// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>

#include <ctre/Phoenix.h>
#include <Constants.h>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  void Drive(double speed, double rotation);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  WPI_TalonSRX m_leftMotor{DriverConstants::kLeftMotorPort};
  WPI_TalonSPX m_rightMotor{DriverConstants::kRightMotorPort};

  frc::DifferentialDrive m_drive{m_leftMotor, m_rightMotor};
};
