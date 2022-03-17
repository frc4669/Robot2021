// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include <frc/smartdashboard/SmartDashboard.h>

Climber::Climber() {
  ConfigureMotor(m_rightMotor, true);
  ConfigureMotor(m_leftMotor, false);

  //m_leftMotor.Follow(m_rightMotor); //follow right climb motor
};

// This method will be called once per scheduler run
void Climber::Periodic() {
  frc::SmartDashboard::PutNumber("right climb", abs(m_rightMotor.GetSensorCollection().GetIntegratedSensorPosition()));
  frc::SmartDashboard::PutNumber("left climb", abs(m_leftMotor.GetSensorCollection().GetIntegratedSensorPosition()));

  frc::SmartDashboard::PutBoolean("right switch", IsRightLimitHit());
  frc::SmartDashboard::PutBoolean("left switch", IsLeftLimitHit());
  frc::SmartDashboard::PutBoolean("arms zeroed", AreArmsZeroed());

  if(!armsZeroed)
    ZeroArms();
}

void Climber::RaiseExtendingArms() {
  m_rightMotor.Set(ControlMode::PercentOutput, -0.8);
}

void Climber::LowerExtendingArms() {
  m_rightMotor.Set(ControlMode::PercentOutput, 0.5);
}

void Climber::StopExtendingArms() {
  m_rightMotor.Set(ControlMode::PercentOutput, 0.0);
}

void Climber::ZeroArms() {
  if(!IsLeftLimitHit())
    m_leftMotor.Set(ControlMode::PercentOutput, 0.8);
  
  if(IsLeftLimitHit() && !IsRightLimitHit())
    m_rightMotor.Set(ControlMode::PercentOutput, 0.8);

  if(IsLeftLimitHit() && IsRightLimitHit()) {
    armsZeroed = true;
    m_leftMotor.Follow(m_rightMotor);
  }
}

bool Climber::AreArmsZeroed() {
  return armsZeroed;
}

bool Climber::IsRightLimitHit() {
  return m_rightMotor.GetSensorCollection().IsFwdLimitSwitchClosed();
}

bool Climber::IsLeftLimitHit() {
  return m_leftMotor.GetSensorCollection().IsFwdLimitSwitchClosed();
}

void Climber::ConfigureMotor(WPI_TalonFX &motor, bool inverted) {
  //!: LimitReverse should be set on Disabled
  //!: ClearPos on Forward limit should be set on Enabled 

  motor.SetInverted(inverted);  

  motor.ConfigNominalOutputForward(0);
  motor.ConfigNominalOutputReverse(0);
  motor.ConfigPeakOutputForward(1);
  motor.ConfigPeakOutputReverse(-1);

  motor.ConfigMotionCruiseVelocity(1500); // 2500
  motor.ConfigMotionAcceleration(1500);

  motor.SetNeutralMode(NeutralMode::Brake);
}