// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/DoubleSolenoid.h> //for intake arm
#include <ctre/Phoenix.h>       //for intake/feeder belts

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
   * @param stopIntake whether to stop the intake (defaults to false)
   */
  void RunIntake(bool runReverse, bool stopIntake = false);

  /**
   * Run feeder motor
   * 
   * @param runReverse whether to reverse the feeder
   * @param stopFeeder whether to stop the feeder (defaults to false)
   */
  void RunFeeder(bool runReverse, bool stopFeeder = false);

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
};
