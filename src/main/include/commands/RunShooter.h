// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Shooter.h>


class RunShooter : public frc2::CommandHelper<frc2::CommandBase, RunShooter> {
 public:
  /**
   * Run the shooter motors at a given velocity.
   *
   * @param shooter a Shooter object pointer
   * @param targetVelocity the speed to run the shooter at
   */
  RunShooter(Shooter* shooter, double targetVelocity);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Shooter* shooter;
  double targetVelocity;
};
