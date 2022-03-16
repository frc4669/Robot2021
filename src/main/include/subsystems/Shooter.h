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
   * Run the shooter at a given speed
   *
   * @param velocity the speed to run the shooter at
   */
  void RunShooter(double velocity);

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

  void MoveHoodForward();

  void MoveHoodBackwawrd();

  void StopHood();

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
};
