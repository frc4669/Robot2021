// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/Trajectory.h>

#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/PathPlannerTrajectory.h>

using namespace pathplanner;

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
  m_odometry.Update(GetRotation(), GetLeftDistanceMeters(), GetRightDistanceMeters());

  frc::SmartDashboard::PutNumber("Left Velocity", GetLeftVelocity());
  frc::SmartDashboard::PutNumber("Right Velocity", GetRightVelocity());

  frc::SmartDashboard::PutBoolean("In High Gear", IsShiftedToHighGear());

  frc::SmartDashboard::PutBoolean("Can Turn In Place", IsCurvatureDriveEnabled());
  frc::SmartDashboard::PutBoolean("Forward Towards Intake", IsForwardTowardIntake());
}

void Drivetrain::CurvatureDrive(double fwd, double rot, bool fromController) {
  //?: If forward towards intake, use normal turning, if not, inverse turning
  rot = kForwardTowardIntake ? rot : -rot;
  rot = kcontrollerMoveEnabled ? rot : 0;

  //?: Same as arcade drive, except you can toggle on and off the ability to turn in place or use curvature drive
  m_drive.CurvatureDrive(fwd, rot, kTurnInPlaceEnabled);
}

frc::Trajectory Drivetrain::GetAutoTrajectory() {
  PathPlannerTrajectory autonomousPath = PathPlanner::loadPath(AUTO_TRAJECTORY, 1.5_mps, 2_mps_sq);
  frc::Trajectory trajectory = autonomousPath.asWPILibTrajectory();
  return trajectory;
}

frc::Pose2d Drivetrain::GetAutoInitialPose() {
  PathPlannerTrajectory autonomousPath = PathPlanner::loadPath(AUTO_TRAJECTORY, 1.5_mps, 2_mps_sq);
  return autonomousPath.getInitialState()->pose;
}

frc::Rotation2d Drivetrain::GetAutoInitialRotation() {
  PathPlannerTrajectory autonomousPath = PathPlanner::loadPath(AUTO_TRAJECTORY, 1.5_mps, 2_mps_sq);
  return autonomousPath.getInitialState()->pose.Rotation();
}

void Drivetrain::ToggleCurvatureTurnInPlace() {
  kTurnInPlaceEnabled = !kTurnInPlaceEnabled;
}

bool Drivetrain::IsCurvatureDriveEnabled() {
  return kTurnInPlaceEnabled;
}

double Drivetrain::GetTicksToTravel(double inches) {
  //?: If shifted to high gear, use the high gear ticks per inch, otherwise use the low gear one
  double ticksPerInch = kShiftedToHighGear ? DriveGearingConstants::kTicksPerInch_HighGear : DriveGearingConstants::kTicksPerInch_LowGear;
  
  return (inches * ticksPerInch);
}

void Drivetrain::DriveForward(double ticksToTravel) {
  //?: Set master motors to move using motion magic, slave motors not called (they are following the master)

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

double Drivetrain::GetLeftVelocity() {
  return m_leftMaster.GetSensorCollection().GetIntegratedSensorVelocity();
}

double Drivetrain::GetRightVelocity() {
  return m_rightMaster.GetSensorCollection().GetIntegratedSensorVelocity();
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
  return m_imu.GetAngle();
  // return units::degree_t(0);
}

frc::Rotation2d Drivetrain::GetRotation() {
  return frc::Rotation2d(m_imu.GetAngle());
}

frc::RamseteController& Drivetrain::GetRamseteController() {
  return m_ramseteController;
}

frc::DifferentialDriveKinematics& Drivetrain::GetKinematics() {
  return m_driveKinematics;
}

frc::ADIS16470_IMU& Drivetrain::GetIMU() {
  return m_imu;
}

void Drivetrain::ShiftGear() {
  if (IsShiftedToHighGear()) { // check if in high gear
    m_shifter.Set(frc::DoubleSolenoid::kReverse); // shift to low gear
    kShiftedToHighGear = false;
    m_rightMaster.ConfigOpenloopRamp(0.2);
    m_leftMaster.ConfigOpenloopRamp(0.2);
  } else {
    m_shifter.Set(frc::DoubleSolenoid::kForward); // shift to high gear
    kShiftedToHighGear = true;
    m_rightMaster.ConfigOpenloopRamp(0.4);
    m_leftMaster.ConfigOpenloopRamp(0.4);
  }
}

bool Drivetrain::IsShiftedToHighGear() {
  return kShiftedToHighGear;
}

void Drivetrain::ReverseRelativeFront() {
  // basically gets the inverted status and adds "!" to it which inverts it
  if(kForwardTowardIntake) {
    m_leftMaster.SetInverted(false);
    m_leftSlave.SetInverted(false);

    m_rightMaster.SetInverted(true);
    m_rightSlave.SetInverted(true);
  } else {
    m_leftMaster.SetInverted(true);
    m_leftSlave.SetInverted(true);

    m_rightMaster.SetInverted(false);
    m_rightSlave.SetInverted(false);
  } 

  kForwardTowardIntake = !kForwardTowardIntake;
}

bool Drivetrain::IsForwardTowardIntake() {
  return kForwardTowardIntake;
}

void Drivetrain::ChangeControllerAccess(bool changeTo) {
  kcontrollerMoveEnabled = changeTo;
}

bool Drivetrain::DoesControllerHaveMovementRights() {
  return kcontrollerMoveEnabled;
}

void Drivetrain::tempKpChange() {
  m_leftMaster.Config_kP(0, 2.1706); // kP, the proportional constant (how fast the motor changes speed), acts like a “software-defined springs”
  m_leftSlave.Config_kP(0, 2.1706); // kP, the proportional constant (how fast the motor changes speed), acts like a “software-defined springs”

  m_rightMaster.Config_kP(0, 2.1706); // kP, the proportional constant (how fast the motor changes speed), acts like a “software-defined springs”
  m_rightSlave.Config_kP(0, 2.1706); // kP, the proportional constant (how fast the motor changes speed), acts like a “software-defined springs”
}

void Drivetrain::ConfigureMotor(WPI_TalonFX &motor, bool inverted) {
  // set the max velocity and acceleration for motion magic
  motor.ConfigMotionCruiseVelocity(20000);
  motor.ConfigMotionAcceleration(7000);

  // set the current limit for the supply/output current
  motor.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 25, 25, 0.5));
  motor.ConfigStatorCurrentLimit(StatorCurrentLimitConfiguration(true, 25, 25, 0.5));

  // time it takes for the motor to go from 0 to full power (in seconds) in an open/closed loop
  motor.ConfigOpenloopRamp(0.2);
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
  motor.Config_kD(0, 0.00); // kD, the derivative constant (drives the velocity error to zero)
  motor.Config_kF(0, 0.00); // kF, the feed forward constant (how much the output is affected by the setpoint)
}

void Drivetrain::ResetOdometry(frc::Pose2d pose, frc::Rotation2d angle) {
  ResetEncoders();
  m_odometry.ResetPosition(pose, angle);
}

units::meter_t Drivetrain::GetLeftDistanceMeters() {
  return units::meter_t(
    units::inch_t(
      m_leftMaster.GetSensorCollection().GetIntegratedSensorPosition() * ( IsShiftedToHighGear() ? DriveConstants::kInchesPerTicksHighGear : DriveConstants::kInchesPerTicksLowGear )
    )
  );
}

units::meter_t Drivetrain::GetRightDistanceMeters() {
  return units::meter_t(
    units::inch_t(
      m_rightMaster.GetSensorCollection().GetIntegratedSensorPosition() * ( IsShiftedToHighGear() ? DriveConstants::kInchesPerTicksHighGear : DriveConstants::kInchesPerTicksLowGear )
    )
  );
}

units::meters_per_second_t Drivetrain::GetLeftVelMetersPerSecond() {
  double ticksPerSecond = m_leftMaster.GetSensorCollection().GetIntegratedSensorVelocity() * 10;
  double velMpS = ticksPerSecond * (IsShiftedToHighGear() ? DriveConstants::kInchesPerTicksHighGear : DriveConstants::kInchesPerTicksLowGear);

  return units::meters_per_second_t(
    units::meter_t(units::inch_t(velMpS)).value()
  );
}

units::meters_per_second_t Drivetrain::GetRightVelMetersPerSecond() {
  double ticksPerSecond = m_rightMaster.GetSensorCollection().GetIntegratedSensorVelocity() * 10;
  double velMpS = ticksPerSecond * (IsShiftedToHighGear() ? DriveConstants::kInchesPerTicksHighGear : DriveConstants::kInchesPerTicksLowGear);

  return units::meters_per_second_t(
    units::meter_t(units::inch_t(velMpS)).value()
  );
}

frc::DifferentialDriveWheelSpeeds Drivetrain::GetWheelSpeeds() {
  return {
    GetLeftVelMetersPerSecond(),
    GetRightVelMetersPerSecond()
  };
}

frc::Pose2d Drivetrain::GetCurrentPose() {
  return m_odometry.GetPose();
}

void Drivetrain::SetLeftVoltage(units::volt_t voltage) {
  m_leftMaster.SetVoltage(voltage);
}

void Drivetrain::SetRightVoltage(units::volt_t voltage) {
  m_rightMaster.SetVoltage(voltage);
}

frc::SimpleMotorFeedforward <units::meters> Drivetrain::GetFeedforward() {
  return m_feedforward;
}
