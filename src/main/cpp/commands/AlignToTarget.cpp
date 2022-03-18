// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AlignToTarget.h"

AlignToTarget::AlignToTarget(Drivetrain* drivetrain, Vision* vision) {
  AddRequirements( {drivetrain, vision} );
  this->drivetrain = drivetrain;
  this->vision = vision;
}

// Called when the command is initially scheduled.
void AlignToTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AlignToTarget::Execute() {}

// Called once the command ends or is interrupted.
void AlignToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool AlignToTarget::IsFinished() {
  return false;
}
