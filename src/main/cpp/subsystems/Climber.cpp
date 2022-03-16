// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"

Climber::Climber() {
  m_leftMotor.SetInverted(true);
  m_leftMotor.Set(ControlMode::Follower, ClimbConstants::kRightMotorPort); //follow right climb motor

  m_rightMotor.ConfigNominalOutputForward(0);
  m_rightMotor.ConfigNominalOutputReverse(0);
  m_rightMotor.ConfigPeakOutputForward(1);
  m_rightMotor.ConfigPeakOutputReverse(-1);

  m_rightMotor.ConfigMotionCruiseVelocity(1500); // 2500
  m_rightMotor.ConfigMotionAcceleration(1500);

  m_rightMotor.SetNeutralMode(NeutralMode::Brake);
};

// This method will be called once per scheduler run
void Climber::Periodic() {}

void Climber::RaiseExtendingArms() {
  m_rightMotor.Set(ControlMode::PercentOutput, 0.8);
}

void Climber::LowerExtendingArms() {
  m_rightMotor.Set(ControlMode::PercentOutput, -0.8);
}

void Climber::StopExtendingArms() {
  m_rightMotor.Set(ControlMode::PercentOutput, 0.0);
}