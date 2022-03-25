// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h> // for debugging

Shooter::Shooter() {
  // Invert motors if needed
  m_masterShooterMotor.SetInverted(true);

  // Set slave motor to follow master motor
  m_slaveShooterMotor.Follow(m_masterShooterMotor, true);

  m_masterPIDController.SetP(0.00);     // kP
  m_masterPIDController.SetD(0.00);     // kD
  m_masterPIDController.SetFF(0.0002);  // kFF

  // Setup hood motors
  //!: ClearPos on Forward limit should be set on Enabled 
  m_rightHoodMotor.SetInverted(true);

  m_leftHoodMotor.ConfigNominalOutputForward(0);
  m_leftHoodMotor.ConfigNominalOutputReverse(0);
  m_leftHoodMotor.ConfigPeakOutputForward(1);
  m_leftHoodMotor.ConfigPeakOutputReverse(-1);

  m_leftHoodMotor.ConfigMotionCruiseVelocity(1500);
  m_leftHoodMotor.ConfigMotionAcceleration(1500);

  m_leftHoodMotor.SetNeutralMode(NeutralMode::Brake);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
  frc::SmartDashboard::PutNumber("Master Shooter Active Velocity", GetMasterShooterVelocity());
  frc::SmartDashboard::PutNumber("Slave Shooter Active Velocity", GetSlaveShooterVelocity());
  frc::SmartDashboard::PutNumber("Shooter Set Velocity", GetShooterSetSpeed());

  //frc::SmartDashboard::PutNumber("Hood Current Position", GetHoodPosition()); //!: Comment out for comp
  frc::SmartDashboard::PutNumber("Hood Current Angle", GetHoodAngle());
  frc::SmartDashboard::PutNumber("Hood Active Velocity", GetHoodActiveVelocity());
  frc::SmartDashboard::PutNumber("Hood Move Speed Percentage", GetHoodSetMoveSpeed());
  frc::SmartDashboard::PutBoolean("Hood Neutral Brake Mode", IsHoodInBreakMode());
  frc::SmartDashboard::PutBoolean("Hood Zeroed", IsHoodZeroed());

  if(IsHoodZeroed() == false)
    ZeroHood();
}

void Shooter::RunShooter() {
  m_masterPIDController.SetReference(m_shooterVelocity, rev::ControlType::kVelocity);
  //?: Slave shooter motor not set because it's already following the master motor
}

void Shooter::StopShooter() {
  m_masterPIDController.SetReference(0.0, rev::ControlType::kVelocity);
}

double Shooter::GetMasterShooterVelocity() {
  return m_masterEncoder.GetVelocity();
}

double Shooter::GetSlaveShooterVelocity() {
  return m_slaveEncoder.GetVelocity();
}

void Shooter::MoveHoodForward() {
  m_leftHoodMotor.Set(ControlMode::PercentOutput, -m_hoodMoveSpeed);
}

void Shooter::MoveHoodBackward() {
  m_leftHoodMotor.Set(ControlMode::PercentOutput, m_hoodMoveSpeed);
}

void Shooter::StopHood() {
  m_leftHoodMotor.Set(ControlMode::PercentOutput, 0.0);
}

double Shooter::GetHoodPosition() {
  return abs(m_leftHoodMotor.GetSensorCollection().GetIntegratedSensorPosition());
}

double Shooter::GetHoodAngle() {
  double ticksPerAngle = ((2048 * 4) * 100) / 360;
  return GetHoodPosition()/ticksPerAngle;
}

double Shooter::GetHoodSetMoveSpeed() {
  return m_hoodMoveSpeed;
}

double Shooter::GetHoodActiveVelocity() {
  return m_leftHoodMotor.GetSensorCollection().GetIntegratedSensorVelocity();
}

void Shooter::SetHoodMoveSpeed(double speed) {
  m_hoodMoveSpeed = speed;
}

double Shooter::GetShooterSetSpeed() {
  return m_shooterVelocity;
}

void Shooter::IncrementShooterSetSpeed(double increment) {
  m_shooterVelocity += increment;
}

void Shooter::IncrementHoodSetSpeed(double increment) {
  m_hoodMoveSpeed += increment;
}

void Shooter::SwitchHoodNeutralMode() {
  if (IsHoodInBreakMode()) {
    m_leftHoodMotor.SetNeutralMode(NeutralMode::Coast);
    m_hoodNeutralBrakeMode = false;
  } else {
    m_leftHoodMotor.SetNeutralMode(NeutralMode::Brake);
    m_hoodNeutralBrakeMode = true;
  }
}

bool Shooter::IsHoodInBreakMode() {
  return m_hoodNeutralBrakeMode;
}

bool Shooter::HoodLimitSwitchTriggered() {
  return m_leftHoodMotor.GetSensorCollection().IsFwdLimitSwitchClosed();
}

void Shooter::ZeroHood() {
/*   if(!HoodLimitSwitchTriggered()) {
    m_rightHoodMotor.Set(ControlMode::PercentOutput, 0.2);
    m_leftHoodMotor.Set(ControlMode::PercentOutput, 0.2);
  }

  if(HoodLimitSwitchTriggered()) { */
    m_hoodZeroed = true;
    StopHood();
    m_rightHoodMotor.Follow(m_leftHoodMotor); //follow left climb motor
  //}
}

bool Shooter::IsHoodZeroed() {
  return m_hoodZeroed;
}