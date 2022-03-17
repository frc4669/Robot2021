// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Intake.h"
#include <frc/smartdashboard/SmartDashboard.h>

Intake::Intake() {
  // Start robot with intake retracted
  m_intakeArm.Set(frc::DoubleSolenoid::kReverse);
  m_intakeMotor.SetInverted(true);
}

// This method will be called once per scheduler run
void Intake::Periodic() {
  frc::SmartDashboard::PutBoolean("Intake Arm Deployed", IsArmExtended());
}

void Intake::ManipulateArm() {
  if (IsArmExtended()) {
    m_intakeArm.Set(frc::DoubleSolenoid::kReverse);
    m_intakeArmExtended = false;
  } else {
    m_intakeArm.Set(frc::DoubleSolenoid::kForward);
    m_intakeArmExtended = true;
  }
}

bool Intake::IsArmExtended() {
  return m_intakeArmExtended;
}

void Intake::RunIntake(bool runReverse) {
  if (runReverse)
    m_intakeMotor.Set(ControlMode::PercentOutput, -0.8);
  else
    m_intakeMotor.Set(ControlMode::PercentOutput, 0.8);
}

void Intake::StopIntake() {
  m_intakeMotor.Set(ControlMode::PercentOutput, 0.0);
}

void Intake::RunFeeder(bool runReverse) {
  if (runReverse)
    m_feederMotor.Set(ControlMode::PercentOutput, -0.5);
  else
    m_feederMotor.Set(ControlMode::PercentOutput, 0.5);
}

void Intake::StopFeeder() {
  m_feederMotor.Set(ControlMode::PercentOutput, 0.0);
}
