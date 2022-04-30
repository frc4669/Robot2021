// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <ctre/Phoenix.h>       // for hood motor
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

#include <Constants.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Run the shooter at a set velocity.
   *
   * @param stopShooter whether to stop the shooter
   * (defaults to false)
   */
  void RunShooter(bool stopShooter = false);

  /**
   * Get the current velocity of the master shooter
   *
   * @return the current velocity of the master shooter
   */
  double GetMasterShooterVelocity();

  /**
   * Get the current velocity of the slave shooter
   *
   * @return the current velocity of the slave shooter
   */
  double GetSlaveShooterVelocity();

  /**
   * Get the current set velocity of the shooter system.
   *
   * @return set velocity of the shooter system
   */
  double GetSetVelocityPoint();

  /**
   * Move hood by a percentage of its maximum speed.
   *
   * @param percentage Percent of maximum speed to move the hood by
   * (negative moves the hood up, positive moves the hood down)
   * (defaults to 0, stops the hood)
   */
  void MoveHood(double percentage = 0.0);

  /**
   * Sets the hood to a given angle.
   *
   * @param angle in degrees
   */
  void SetHoodAngle(double angle);

  /**
   * Returns the current angle of the hood.
   *
   * @return the current angle of the hood
   */
  double GetHoodAngle();

  double GetShooterSetSpeed();

  void IncrementShooterSetSpeed(double increment);

  bool ShooterWithinSetSpeed();

  bool HoodWithinSetAngle();

 private:
  // Our shooter motors
  rev::CANSparkMax m_leftShooterMotor{ ShooterConstants::kLeftMotorCAN, rev::CANSparkMax::MotorType::kBrushless };
  rev::CANSparkMax m_rightShooterMotor{ ShooterConstants::kRightMotorCAN, rev::CANSparkMax::MotorType::kBrushless };

  // PID controllers so we can slowly ramp up the shooter to a given speed
  rev::SparkMaxPIDController m_masterPIDController{ m_leftShooterMotor.GetPIDController() };
  rev::SparkMaxPIDController m_slavePIDController{ m_rightShooterMotor.GetPIDController() };

  // Motor encoders
  rev::SparkMaxRelativeEncoder m_masterEncoder{ m_leftShooterMotor.GetEncoder() };
  rev::SparkMaxRelativeEncoder m_slaveEncoder{ m_rightShooterMotor.GetEncoder() };


  WPI_TalonSRX m_hoodMotor{ ShooterConstants::kHoodMotorCAN };

  double kShooterVelocity = 4500;
  double kMaxShooterVelocity = 5800;

  double kHoodAngle = 0;
  double kHoodMaxAngle = 90;
};
