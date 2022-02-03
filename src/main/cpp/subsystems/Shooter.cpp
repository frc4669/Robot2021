// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"

Shooter::Shooter() {
    // Invert master shooter motor
    masterShooterMotor.SetInverted(true);
    slaveShooterMotor.SetInverted(true);

    // Set slave to follow
    slaveShooterMotor.Follow(masterShooterMotor, true);

    masterPIDController.SetP(0.00); // kP
    masterPIDController.SetI(0.00); // kI
    masterPIDController.SetD(0.00); // kD
    masterPIDController.SetFF(0.0001947);   // kFF
}

// This method will be called once per scheduler run
void Shooter::Periodic() {}

void Shooter::RunShooter(double velocity) {
    masterPIDController.SetReference(-velocity, rev::ControlType::kVelocity);
}

void Shooter::StopShooter() {
    RunShooter(0);
}

double Shooter::GetShooterVelocity() {
    return masterPIDController.GetSmartMotionMaxVelocity(); // maybe work maybe dont we dont know
}