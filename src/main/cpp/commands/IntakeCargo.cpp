// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeCargo.h"

IntakeCargo::IntakeCargo(Intake* intake) {
  AddRequirements( {intake} );
  this->intake = intake;
}

// Called when the command is initially scheduled.
void IntakeCargo::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeCargo::Execute() {
  intake->RunIntake(false);
  intake->RunFeeder(false);
}

// Called once the command ends or is interrupted.
void IntakeCargo::End(bool interrupted) {
  intake->RunIntake(false, true);
  intake->RunIntake(false, true);
}

// Returns true when the command should end.
bool IntakeCargo::IsFinished() {
  return false;
}
