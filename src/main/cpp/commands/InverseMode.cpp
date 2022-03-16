// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/InverseMode.h"

InverseMode::InverseMode(Drivetrain* drivetrain) {
  AddRequirements( {drivetrain} );
  this->drivetrain = drivetrain;
}

// Called when the command is initially scheduled.
void InverseMode::Initialize() {
  drivetrain->ReverseRelativeFront();
}

// Called repeatedly when this Command is scheduled to run
void InverseMode::Execute() {}

// Called once the command ends or is interrupted.
void InverseMode::End(bool interrupted) {}

// Returns true when the command should end.
bool InverseMode::IsFinished() {
  return true;
}
