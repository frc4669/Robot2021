// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunShooter.h"

RunShooter::RunShooter(Shooter* shoot, double speed) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({ shoot });
  shooter = shoot;
  targetVelocity = speed;
}

// Called when the command is initially scheduled.
void RunShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
  // TODO: shooter->RunShooter(targetVelocity);
}

// Called once the command ends or is interrupted.
void RunShooter::End(bool interrupted) {
  // TODO: shooter->StopShooter();
}

// Returns true when the command should end.
bool RunShooter::IsFinished() {
  return false;
}
