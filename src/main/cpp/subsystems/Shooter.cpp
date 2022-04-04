// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h> // for debugging

Shooter::Shooter() {
  // Invert motors if needed
  m_leftShooterMotor.SetInverted(true);

  // Set slave motor to follow master motor, but inverted
  m_rightShooterMotor.Follow(m_leftShooterMotor, true);

  m_masterPIDController.SetP(0.00);     // kP
  m_masterPIDController.SetD(0.00);     // kD
  m_masterPIDController.SetFF(0.0002);  // kFF

  // Setup hood motors
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
  frc::SmartDashboard::PutNumber("Master Shooter Active Velocity", GetMasterShooterVelocity());
  frc::SmartDashboard::PutNumber("Slave Shooter Active Velocity", GetSlaveShooterVelocity());
  frc::SmartDashboard::PutNumber("Shooter Set Velocity", GetShooterSetSpeed());
}

void Shooter::RunShooter(bool stopShooter) {
  double setVelocity = stopShooter ? 0 : kShooterVelocity;

  m_masterPIDController.SetReference(setVelocity, rev::ControlType::kVelocity);
  //?: Slave shooter motor not set because it's already following the master motor
}

double Shooter::GetMasterShooterVelocity() {
  return m_masterEncoder.GetVelocity();
}

double Shooter::GetSlaveShooterVelocity() {
  return abs(m_slaveEncoder.GetVelocity());
}

double Shooter::GetShooterSetSpeed() {
  return kShooterVelocity;
}

void Shooter::IncrementShooterSetSpeed(double increment) {
  if(kShooterVelocity + increment < kMaxShooterVelocity && kShooterVelocity + increment > 0)
    kShooterVelocity += increment;
}

//!: CTRE Tuner, Software Limit Switches, Forward Limit Switch Enable = True