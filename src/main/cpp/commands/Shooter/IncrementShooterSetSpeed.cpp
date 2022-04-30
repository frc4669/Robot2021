// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Shooter/IncrementShooterSetSpeed.h"

IncrementShooterSetSpeed::IncrementShooterSetSpeed(Shooter* shooter, double increment) {
  AddRequirements( {shooter} );
  this->shooter = shooter;
  this->increment = increment;
}

// Called when the command is initially scheduled.
void IncrementShooterSetSpeed::Initialize() {
  shooter->IncrementShooterSetSpeed(increment);
}

// Called repeatedly when this Command is scheduled to run
void IncrementShooterSetSpeed::Execute() {}

// Called once the command ends or is interrupted.
void IncrementShooterSetSpeed::End(bool interrupted) {}

// Returns true when the command should end.
bool IncrementShooterSetSpeed::IsFinished() {
  return true;
}
