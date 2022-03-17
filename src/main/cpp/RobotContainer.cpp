// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>

#include <commands/DriveForward.h>
#include <commands/ShiftGear.h>
#include <commands/RunShooter.h>
#include <commands/ExtendArms.h>
#include <commands/InverseMode.h>
#include <commands/ManipulateIntakeArm.h>
#include <commands/RunFeeder.h>
#include <commands/RunIntake.h>
#include <commands/SetHoodAngle.h>

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Setup F310 joystick bindings
  m_drivetrain.SetDefaultCommand(frc2::RunCommand(
    [this] 
      {  m_drivetrain.CurvatureDrive(f310.getLeftY()*joyMultiplier, -f310.getRightX()*joyMultiplier); },
      {  &m_drivetrain  }
  ));

  m_drivetrain.ResetEncoders();
}

void RobotContainer::ConfigureButtonBindings() {
  //f310.greenButtonObject.WhenPressed( DriveForward(&m_drivetrain, 36.0) );  // Drive forward 36 inches when green button is pressed
  //f310.blueButtonObject.WhenPressed( DriveForward(&m_drivetrain, 5.607) );
  //f310.redButtonObject.WhenPressed( DriveForward(&m_drivetrain, 56.07) );
  //f310.orangeButtonObject.WhenPressed( DriveForward(&m_drivetrain, .5607)); // Drive forward 12 inches when orange button is pressed
  //f310.orangeButtonObject.WhenPressed( ShiftGear(&m_drivetrain) );    // Shift when left shoulder is pressed
  //f310.greenButtonObject.WhenPressed( ManipulateIntakeArm(&m_intake) );
  f310.rightShoulderButtonObject.WhenHeld( RunIntake(&m_intake, false) );
  //f310.greenButtonObject.WhenHeld( RunFeeder(&m_intake, true) );
  //f310.orangeButtonObject.WhenHeld( RunFeeder(&m_intake, false) );



  f310.greenButtonObject.WhenHeld( SetHoodAngle(&m_shooter, true) ); // raise hood angle
  f310.orangeButtonObject.WhenHeld( SetHoodAngle(&m_shooter, false) ); // lower hood angle

  f310.blueButtonObject.WhenHeld( ExtendArms(&m_climber, true) ); //raise
  f310.redButtonObject.WhenHeld( ExtendArms(&m_climber, false) ); //lower

  //f310.leftShoulderButtonObject.WhenPressed( InverseMode(&m_drivetrain) );

  f310.leftShoulderButtonObject.WhenHeld( RunShooter(&m_shooter) );
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}