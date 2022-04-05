// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunIntake.h"

RunIntake::RunIntake(Intake* intake, bool runReverse) {
  AddRequirements( {intake} );
  this->intake = intake;
  this->runReverse = runReverse;
}

// Called when the command is initially scheduled.
void RunIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntake::Execute() {
  intake->RunIntake(runReverse);
}

// Called once the command ends or is interrupted.
void RunIntake::End(bool interrupted) {
  intake->RunIntake(runReverse, true);
}

// Returns true when the command should end.
bool RunIntake::IsFinished() {
  return false;
}
