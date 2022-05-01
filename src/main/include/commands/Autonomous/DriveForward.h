// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Drivetrain.h>

class DriveForward : public frc2::CommandHelper<frc2::CommandBase, DriveForward> {
 public:
  /**
   * Drives forward a set distance.
   *
   * @param drivetrain a Drivetrain object pointer
   * @param targetInchesDistance the distance to drive in inches
   */
  DriveForward(Drivetrain* drivetrain, double targetInchesDistance);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drivetrain* drivetrain;
  double targetInchesDistance;
  double targetTicksDistance;
};
