// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shooter/SetHoodAngle.h"

SetHoodAngle::SetHoodAngle(Shooter* shooter, double toAngle) {
  AddRequirements({ shooter });
  this->shooter = shooter;
  this->toAngle = toAngle;
}

// Called when the command is initially scheduled.
void SetHoodAngle::Initialize() {
  shooter->SetHoodAngle(toAngle);
}

// Called repeatedly when this Command is scheduled to run
void SetHoodAngle::Execute() {}

// Called once the command ends or is interrupted.
void SetHoodAngle::End(bool interrupted) {}

// Returns true when the command should end.
bool SetHoodAngle::IsFinished() {
  return true;
}
