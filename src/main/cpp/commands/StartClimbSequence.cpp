// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/StartClimbSequence.h"

StartClimbSequence::StartClimbSequence(Climber* climber, Shooter* shooter, Intake* intake) {
  AddRequirements( {climber, shooter, intake} );
  this->climber = climber;
  this->shooter = shooter;
  this->intake = intake;
}

// Called when the command is initially scheduled.
void StartClimbSequence::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void StartClimbSequence::Execute() {}

// Called once the command ends or is interrupted.
void StartClimbSequence::End(bool interrupted) {}

// Returns true when the command should end.
bool StartClimbSequence::IsFinished() {
  return false;
}
