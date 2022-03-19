// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TimedIntake.h"

TimedIntake::TimedIntake(units::second_t timeout, Intake* intake) : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->intake = intake;
}

// Called just before this Command runs the first time
void TimedIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TimedIntake::Execute() {
  intake->RunIntake(false);
  intake->RunFeeder(false);
}

// Called once after command times out
void TimedIntake::End() {
  intake->StopIntake();
  intake->StopFeeder();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedIntake::Interrupted() {}
