// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/commands/TimedCommand.h>
#include <units/time.h>

#include "subsystems/Intake.h"

class TimedIntake : public frc::TimedCommand {
 public:
  explicit TimedIntake(units::second_t timeout, Intake* intake);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  Intake* intake;
};
