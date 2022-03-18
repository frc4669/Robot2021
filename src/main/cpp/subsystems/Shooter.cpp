// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h> // for debugging

Shooter::Shooter() {
  // Invert motors if needed
  m_masterShooterMotor.SetInverted(false);

  // Set slave motor to follow master motor
  m_slaveShooterMotor.Follow(m_masterShooterMotor, true);

  m_masterPIDController.SetP(0.00);     // kP
  m_masterPIDController.SetD(0.00);     // kD
  m_masterPIDController.SetFF(0.0002);  // kFF

  // Setup hood motors
  //!: ClearPos on Forward limit should be set on Enabled 
  m_rightHoodMotor.SetInverted(true);
  m_rightHoodMotor.Follow(m_leftHoodMotor); //follow left climb motor

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
  frc::SmartDashboard::PutNumber("Master Shooter Velocity", GetMasterShooterVelocity());
  frc::SmartDashboard::PutNumber("Slave Shooter Velocity", GetSlaveShooterVelocity());

  frc::SmartDashboard::PutNumber("Hood Pos", GetHoodPosition());
  frc::SmartDashboard::PutNumber("Hood Angle", GetHoodAngle());
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