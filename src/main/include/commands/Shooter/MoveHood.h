// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Shooter.h>

class MoveHood : public frc2::CommandHelper<frc2::CommandBase, MoveHood> {
 public:
  /**
   * Move hood by a set motor speed.
   * 
   * @param shooter a Shooter object pointer
   * @param outputPercent motor output percent, 1.0 being 100% motor power
   */
  MoveHood(Shooter *shooter, double outputPercent);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Shooter* shooter;
  double outputPercent;
};
