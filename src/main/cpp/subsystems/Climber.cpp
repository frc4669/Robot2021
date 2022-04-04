// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"

#include <frc/smartdashboard/SmartDashboard.h>

Climber::Climber() {
  ConfigureMotor(m_staticRight, true);
  ConfigureMotor(m_staticLeft, false);
}

// This method will be called once per scheduler run
void Climber::Periodic() {
  frc::SmartDashboard::PutNumber("Right Climber Position", GetRightPostion());
  frc::SmartDashboard::PutNumber("Left Climber Position", GetLeftPosition());

  frc::SmartDashboard::PutBoolean("Right Limit Switch Triggered", IsRightLimitHit());
  frc::SmartDashboard::PutBoolean("Left Limit Switch Triggered", IsLeftLimitHit());
  frc::SmartDashboard::PutBoolean("Arms Zeroed", AreArmsZeroed());

  //if(AreArmsZeroed() == false)
    //ZeroArms();
}

void Climber::RaiseExtendingArms() {
  m_staticRight.Set(ControlMode::PercentOutput, -0.8);
}

void Climber::LowerExtendingArms() {
  m_staticRight.Set(ControlMode::PercentOutput, 0.8);
}

void Climber::StopExtendingArms() {
  m_staticRight.Set(ControlMode::PercentOutput, 0.0);
}

void Climber::ZeroArms() {
  // Lower slave motor if not at base position
  //?: slave motor lowered first because if the master hits the limit switch, the slave will not be able to move
  if(!IsLeftLimitHit())
    m_staticLeft.Set(ControlMode::PercentOutput, 0.1);
  
  // Lower master motor if not at base position once slave motor is at base position
  if(!IsRightLimitHit())
    m_staticRight.Set(ControlMode::PercentOutput, 0.1);

  // If both motors are at base position, stop the periodic loop, they have now been synchronized
  if(IsLeftLimitHit() && IsRightLimitHit()) {
    kArmsZeroed = true;
    m_staticLeft.Follow(m_staticRight);
    StopExtendingArms();
  }
}

bool Climber::AreArmsZeroed() {
  return kArmsZeroed;
}

bool Climber::IsRightLimitHit() {
  return m_staticRight.GetSensorCollection().IsFwdLimitSwitchClosed();
}

bool Climber::IsLeftLimitHit() {
  return m_staticLeft.GetSensorCollection().IsFwdLimitSwitchClosed();
}

double Climber::GetRightPostion() {
  return m_staticRight.GetSensorCollection().GetIntegratedSensorPosition();
}

double Climber::GetLeftPosition() {
  //?: invert is needed because the slave motor is inverted
  return -m_staticLeft.GetSensorCollection().GetIntegratedSensorPosition();
}

void Climber::ConfigureMotor(WPI_TalonFX &motor, bool inverted) {
  //!: LimitReverse should be set on Disabled
  //!: ClearPos on Forward limit should be set on Enabled 

  motor.SetInverted(inverted);  

  motor.ConfigNominalOutputForward(0);
  motor.ConfigNominalOutputReverse(0);
  motor.ConfigPeakOutputForward(1);
  motor.ConfigPeakOutputReverse(-1);

  // Set velocity and acceleration limits for motion magic
  motor.ConfigMotionCruiseVelocity(1500);
  motor.ConfigMotionAcceleration(1500);

  motor.SetNeutralMode(NeutralMode::Brake); //?: Brake mode so the motor doesn't unspool when hanging
}