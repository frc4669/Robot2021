// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

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
   * Get the current velocity of the shooter
   *
   * @return the current velocity of the shooter
   */
  double GetShooterVelocity();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Our shooter motors
  rev::CANSparkMax masterShooterMotor{ShooterConstants::kShooterMasterPort, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax slaveShooterMotor{ShooterConstants::kShooterSlavePort, rev::CANSparkMax::MotorType::kBrushless};

  // PID controllers so we dont kill motors
  rev::SparkMaxPIDController masterPIDController{masterShooterMotor.GetPIDController()};
  rev::SparkMaxPIDController slavePIDController{slaveShooterMotor.GetPIDController()};
};
