// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PlayAwesomeSong.h"

PlayAwesomeSong::PlayAwesomeSong(Drivetrain* drivetrain) {
  AddRequirements( {drivetrain} );
  this->drivetrain = drivetrain;
}

// Called when the command is initially scheduled.
void PlayAwesomeSong::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PlayAwesomeSong::Execute() {
  drivetrain->PlayTheBestSong();
}

// Called once the command ends or is interrupted.
void PlayAwesomeSong::End(bool interrupted) {}

// Returns true when the command should end.
bool PlayAwesomeSong::IsFinished() {
  return false;
}
