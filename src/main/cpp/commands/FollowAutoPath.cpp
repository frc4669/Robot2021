// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/FollowAutoPath.h"
#include <Constants.h>

FollowAutoPath::FollowAutoPath(Drivetrain* drivetrain) {
  AddRequirements( {drivetrain} );

  std::function<frc::Pose2d()> getPose = [this] () { return this->drivetrain->GetCurrentPose(); };
  std::function<frc::DifferentialDriveWheelSpeeds()> getWheelSpeeds = [this] () { return this->drivetrain->GetWheelSpeeds(); };
  std::function<void(units::volt_t, units::volt_t)> setVoltages = [this] (auto left, auto right) {
      this->drivetrain->SetLeftVoltage(left);
      this->drivetrain->SetRightVoltage(right);
  };

  this->drivetrain = drivetrain;

  drivetrain->ResetOdometry(drivetrain->GetAutoInitialPose(), drivetrain->GetAutoInitialRotation());

  this->command = new frc2::RamseteCommand(
      drivetrain->GetAutoTrajectory(), //Gets the trajectory from pathplannnerlib
      getPose, //Allows the command to repeatedly retrieve the pose from the odometry
      drivetrain->GetRamseteController(),
      drivetrain->GetFeedforward(),
      drivetrain->GetKinematics(),
      getWheelSpeeds, //Allows the command to repeatedly get the speeds of the wheels
      frc2::PIDController(DriveConstants::kp, 0, 0), //PID controller (confirm kp is right)
      frc2::PIDController(DriveConstants::kp, 0, 0), //PID controller (confirm kp is right)
      setVoltages, //Sets voltage of motors based on command output
      // wpi::span<Drivetrain>{ &drivetrain }
      {drivetrain}
  );
}

// Called when the command is initially scheduled.
void FollowAutoPath::Initialize() {
    return command->Initialize();
}

// Called repeatedly when this Command is scheduled to run
void FollowAutoPath::Execute() {
    return command->Execute();
}

// Called once the command ends or is interrupted.
void FollowAutoPath::End(bool interrupted) {
    return command->End(interrupted);
}

// Returns true when the command should end.
bool FollowAutoPath::IsFinished() {
  return command->IsFinished();
}
