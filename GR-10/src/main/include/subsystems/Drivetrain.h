// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/SpeedController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>

#include <ctre/Phoenix.h>       // talon
#include <frc/ADIS16470_IMU.h>  // imu

#include <Constants.h>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // motors
  WPI_TalonFX m_leftMaster  = {DriveConstants::kLeftMotor1Port};
  WPI_TalonFX m_leftSlave   = {DriveConstants::kLeftMotor2Port};
  WPI_TalonFX m_rightMaster = {DriveConstants::kRightMotor1Port};
  WPI_TalonFX m_rightSlave  = {DriveConstants::kRightMotor2Port};

  frc::SpeedControllerGroup m_leftMotors{m_leftMaster, m_leftSlave};
  frc::SpeedControllerGroup m_rightMotors{m_rightMaster, m_rightSlave};

  frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};



  frc::ADIS16470_IMU m_imu{ };
};
