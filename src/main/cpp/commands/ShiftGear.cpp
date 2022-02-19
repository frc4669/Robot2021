// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShiftGear.h"

ShiftGear::ShiftGear(Drivetrain *drive) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({ drive });
  drivetrain = drive;
}

// Called when the command is initially scheduled.
void ShiftGear::Initialize() {
  drivetrain->ShiftGear();
}

// Called repeatedly when this Command is scheduled to run
void ShiftGear::Execute() {}

// Called once the command ends or is interrupted.
void ShiftGear::End(bool interrupted) {}

// Returns true when the command should end.
bool ShiftGear::IsFinished() {
  return true;  // finish instantly after Initialize() is called
}
