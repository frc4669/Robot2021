// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SwitchHoodNeutralMode.h"

SwitchHoodNeutralMode::SwitchHoodNeutralMode(Shooter* shooter) {
  AddRequirements( {shooter} );
  this->shooter = shooter;
}

// Called when the command is initially scheduled.
void SwitchHoodNeutralMode::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SwitchHoodNeutralMode::Execute() {
  shooter->SwitchHoodNeutralMode();
}

// Called once the command ends or is interrupted.
void SwitchHoodNeutralMode::End(bool interrupted) {}

// Returns true when the command should end.
bool SwitchHoodNeutralMode::IsFinished() {
  return true;
}
