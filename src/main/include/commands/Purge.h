// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Intake.h>
#include <subsystems/Shooter.h>


class Purge : public frc2::CommandHelper<frc2::CommandBase, Purge> {
 public:
  /**
   * Runs feeder and shooter to purge the robot of all cargo. 
   * Mainly to make sure that we purge cargo safely.
   * 
   * @param intake an Intake object pointer
   * @param shooter a Shooter object pointer
   */
  Purge(Intake* intake, Shooter* shooter);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  Intake* intake;
  Shooter* shooter;
};
