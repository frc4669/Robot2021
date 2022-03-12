// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <ctre/Phoenix.h>       // talon

#include <Constants.h>

class Climber : public frc2::SubsystemBase {
 public:
  Climber();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;


  void RaiseExtendingArms();

  void LowerExtendingArms();

  void StopExtendingArms();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX m_leftMotor{ClimbConstants::kLeftMotorPort};
  WPI_TalonFX m_rightMotor{ClimbConstants::kRightMotorPort};

  frc::MotorControllerGroup m_climbMotors{m_leftMotor, m_rightMotor};
};