// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/Climber.h>


class ExtendArms : public frc2::CommandHelper<frc2::CommandBase, ExtendArms> {
 public:
  /**
   * Raise/lower the telescopic arms.
   * 
   * @param climber a Climber object pointer
   * @param isRaising whether to raise or lower arms
   */
  ExtendArms(Climber* climber, bool isRaising, bool isRight, bool isLeft);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Climber* climber;
  bool isRaising;
  bool isRight;
  bool isLeft;
};
