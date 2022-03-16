// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetHoodAngle.h"

SetHoodAngle::SetHoodAngle(Shooter* shooter, bool raiseHood) {
  AddRequirements( {shooter} );
  this->shooter = shooter;
  this->raiseHood = raiseHood;
}

// Called when the command is initially scheduled.
void SetHoodAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetHoodAngle::Execute() {
  if(raiseHood)
    shooter->MoveHoodForward();
  else
    shooter->MoveHoodBackwawrd();
}

// Called once the command ends or is interrupted.

void SetHoodAngle::End(bool interrupted) {
  shooter->StopHood();
}

// Returns true when the command should end.
bool SetHoodAngle::IsFinished() {
  return false;
}
