// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/RunFeeder.h"

RunFeeder::RunFeeder(Intake* intake, bool runReverse) {
  AddRequirements( {intake} );
  this->intake = intake;
  this->runReverse = runReverse;
}

// Called when the command is initially scheduled.
void RunFeeder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunFeeder::Execute() {
  intake->RunFeeder(runReverse, false);
}

// Called once the command ends or is interrupted.
void RunFeeder::End(bool interrupted) {
  intake->RunFeeder(runReverse, true);
}

// Returns true when the command should end.
bool RunFeeder::IsFinished() {
  return false;
}
