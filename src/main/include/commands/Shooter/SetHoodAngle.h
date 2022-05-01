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
   * Set the shooter hood to a set angle.
   * 
   * @param shooter a Shooter object pointer
   * @param toAngle angle to set shooter hood to
   */
  SetHoodAngle(Shooter* shooter, double toAngle);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Shooter* shooter;
  double toAngle;
};
