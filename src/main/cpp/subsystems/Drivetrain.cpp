// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"

Drivetrain::Drivetrain() {
    // Disable safety on the drivetrain motors
    m_drive.SetSafetyEnabled(false);

    // Configure the drivetrain motors (for now)
    m_leftMaster.ConfigFactoryDefault();
    m_leftSlave.Follow(m_leftMaster);

    m_rightMaster.ConfigFactoryDefault();
    m_rightSlave.Follow(m_rightMaster);

    // Reset encoder values to 0 (this also syncs the motor controllers)
    ResetEncoders();

    // TODO: SmartDashboard stuff
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    // TODO: SmartDashboard encoder stuff
}

void Drivetrain::ArcadeDrive(double fwd, double rot) {
    m_drive.ArcadeDrive(fwd, rot);
}

double Drivetrain::GetTicksToTravel(double inches) {
    if (shiftedToHighGear) {
        return (inches * DriveConstants::kTicksPerInchesHighGear);
    } else {
        return (inches * DriveConstants::kTicksPerInchesLowGear);
    }
}

void Drivetrain::DriveForward(double inches) {\
    double ticksToTravel = GetTicksToTravel(inches);

    m_leftMaster.Set(ControlMode::MotionMagic, ticksToTravel);
    m_leftSlave.Set(ControlMode::Follower, DriveConstants::kLeftMotor1Port);

    m_rightMaster.Set(ControlMode::MotionMagic, ticksToTravel);
    m_rightSlave.Set(ControlMode::Follower, DriveConstants::kRightMotor1Port);
}

void Drivetrain::RotateByAngle(double angle) {
    // TODO: Rotate by angle using encoders
}


void Drivetrain::ResetLeftEncoder() {
    m_leftMaster.GetSensorCollection().SetIntegratedSensorPosition(0);
}

void Drivetrain::ResetRightEncoder() {
    m_rightMaster.GetSensorCollection().SetIntegratedSensorPosition(0);
}

void Drivetrain::ResetEncoders() {
    ResetLeftEncoder();
    ResetRightEncoder();
}

double Drivetrain::GetLeftEncoderDistance() {
    return m_leftMaster.GetSensorCollection().GetIntegratedSensorPosition();
}

double Drivetrain::GetRightEncoderDistance() {
    return m_rightMaster.GetSensorCollection().GetIntegratedSensorPosition();
}


units::degree_t Drivetrain::GetHeading() {
    // return units::degree_t(std::remainder(m_imu.GetAngle(), 360.0)) * (DriveConstants::kGyroReversed ? -1.0 : 1.0); // !: Come back to this
    return units::degree_t(0); // temp
}

frc::ADIS16470_IMU& Drivetrain::GetIMU() {
    return m_imu;
}

void Drivetrain::ShiftGear() {
    if(IsShiftedToHighGear()) { // check if in high gear
        m_shifter.Set(frc::DoubleSolenoid::kReverse); // shift to low gear
        shiftedToHighGear = false;
    } else {
        m_shifter.Set(frc::DoubleSolenoid::kForward); // shift to high gear
        shiftedToHighGear = true;
    }
}

bool Drivetrain::IsShiftedToHighGear() {
    return shiftedToHighGear;
}