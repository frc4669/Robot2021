// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TimedShooter.h"

TimedShooter::TimedShooter(units::second_t timeout, Shooter* shooter) : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->shooter = shooter;
}

// Called just before this Command runs the first time
void TimedShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TimedShooter::Execute() {
  shooter->RunShooter();
}

// Called once after command times out
void TimedShooter::End() {
  shooter->StopShooter();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedShooter::Interrupted() {}
