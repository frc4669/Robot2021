// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunFeeder.h"

RunFeeder::RunFeeder(Intake* intake) {
  AddRequirements( {intake} );
  this->intake = intake;  
}

// Called when the command is initially scheduled.
void RunFeeder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunFeeder::Execute() {}

// Called once the command ends or is interrupted.
void RunFeeder::End(bool interrupted) {}

// Returns true when the command should end.
bool RunFeeder::IsFinished() {
  return false;
}
