// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ManipulateIntakeArm.h"

ManipulateIntakeArm::ManipulateIntakeArm(Intake* intake) {
  AddRequirements( {intake} );
  this->intake = intake;
}

// Called when the command is initially scheduled.
void ManipulateIntakeArm::Initialize() {
  intake->ManipulateArm();
}

// Called repeatedly when this Command is scheduled to run
void ManipulateIntakeArm::Execute() {}

// Called once the command ends or is interrupted.
void ManipulateIntakeArm::End(bool interrupted) {}

// Returns true when the command should end.
bool ManipulateIntakeArm::IsFinished() {
  return true;  // finish instantly after Initialize() is called
}
