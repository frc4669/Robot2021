// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Intake/RunIntakeAndFeeder.h"

RunIntakeAndFeeder::RunIntakeAndFeeder(Intake* intake) {
  AddRequirements( {intake} );
  this->intake = intake;
}

// Called when the command is initially scheduled.
void RunIntakeAndFeeder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntakeAndFeeder::Execute() {
  intake->RunIntake();
  intake->RunFeeder();
}

// Called once the command ends or is interrupted.
void RunIntakeAndFeeder::End(bool interrupted) {
  intake->StopIntake();
  intake->StopFeeder();
}

// Returns true when the command should end.
bool RunIntakeAndFeeder::IsFinished() {
  return false;
}
