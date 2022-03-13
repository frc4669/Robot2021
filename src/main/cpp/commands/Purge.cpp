// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Purge.h"

Purge::Purge(Intake* intake, Shooter* shooter) {
  AddRequirements( {intake, shooter} );
  this->intake = intake;
  this->shooter = shooter;
}

// Called when the command is initially scheduled.
void Purge::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Purge::Execute() {}

// Called once the command ends or is interrupted.
void Purge::End(bool interrupted) {}

// Returns true when the command should end.
bool Purge::IsFinished() {
  return false;
}
