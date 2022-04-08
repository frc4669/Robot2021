// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Pivot.h"

Pivot::Pivot(Climber* climber, bool pivotForward) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements( {climber} );
  this->climber = climber;
  this->pivotForward = pivotForward;
}

// Called when the command is initially scheduled.
void Pivot::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Pivot::Execute() {
  double ticksToFullExtend = 999999999999999;

  if(pivotForward)
    if(climber->GetRightTicks() < ticksToFullExtend && climber->GetLeftTicks() < ticksToFullExtend)
      climber->PivotBackwards();
    else  
      End(true);
  else
    climber->PivotForwards();
}

// Called once the command ends or is interrupted.
void Pivot::End(bool interrupted) {
  climber->StopPivot();
}

// Returns true when the command should end.
bool Pivot::IsFinished() {
  return false;
}
