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

#include <commands/IntakeCargo.h>
#include <commands/PrimeHoodToHub.h>
#include <commands/IncrementShooterSetSpeed.h>
#include <commands/CurvatureDriveToggle.h>

#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <commands/MoveHood.h>
#include <commands/Pivot.h>

#include <commands/SetHoodAngle.h>

#include <commands/FollowAutoPath.h>


RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Setup F310 joystick bindings
  m_drivetrain.SetDefaultCommand(frc2::RunCommand(
    [this] 
      {  m_drivetrain.CurvatureDrive(i_f310.getLeftJoyY(), i_f310.getRightJoyX()*joyMultiplier, true); },
      {  &m_drivetrain  }
  ));

  m_drivetrain.ResetEncoders();
}

void RobotContainer::ConfigureButtonBindings() {
  // Joystick buttons
  i_f310.leftJoyButton.WhenPressed( ShiftGear(&m_drivetrain) );             // Shift gear up/down //?: left joy button
  i_f310.rightJoyButton.WhenPressed( InverseMode(&m_drivetrain) );          // Inverse drive mode //?: right joy button

  // Top buttons
  i_f310.leftShoulderButton.WhenHeld( RunFeeder(&m_intake, true) );         // Reverse feeder //?: left shoulder
  i_f310.rightShoulderButton.WhenPressed( ManipulateIntakeArm(&m_intake) );            // Intake cargo   //?: right shoulder

  i_f310.greenButton.WhenPressed( CurvatureDriveToggle(&m_drivetrain) );    // Switch front     //?: start button

  // Colour buttons


  i_extreme3.triggerButton.WhenHeld( RunShooter(&m_shooter) );
  i_extreme3.sideTriggerButton.WhenHeld( RunFeeder(&m_intake, false) );
  i_extreme3.topLeftJoyButton.WhenHeld( RunFeeder(&m_intake, true) );

  i_extreme3.topRightJoyButton.WhenPressed( ManipulateIntakeArm(&m_intake) );

  i_extreme3.topLeftButton.WhenHeld( MoveHood(&m_shooter, 0.10) );
  i_extreme3.topRightButton.WhenHeld( MoveHood(&m_shooter, -0.10) );

  i_extreme3.middleLeftButton.WhenPressed( IncrementShooterSetSpeed(&m_shooter, -100) );
  i_extreme3.middleRightButton.WhenPressed( IncrementShooterSetSpeed(&m_shooter, 100) );

  i_extreme3.bottomLeftButton.WhenHeld( ExtendArms(&m_climber, true) );
  i_extreme3.bottomRightButton.WhenHeld( ExtendArms(&m_climber, false) );

  i_extreme3.bottomLeftJoyButton.WhenHeld( Pivot(&m_climber, true) );
  i_extreme3.bottomRightJoyButton.WhenHeld( Pivot(&m_climber, false) );
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
<<<<<<< HEAD

  return new frc2::SequentialCommandGroup {
      FollowAutoPath(&m_drivetrain)
=======
  return new frc2::SequentialCommandGroup { 
    DriveForward(&m_drivetrain, 75.0),   // drive forward

    frc2::ParallelCommandGroup  {
      RunShooter(&m_shooter),             // start shooter
      IntakeCargo(&m_intake)             // run feeder
    },   
>>>>>>> parent of 0e6877e... SVR end of day changes (WORKING)
  };
}