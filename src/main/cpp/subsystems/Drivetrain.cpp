// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/SmartDashboard.h>

Drivetrain::Drivetrain() {
    // Disable safety on the drivetrain motors
    m_drive.SetSafetyEnabled(false);

    // Configure the drivetrain motors (for now)
    ConfigureMotor(m_leftMaster, true);
    ConfigureMotor(m_leftSlave, true);

    ConfigureMotor(m_rightMaster, false);
    ConfigureMotor(m_rightSlave, false);

    // Reset encoder values to 0 (this also syncs the motor controllers)
    ResetEncoders();

    // Shift into low gear by default (because we don't know if the last session was left in high gear)
    m_shifter.Set(frc::DoubleSolenoid::kReverse);
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
    // setup smartdashboard to show our drivetrain values
    frc::SmartDashboard::PutNumber("Left Encoder", m_leftMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Right Encoder", m_rightMaster.GetSelectedSensorPosition());

    frc::SmartDashboard::PutNumber("Left Velocity", m_leftMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Right Velocity", m_rightMaster.GetSelectedSensorVelocity());

    frc::SmartDashboard::PutBoolean("Shifted to High", IsShiftedToHighGear());
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

void Drivetrain::DriveForward(double inches, double velocity = 40000) {
    // set velocity using motion magic
    m_leftMaster.Set(ControlMode::MotionMagic, velocity);
    m_leftSlave.Set(ControlMode::Follower, DriveConstants::kLeftMotor1Port);

    m_rightMaster.Set(ControlMode::MotionMagic, velocity);
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
    return -m_leftMaster.GetSensorCollection().GetIntegratedSensorPosition();
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

void Drivetrain::ConfigureMotor(WPI_TalonFX &motor, bool inverted) {
    // set the max velocity and acceleration for motion magic
    motor.ConfigMotionCruiseVelocity(20000);
    motor.ConfigMotionAcceleration(8000);

    // set the current limit for the supply/output current
    motor.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 25, 25, 0.5));
    motor.ConfigStatorCurrentLimit(StatorCurrentLimitConfiguration(true, 25, 25, 0.5));

    // time it takes for the motor to go from 0 to full power (in seconds) in an open/closed loop
    motor.ConfigOpenloopRamp(0.8);
    motor.ConfigClosedloopRamp(0);

    // when controller is neutral, set motor to break
    motor.SetNeutralMode(NeutralMode::Brake);

    // disable motor safety
    motor.SetSafetyEnabled(false);

    // motor set experation time
    motor.SetExpiration(100_ms);

    // invert the motor if necessary
    motor.SetInverted(inverted);

    // Motor PID values (for now)
    motor.Config_kP(0, 0.01); // kP, the proportional constant (how fast the motor changes speed), acts like a “software-defined springs”
    motor.Config_kD(0, 0.02); // kD, the derivative constant (drives the velocity error to zero)
    motor.Config_kF(0, 0.05); // kF, the feed forward constant (how much the output is affected by the setpoint)
}