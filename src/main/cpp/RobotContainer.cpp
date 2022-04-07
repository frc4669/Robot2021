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
#include <commands/IncrementShooterSetSpeed.h>
#include <commands/CurvatureDriveToggle.h>

#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <commands/MoveHood.h>

#include <commands/FollowAutoPath.h>


RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Setup F310 joystick bindings
/*   m_drivetrain.SetDefaultCommand(frc2::RunCommand(
    [this] 
      {  m_drivetrain.CurvatureDrive(i_f310.getLeftJoyY(), i_f310.getRightJoyX()*joyMultiplier); },
      {  &m_drivetrain  }
  )); */

  m_drivetrain.ResetEncoders();
}

void RobotContainer::ConfigureButtonBindings() {
  // Joystick buttons
  i_f310.leftJoyButton.WhenPressed( ShiftGear(&m_drivetrain) );             // Shift gear up/down //?: left joy button
  i_f310.rightJoyButton.WhenPressed( InverseMode(&m_drivetrain) );          // Inverse drive mode //?: right joy button

  // Top buttons
  i_f310.leftShoulderButton.WhenHeld( RunFeeder(&m_intake, true) );         // Reverse feeder //?: left shoulder
  i_f310.rightShoulderButton.WhenHeld( IntakeCargo(&m_intake) );            // Intake cargo   //?: right shoulder

  // Misc Buttons
  //i_f310.backButton.WhenPressed( AlignToTarget(&m_drivetrain, &m_vision) ); // Align to target  //?: back button
  i_f310.startButton.WhenPressed( CurvatureDriveToggle(&m_drivetrain) );    // Switch front     //?: start button

  // Colour buttons
  i_f310.orangeButton.WhenHeld( ManipulateIntakeArm(&m_intake) );           // deploy intake //?: orange button
  i_f310.greenButton.WhenHeld( RunShooter(&m_shooter) );                    // Run shooter   //?: green button

  i_f310.blueButton.WhenHeld( MoveHood(&m_shooter, 0.10) );
  i_f310.redButton.WhenHeld( MoveHood(&m_shooter, -0.10) );


  //i_attack3.topLeftButton.WhenHeld( SetHoodAngle(&m_shooter, true) );             // raise hood angle  //?: red button
  //i_attack3.bottomLeftButton.WhenHeld( SetHoodAngle(&m_shooter, false) );           // lower hood angle  //?: blue button

  // POV buttons
  i_attack3.topJoyButton.WhenHeld( ExtendArms(&m_climber, true) );           // Extend arms    //?: dpad up
  i_attack3.bottomJoyButton.WhenHeld( ExtendArms(&m_climber, false) );        // Retract arms   //?: dpad down

  i_attack3.leftJoyButton.WhenPressed( IncrementShooterSetSpeed(&m_shooter, 100) );  // Increase shooter speed //?: dpad right
  i_attack3.rightJoyButton.WhenPressed( IncrementShooterSetSpeed(&m_shooter, -100) );  // Decrease shooter speed //?: dpad left
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  /*return new frc2::SequentialCommandGroup { 
    frc2::ParallelCommandGroup {
      RunShooter(&m_shooter),             // start shooter
      IntakeCargo(&m_intake),             // run feeder
      DriveForward(&m_drivetrain, 75.0)   // drive forward
    },
  };*/
  return new frc2::SequentialCommandGroup {
    frc2::ParallelCommandGroup {
      FollowAutoPath(&m_drivetrain)
    }
  };
}