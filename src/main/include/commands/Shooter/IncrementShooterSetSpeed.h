// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Shooter.h>

class IncrementShooterSetSpeed : public frc2::CommandHelper<frc2::CommandBase, IncrementShooterSetSpeed> {
 public:
  /**
   * Change shooter motor speed by a set increment.
   * 
   * @param shooter a Shooter object pointer
   * @param increment what to increment the set motor speed by
   */
  IncrementShooterSetSpeed(Shooter* shooter, double increment);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Shooter* shooter;
  double increment;
};
