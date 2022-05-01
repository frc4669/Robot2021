// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shooter/MoveHood.h"

MoveHood::MoveHood(Shooter* shooter, double outputPercent) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements( {shooter} );
  this->shooter = shooter;
  this->outputPercent = outputPercent;
}

// Called when the command is initially scheduled.
void MoveHood::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveHood::Execute() {
  shooter->MoveHood(outputPercent);
}

// Called once the command ends or is interrupted.
void MoveHood::End(bool interrupted) {
  shooter->MoveHood(0.0);
}

// Returns true when the command should end.
bool MoveHood::IsFinished() {
  return false;
}
