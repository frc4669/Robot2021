// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DeployIntakeArm.h"

DeployIntakeArm::DeployIntakeArm(Intake* intake) {
  AddRequirements( {intake} );
  this->intake = intake;
}

// Called when the command is initially scheduled.
void DeployIntakeArm::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DeployIntakeArm::Execute() {}

// Called once the command ends or is interrupted.
void DeployIntakeArm::End(bool interrupted) {}

// Returns true when the command should end.
bool DeployIntakeArm::IsFinished() {
  return false;
}
