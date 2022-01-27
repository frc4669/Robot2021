// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveForward.h"

DriveForward::DriveForward(Drivetrain* drive, double inches) {
  AddRequirements({ drive });
  drivetrain = drive;
  targetDistance = inches;
}

// Called when the command is initially scheduled.
void DriveForward::Initialize() {
  drivetrain->ResetEncoders(); // Reset encoders so we don't finish early
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {
  drivetrain->DriveForward(targetDistance, 40000);
}

// Called once the command ends or is interrupted.
void DriveForward::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveForward::IsFinished() {
  double expectedTicksTraveled = drivetrain->GetTicksToTravel(targetDistance); // Calculate how many ticks we need to travel

  // check if we've traveled the expected distance
  return drivetrain->GetLeftEncoderDistance() >= expectedTicksTraveled || drivetrain->GetRightEncoderDistance() >= expectedTicksTraveled;
}
