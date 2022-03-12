// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>

#include <commands/DriveForward.h>
#include <commands/ShiftGear.h>
#include <commands/RunShooter.h>
#include <commands/ExtendingArms.h>

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Setup F310 joystick bindings
  m_drivetrain.SetDefaultCommand(frc2::RunCommand(
    [this] 
      {  m_drivetrain.ArcadeDrive(f310.getLeftY()*joyMultiplier, -f310.getRightX()*joyMultiplier); },
      {  &m_drivetrain  }
  ));

  m_drivetrain.ResetEncoders();
}

void RobotContainer::ConfigureButtonBindings() {
  f310.greenButtonObject.WhenPressed( DriveForward(&m_drivetrain, 36.0) );  // Drive forward 36 inches when green button is pressed
  f310.orangeButtonObject.WhenPressed ( DriveForward(&m_drivetrain, 12.0)); // Drive forward 12 inches when orange button is pressed
  //f310.leftShoulderButtonObject.WhenPressed( ShiftGear(&m_drivetrain) );    // Shift when left shoulder is pressed

  //f310.rightShoulderButtonObject.WhenHeld( RunShooter(&m_shooter, -3500.0) );  // Run shooter at 1.0 when right shoulder is pressed

  f310.leftShoulderButtonObject.WhenHeld( ExtendingArms(&m_climber, true) ); //raise
  f310.rightShoulderButtonObject.WhenHeld( ExtendingArms(&m_climber, false) ); //lower
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}