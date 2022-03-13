// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Drivetrain.h>


class AlignToTarget : public frc2::CommandHelper<frc2::CommandBase, AlignToTarget> {
 public:
  /**
   * Align to the hub if seen by targetting system.
   * 
   * @param drivetrain a Drivetrain object pointer
   */
  AlignToTarget(Drivetrain* drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drivetrain* drivetrain;
};
