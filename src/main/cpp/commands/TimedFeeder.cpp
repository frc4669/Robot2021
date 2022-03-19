// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TimedFeeder.h"

TimedFeeder::TimedFeeder(units::second_t timeout, Intake* intake, bool runReverse) : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->intake = intake;
  this->runReverse = runReverse;
}

// Called just before this Command runs the first time
void TimedFeeder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TimedFeeder::Execute() {
  intake->RunFeeder(runReverse);
}

// Called once after command times out
void TimedFeeder::End() {
  intake->StopFeeder();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedFeeder::Interrupted() {}
