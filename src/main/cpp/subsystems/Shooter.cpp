// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h> // for debugging

Shooter::Shooter() {
    // Invert master shooter motor
    m_masterShooterMotor.SetInverted(false);
    m_slaveShooterMotor.SetInverted(false);

    // Set slave motor to follow master motor
    m_slaveShooterMotor.Follow(m_masterShooterMotor, true);

    m_masterPIDController.SetP(0.00); // kP
    m_masterPIDController.SetD(0.00); // kD
    m_masterPIDController.SetFF(0.0002);   // kFF
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    frc::SmartDashboard::PutNumber("Master Shooter Velocity", GetMasterShooterVelocity());
    frc::SmartDashboard::PutNumber("Slave Shooter Velocity", GetSlaveShooterVelocity());
}

void Shooter::RunShooter(double velocity) {
    m_masterPIDController.SetReference(velocity, rev::ControlType::kVelocity);
    // dont need to set slave to reference too since its following master
}

void Shooter::StopShooter() {
    RunShooter(0);
}

double Shooter::GetMasterShooterVelocity() {
    return m_masterEncoder.GetVelocity();
}

double Shooter::GetSlaveShooterVelocity() {
    return m_slaveEncoder.GetVelocity();
}