// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/SpeedController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <ctre/Phoenix.h>       // talon
#include <frc/ADIS16470_IMU.h>  // imu
#include <frc/DoubleSolenoid.h> // gear shifter solenoid

#include <Constants.h>

class Drivetrain : public frc2::SubsystemBase
{
public:
  Drivetrain();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Drive robot using arcade controls
   *
   * @param fwd Forward/backward value
   * @param rot Rotation value
   */
  void ArcadeDrive(double fwd, double rot);

  /**
   * Get ticks needed to travel given distance in inches
   *
   * @param inches Distance in inches
   * @return Ticks needed to travel given distance
   */
  double GetTicksToTravel(double inches);

  /**
   * Drive robot given a set distance using encoders
   *
   * @param inches Distance to travel
   */
  void DriveForward(double inches);

  /**
   * Rotate robot using given angle where positive is clockwise, and vice versa
   *
   * @param angle Angle to rotate to
   */
  void RotateByAngle(double angle);

  // Encoder stuff
  /**
   * Reset the left encoder to 0
   */
  void ResetLeftEncoder();

  /**
   * Reset the right encoder to 0
   */
  void ResetRightEncoder();

  /**
   * Reset both encoders to 0
   */
  void ResetEncoders();

  /**
   * Gets distance of encoder on the left gearbox
   *
   * @return Average of the two encoders in the left gearbox
   */
  double GetLeftEncoderDistance();

  /**
   * Gets distance of encoder on the right gearbox
   *
   * @return Average of the two encoders in the right gearbox
   */
  double GetRightEncoderDistance();

  /**
   * Returns heading of the robot
   *
   * @return in degrees, the heading of the robot from -180 to 180
   */
  units::degree_t GetHeading();

  /**
   * Gets current IMU
   *
   * @return pointer to the IMU object
   */
  frc::ADIS16470_IMU &GetIMU();

  /**
   * Shifts the gearbox solenoid to the other gear
   */
  void ShiftGear();

  /**
   * Returns whether the robot is in high gear
   *
   * @return true if the robot is in high gear, true otherwise
   */
  bool IsShiftedToHighGear();

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Motor controllers
  WPI_TalonFX m_leftMaster{DriveConstants::kLeftMotor1Port};
  WPI_TalonFX m_leftSlave{DriveConstants::kLeftMotor2Port};
  WPI_TalonFX m_rightMaster{DriveConstants::kRightMotor1Port};
  WPI_TalonFX m_rightSlave{DriveConstants::kRightMotor2Port};

  // Link motor controllers together (since we have two on each gearbox)
  frc::MotorControllerGroup m_leftMotors{m_leftMaster, m_leftSlave};
  frc::MotorControllerGroup m_rightMotors{m_rightMaster, m_rightSlave};

  // Robot's main drive object
  frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};

  // Shifter for gearboxes (solenoid)
  frc::DoubleSolenoid m_shifter{frc::PneumaticsModuleType::CTREPCM, DriveConstants::kGearShifterForwardChannel, DriveConstants::kGearShifterReverseChannel};
  bool shiftedToHighGear = true;

  frc::ADIS16470_IMU m_imu{};

  /**
   * Configure motor to desired settings
   *
   * @param motor Motor to configure
   * @param invert Whether to invert the motor
   */
  void ConfigureMotor(WPI_TalonFX &motor, bool inverted);
};
