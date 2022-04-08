// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <ctre/Phoenix.h>       // talon

#include <Constants.h>

class Climber : public frc2::SubsystemBase {
 public:
  Climber();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Sets both climber motors to unspool, raising the arms.
   */
  void RaiseExtendingArms();

  /**
   * Sets both climber motors to spool, lowering the arms.
   */
  void LowerExtendingArms();

  /**
   * Sets both climber motors to stop.
   */
  void StopExtendingArms();

  /**
   * Gets the current encoder position of the right climber motor.
   * 
   * @return encoder position of the right climber motor 
   */
  double GetRightPostion();

  /**
   * Gets the current encoder position of the left climber motor.
   * 
   * @return encoder position of the left climber motor 
   */
  double GetLeftPosition();

  /**
   * Lowers both arms to their starting positions making sure they're in sync.
   */
  void ZeroArms();

  /**
   * Check if the right climber is hitting its limit switch. 
   * If true, you cannot lower the arm any more.
   * 
   * @return true if the right climber is at its limit switch, false otherwise.
   */
  bool IsRightLimitHit();

  /**
   * Check if the left climber is hitting its limit switch. 
   * If true, you cannot lower the arm any more.
   * 
   * @return true if the left climber is at its limit switch, false otherwise.
   */
  bool IsLeftLimitHit();

  /**
   * Check if the climbing arms have been zeroed and are in sync.
   * 
   * @return true if the arms are in have been zeroed (synced), false otherwise.
   */
  bool AreArmsZeroed();

  void PivotBackwards();

  void PivotForwards();

  void StopPivot();

  double GetRightTicks();

  double GetLeftTicks();

 private:
  WPI_TalonFX m_staticRight{ ClimbConstants::kStaticRightCAN };  // Leading motor, right side
  WPI_TalonFX m_staticLeft{ ClimbConstants::kStaticLeftCAN };    // Following Motor, left side
  frc::MotorControllerGroup m_staticArms{ m_staticRight, m_staticLeft };

  WPI_TalonFX m_pivotRight{ ClimbConstants::kPivotRightCAN };   // Leading motor, right side
  WPI_TalonFX m_pivotLeft{ ClimbConstants::kPivotLeftCAN };     // Following motor, left side
  frc::MotorControllerGroup m_pivotArms{ m_pivotRight, m_pivotLeft };

  bool kArmsZeroed = false;  // Whether the arms have been zeroed and are in sync

  /**
   * Configure motor to desired settings
   *
   * @param motor Motor to configure
   * @param invert Whether to invert the motor
   */
  void ConfigureMotor(WPI_TalonFX &motor, bool inverted);
};
