// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autonomous/DriveForward.h"

#include <frc/smartdashboard/SmartDashboard.h> // for debugging

DriveForward::DriveForward(Drivetrain* drivetrain, double targetInchesDistance) {
  AddRequirements({ drivetrain });
  this->drivetrain = drivetrain;
  this->targetInchesDistance = targetInchesDistance;
}

// Called when the command is initially scheduled.
void DriveForward::Initialize() {
  drivetrain->ResetEncoders(); // Reset encoders so we don't finish early
  targetTicksDistance = drivetrain->GetTicksToTravel(targetInchesDistance);

  frc::SmartDashboard::PutNumber("Auto Drive Ticks", targetTicksDistance); // display ticks needed for the command call
  drivetrain->DriveForward(targetTicksDistance); // call motion magic with how many ticks we want to travel
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {}

// Called once the command ends or is interrupted.
void DriveForward::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveForward::IsFinished() {
  double leftVelocity = drivetrain->GetLeftVelocity();
  double rightVelocity = drivetrain->GetRightVelocity();

  // Check if we've stopped moving
  return ( abs(10-leftVelocity) < 10 ) && ( abs(10-rightVelocity) < 10 );
}
