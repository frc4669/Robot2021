// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Shooter.h>


class SetHoodAngle : public frc2::CommandHelper<frc2::CommandBase, SetHoodAngle> {
 public:
  /**
   * Move the shooter hood to a given angle.
   * 
   * @param shooter a Shooter object pointer
   * @param raiseHood whether to raise or lower the hood
   */
  SetHoodAngle(Shooter* shooter, bool raiseHood);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Shooter* shooter;
  bool raiseHood;
};
