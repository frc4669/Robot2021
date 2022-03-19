// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/commands/TimedCommand.h>
#include <units/time.h>

#include "subsystems/Intake.h"

class TimedFeeder : public frc::TimedCommand {
 public:
  explicit TimedFeeder(units::second_t timeout, Intake* intake, bool runReverse);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;

 private:
  Intake* intake;
  bool runReverse;
};
