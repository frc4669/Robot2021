// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <ctre/Phoenix.h>       //for intake/feeder belts
#include <frc/DoubleSolenoid.h> //for intake arm
#include <frc2/command/SubsystemBase.h>

#include <Constants.h>

class Intake : public frc2::SubsystemBase {
 public:
  Intake();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Manipulate the intake arm, extending or retracting,
   * works as a flip flop switch
   */
  void ManipulateArm();

  /**
   * Get the current state of the intake arm
   *
   * @return extended or retracted
   */
  bool IsArmExtended();

  /**
   * Run intake motor
   *
   * @param runReverse whether to reverse the intake
   */
  void RunIntake(bool runReverse = false);

  void StopIntake();

  /**
   * Run feeder motor
   *
   * @param runReverse whether to reverse the feeder
   */
  void RunFeeder(bool runReverse = false);

  void StopFeeder();

  double GetIntakeVelocity();

  double GetFeederVelocity();

  double GetFeederTicks();

  void ResetFeederTicks();

 private:
  // Motor controller for main intake
  WPI_TalonSRX m_intakeMotor{ IntakeConstants::kIntakeCAN };

  // Motor controller for vertical feeder
  WPI_TalonSRX m_feederMotor{ IntakeConstants::kFeederCAN };

  // Intake arm
  frc::DoubleSolenoid m_intakeArm{ frc::PneumaticsModuleType::CTREPCM, IntakeConstants::kArmFwdChannel, IntakeConstants::kArmRevChannel };
  bool kIntakeArmExtended = false; //start with intake arm retracted

  double kIntakeSpeedPercentage = 0.8;
  double kFeederSpeedPercentage = 0.5;
};
