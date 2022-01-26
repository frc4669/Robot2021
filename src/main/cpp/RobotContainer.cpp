// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>

#include <commands/DriveForward.h>

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Setup F310 drive bindings
  m_drivetrain.SetDefaultCommand(frc2::RunCommand(
    [this] 
      {  m_drivetrain.ArcadeDrive(-f310.getLeftY()*joyMultiplier, -f310.getRightX()*joyMultiplier); },
      {  &m_drivetrain  }
  ));

  m_drivetrain.ResetEncoders();
}

void RobotContainer::ConfigureButtonBindings() {
  f310.greenButtonObject.WhenPressed( DriveForward(&m_drivetrain, 1.0) );
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

double RobotContainer::PassThrough(bool left) {
  if(left) {
    return m_drivetrain.GetLeftEncoderDistance();
  } else {
    return m_drivetrain.GetRightEncoderDistance();
  }
}