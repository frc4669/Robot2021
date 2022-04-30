// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autonomous/AlignToHub.h"

AlignToHub::AlignToHub(Drivetrain* drivetrain, Vision* vision) {
  AddRequirements( {drivetrain, vision} );
  this->drivetrain = drivetrain;
  this->vision = vision;
}

// Called when the command is initially scheduled.
void AlignToHub::Initialize() {
  if(!vision->ShooterHasTarget())
    End(true);
}

// Called repeatedly when this Command is scheduled to run
void AlignToHub::Execute() {
  pipelineResult = vision->GetShooterCamData();
  trackedTarget = pipelineResult.GetBestTarget();
  targetYaw = trackedTarget.GetYaw();

  drivetrain->ChangeControllerAccess(false);
  bool IsForwardTowardIntake = drivetrain->IsForwardTowardIntake();
  drivetrain->CurvatureDrive(0, PIDontroller.Calculate(targetYaw, 0));
}

// Called once the command ends or is interrupted.
void AlignToHub::End(bool interrupted) {
  drivetrain->CurvatureDrive(0, 0);
  drivetrain->ChangeControllerAccess(true);
}

// Returns true when the command should end.
bool AlignToHub::IsFinished() {
  // ends if target is not in sight or is within 0.5 yaw
  return targetYaw <= 0.5 || !vision->ShooterHasTarget();
}
