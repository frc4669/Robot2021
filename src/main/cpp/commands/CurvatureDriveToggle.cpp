// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CurvatureDriveToggle.h"

CurvatureDriveToggle::CurvatureDriveToggle(Drivetrain* drivetrain) {
  AddRequirements( {drivetrain} );
  this->drivetrain = drivetrain;
}

// Called when the command is initially scheduled.
void CurvatureDriveToggle::Initialize() {
  drivetrain->ToggleCurvatureTurnInPlace();
}

// Called repeatedly when this Command is scheduled to run
void CurvatureDriveToggle::Execute() {}

// Called once the command ends or is interrupted.
void CurvatureDriveToggle::End(bool interrupted) {}

// Returns true when the command should end.
bool CurvatureDriveToggle::IsFinished() {
  return true;
}
