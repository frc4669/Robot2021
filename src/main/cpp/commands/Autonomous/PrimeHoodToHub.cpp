// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autonomous/PrimeHoodToHub.h"

PrimeHoodToHub::PrimeHoodToHub(Shooter* shooter, Vision* vision) {
  AddRequirements( {shooter, vision} );
  this->shooter = shooter;
  this->vision = vision;
}

// Called when the command is initially scheduled.
void PrimeHoodToHub::Initialize() {
  if(!vision->ShooterHasTarget())
    End(true); 
}

// Called repeatedly when this Command is scheduled to run
void PrimeHoodToHub::Execute() {
  pipelineResult = vision->GetShooterCamData();
  trackedTarget = pipelineResult.GetBestTarget();

  double distanceToHub = vision->GetHubTargetDistance(&trackedTarget);
  //TODO: Finish command
}

// Called once the command ends or is interrupted.
void PrimeHoodToHub::End(bool interrupted) {
  
}

// Returns true when the command should end.
bool PrimeHoodToHub::IsFinished() {
  return !vision->ShooterHasTarget();
}
