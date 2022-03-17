// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>

Drivetrain::Drivetrain() {
  // Disable safety on the drivetrain motors
  m_drive.SetSafetyEnabled(false);

  // Configure the drivetrain motors (for now)
  ConfigureMotor(m_leftMaster, true);
  ConfigureMotor(m_leftSlave, true);
  m_leftSlave.Follow(m_leftMaster); // set back left motor to follow the front left motor

  ConfigureMotor(m_rightMaster, false);
  ConfigureMotor(m_rightSlave, false);
  m_rightSlave.Follow(m_rightMaster); // set back right motor to follow the front right motor

  // Reset encoder values to 0 (this also syncs the motor controllers)
  ResetEncoders();

  // Shift into low gear by default (because we don't know if the last session was left in high gear)
  m_shifter.Set(frc::DoubleSolenoid::kReverse);

  //frc::Shuffleboard::GetTab("IMU Gyro").Add(m_imu); //!: Come back to this
}

// This method will be called once per scheduler run
void Drivetrain::Periodic() {
  // setup smartdashboard to show our drivetrain values
  frc::SmartDashboard::PutNumber("Left Encoder", GetLeftEncoderDistance());
  frc::SmartDashboard::PutNumber("Right Encoder", GetRightEncoderDistance());

  frc::SmartDashboard::PutNumber("Left Velocity", GetLeftVel());
  frc::SmartDashboard::PutNumber("Right Velocity", GetRightVel());

  frc::SmartDashboard::PutBoolean("Shifted to High", IsShiftedToHighGear());
}

void Drivetrain::CurvatureDrive(double fwd, double rot) {
  //?: Same as arcade drive, except you can toggle on and off the ability to turn in place or use curvature drive
  m_drive.CurvatureDrive(fwd, rot, m_curvatureDriveTurnInPlace);
}

void Drivetrain::ToggleCurvatureTurnInPlace() {
  m_curvatureDriveTurnInPlace = !m_curvatureDriveTurnInPlace;
}

bool Drivetrain::GetCurvatureTurnInPlaceStatus() {
  return m_curvatureDriveTurnInPlace;
}

double Drivetrain::GetTicksToTravel(double inches) {
  if (m_shiftedToHighGear)
    return (inches * DriveConstants::kTicksPerInchesHighGear);
  else
    return (inches * DriveConstants::kTicksPerInchesLowGear);
}

void Drivetrain::DriveForward(double ticksToTravel) {
  m_leftMaster.Set(ControlMode::MotionMagic, ticksToTravel);
  m_rightMaster.Set(ControlMode::MotionMagic, ticksToTravel);
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

double Drivetrain::GetLeftVel() {
  return m_leftMaster.GetSensorCollection().GetIntegratedSensorVelocity();
}

double Drivetrain::GetRightVel() {
  return m_rightMaster.GetSensorCollection().GetIntegratedSensorVelocity();
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
  return units::degree_t(0);
}

frc::ADIS16470_IMU& Drivetrain::GetIMU() {
  return m_imu;
}

void Drivetrain::ShiftGear() {
  if (IsShiftedToHighGear()) { // check if in high gear
    m_shifter.Set(frc::DoubleSolenoid::kReverse); // shift to low gear
    m_shiftedToHighGear = false;
  } else {
    m_shifter.Set(frc::DoubleSolenoid::kForward); // shift to high gear
    m_shiftedToHighGear = true;
  }
}

bool Drivetrain::IsShiftedToHighGear() {
  return m_shiftedToHighGear;
}

void Drivetrain::ReverseRelativeFront() {
  // basically gets the inverted status and adds "!" to it which inverts it
  m_leftMaster.SetInverted(!m_leftMaster.GetInverted());
  m_leftSlave.SetInverted(!m_leftSlave.GetInverted());

  m_rightMaster.SetInverted(!m_rightMaster.GetInverted());
  m_rightSlave.SetInverted(!m_rightSlave.GetInverted());
}

void Drivetrain::ConfigureMotor(WPI_TalonFX &motor, bool inverted) {
  // set the max velocity and acceleration for motion magic
  motor.ConfigMotionCruiseVelocity(20000);
  motor.ConfigMotionAcceleration(6000);

  // set the current limit for the supply/output current
  motor.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 25, 25, 0.5));
  motor.ConfigStatorCurrentLimit(StatorCurrentLimitConfiguration(true, 25, 25, 0.5));

  // time it takes for the motor to go from 0 to full power (in seconds) in an open/closed loop
  motor.ConfigOpenloopRamp(2);
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
