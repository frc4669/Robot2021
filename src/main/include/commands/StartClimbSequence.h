// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Climber.h>
#include <subsystems/Shooter.h>
#include <subsystems/Intake.h>


class StartClimbSequence : public frc2::CommandHelper<frc2::CommandBase, StartClimbSequence> {
 public:
  /**
   * Starts the automated climb sequence for a traversal climb.
   * 
   * @param climber a Climber object pointer
   * @param shooter a Shooter object pointer
   * @param intake an Intake object pointer
   */
  StartClimbSequence(Climber* climber, Shooter* shooter, Intake* intake);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Climber* climber;
  Shooter* shooter;
  Intake* intake;
};
