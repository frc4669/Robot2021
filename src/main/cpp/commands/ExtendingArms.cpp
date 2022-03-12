// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ExtendingArms.h"

ExtendingArms::ExtendingArms(Climber* climb, bool isRaising) {
  AddRequirements({ climb });
  climber = climb;
  raising = isRaising;
}

// Called when the command is initially scheduled.
void ExtendingArms::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ExtendingArms::Execute() {
  if(raising) {
    climber->RaiseExtendingArms();
  } else {
    climber->LowerExtendingArms();
  }
}

// Called once the command ends or is interrupted.
void ExtendingArms::End(bool interrupted) {
  climber->StopExtendingArms();
}

// Returns true when the command should end.
bool ExtendingArms::IsFinished() {
  return true;
}
