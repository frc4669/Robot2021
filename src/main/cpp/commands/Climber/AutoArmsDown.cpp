// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Climber/AutoArmsDown.h"

AutoArmsDown::AutoArmsDown(Climber* climber) {
  AddRequirements( {climber} );
  this->climber = climber;
}

// Called when the command is initially scheduled.
void AutoArmsDown::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoArmsDown::Execute() {}

// Called once the command ends or is interrupted.
void AutoArmsDown::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmsDown::IsFinished() {
  return false;
}
