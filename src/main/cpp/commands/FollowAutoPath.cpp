// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/FollowAutoPath.h"
#include <Constants.h>

FollowAutoPath::FollowAutoPath(Drivetrain* drivetrain) {
  AddRequirements( {climber} );
  this->drivetrain = drivetrain;
  this->command = new frc2::RamseteCommand(
      drivetrain.GetAutoTrajectory(),
      [this] () { return drivetrain.GetCurrentPose(); },
      drivetrain.GetRamseteController(),
      drivetrain.GetFeedforward(),
      drivetrain.GetKinematics(),
      [this] () { return drivetrain.GetWheelSpeeds() },
      frc2::PIDController(DriveConstants::kp, 0, 0),
      frc2::PIDController(DriveConstants::kp, 0, 0),
      [this] (auto left, auto right) {
          drivetrain.SetLeftVoltage(left);
          drivetrain.SetRightVoltage(right);
      },
      { &drivetrain }
  );
}

// Called when the command is initially scheduled.
void FollowAutoPath::Initialize() {
    return command.Initialize();
}

// Called repeatedly when this Command is scheduled to run
void FollowAutoPath::Execute() {
    return command.Execute();
}

// Called once the command ends or is interrupted.
void FollowAutoPath::End(bool interrupted) {
    return command.End(interrupted);
}

// Returns true when the command should end.
bool FollowAutoPath::IsFinished() {
  return command.IsFinished();
}
