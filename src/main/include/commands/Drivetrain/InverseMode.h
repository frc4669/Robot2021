// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <subsystems/Drivetrain.h>

class InverseMode : public frc2::CommandHelper<frc2::CommandBase, InverseMode> {
 public:
  /**
   * Switches mode of robot, changing the relative "front" of the robot.
   * Making driving much easier as shooter and intake do not face the same way.
   *
   * @param drivetrain a Drivetrain object pointer
   */
  InverseMode(Drivetrain* drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drivetrain* drivetrain;
};
