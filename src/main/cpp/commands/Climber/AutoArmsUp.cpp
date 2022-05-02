// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Climber/AutoArmsUp.h"

AutoArmsUp::AutoArmsUp(Climber* climber) {
  AddRequirements( {climber} );
  this->climber = climber;
}

// Called when the command is initially scheduled.
void AutoArmsUp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoArmsUp::Execute() {}

// Called once the command ends or is interrupted.
void AutoArmsUp::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmsUp::IsFinished() {
  return false;
}
