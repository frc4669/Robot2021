// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>       // talon

#include <Constants.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Run the shooter with a given velocity.
   */
  void RunShooter();

  /**
   * Stop the shooter
   */
  void StopShooter();

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
   * Get the max velocity of the shooter system.
   * 
   * @return max velocity of the shooter system
   */
  double GetMaxVelocity();

  /**
   * Raise the hood, making a smaller angle.
   */
  void MoveHoodForward();

  /**
   * Lower the hood, making a larger angle.
   */
  void MoveHoodBackward();

  /**
   * Stop the hood motors.
   */
  void StopHood();

  /**
   * Zero the hood to the largest angle. 
   * This is so both hood motors are synchronized.
   */
  void ZeroHood();

  /**
   * Returns whether the hood has been zeroed. 
   * Meaning both hood motors are synchronized.
   * 
   * @return whether the hood has been zeroed
   */
  bool IsHoodZeroed();

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

  /**
   * Switches between Coast and Brake mode while 
   * the hood is neutral.
   */
  void SwitchHoodNeutralMode();

  /**
   * Returns whether the hood is in Break mode while 
   * the hood is neutral.
   * 
   * @return whether the hood is in Break mode 
   */
  bool IsHoodInBreakMode();

  /**
   * Sets how fast the hood will move.
   * 
   * @param speed percentage of max speed
   */
  void SetHoodMoveSpeed(double speed);

 private:
  // Our shooter motors
  rev::CANSparkMax m_masterShooterMotor{ ShooterConstants::kShooterMasterPort, rev::CANSparkMax::MotorType::kBrushless };
  rev::CANSparkMax m_slaveShooterMotor{ ShooterConstants::kShooterSlavePort, rev::CANSparkMax::MotorType::kBrushless };

  // PID controllers so we can slowly ramp up the shooter to a given speed
  rev::SparkMaxPIDController m_masterPIDController{ m_masterShooterMotor.GetPIDController() };
  rev::SparkMaxPIDController m_slavePIDController{ m_slaveShooterMotor.GetPIDController() };

  // Motor encoders
  rev::SparkMaxRelativeEncoder m_masterEncoder{ m_masterShooterMotor.GetEncoder() };
  rev::SparkMaxRelativeEncoder m_slaveEncoder{ m_slaveShooterMotor.GetEncoder() };

  WPI_TalonFX m_leftHoodMotor{ ShooterConstants::kHoodLeftPort };
  WPI_TalonFX m_rightHoodMotor{ ShooterConstants::kHoodRightPort };

  frc::MotorControllerGroup m_hoodMotors{ m_leftHoodMotor, m_rightHoodMotor };

  double m_shooterVelocity = 4000;
  double m_maxShooterVelocity = 5600; //!: 5800 is the true max but we want make sure we dont go near that

  double m_hoodAngle = 0;
  double m_lowestHoodAngle = 90.0;

  double m_hoodMoveSpeed = 0.2;
};
