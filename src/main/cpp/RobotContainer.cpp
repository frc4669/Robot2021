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
#include <commands/SetHoodAngle.h>

#include <commands/IntakeCargo.h>
#include <commands/AlignToTarget.h>
#include <commands/SwitchHoodNeutralMode.h>
#include <commands/IncrementShooterSetSpeed.h>
#include <commands/CurvatureDriveToggle.h>

#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/ParallelDeadlineGroup.h>
#include <frc2/command/ParallelRaceGroup.h>

#include <units/time.h>
#include <commands/TimedFeeder.h>
#include <commands/TimedIntake.h>
#include <commands/TimedShooter.h>


RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Setup F310 joystick bindings
  m_drivetrain.SetDefaultCommand(frc2::RunCommand(
    [this] 
      {  m_drivetrain.CurvatureDrive(f310.getLeftY(), f310.getRightX()*joyMultiplier); },
      {  &m_drivetrain  }
  ));

  m_drivetrain.ResetEncoders();
}

void RobotContainer::ConfigureButtonBindings() {
  // Joystick buttons
  f310.leftJoyButtonObject.WhenPressed( ShiftGear(&m_drivetrain) );             // Shift gear up/down //?: left joy button
  f310.rightJoyButtonObject.WhenPressed( InverseMode(&m_drivetrain) );          // Inverse drive mode //?: right joy button

  // Top buttons
  f310.leftShoulderButtonObject.WhenHeld( RunFeeder(&m_intake, true) );         // Reverse feeder //?: left shoulder
  f310.rightShoulderButtonObject.WhenHeld( IntakeCargo(&m_intake) );            // Intake cargo   //?: right shoulder

  // Misc Buttons
  f310.backButtonObject.WhenPressed( AlignToTarget(&m_drivetrain, &m_vision) ); // Align to target  //?: back button
  f310.startButtonObject.WhenPressed( CurvatureDriveToggle(&m_drivetrain) );    // Switch front     //?: start button

  // Colour buttons
  f310.orangeButtonObject.WhenHeld( ManipulateIntakeArm(&m_intake) );           // deploy intake //?: orange button
  f310.greenButtonObject.WhenHeld( RunShooter(&m_shooter) );                    // Run shooter   //?: green button

  f310.redButtonObject.WhenHeld( SetHoodAngle(&m_shooter, true) );             // raise hood angle  //?: red button
  f310.blueButtonObject.WhenHeld( SetHoodAngle(&m_shooter, false) );           // lower hood angle  //?: blue button

  // POV buttons
  f310.dpadUpButtonObject.WhenHeld( ExtendArms(&m_climber, true) );           // Extend arms    //?: dpad up
  f310.dpadDownButtonObject.WhenHeld( ExtendArms(&m_climber, false) );        // Retract arms   //?: dpad down

  f310.dpadRightButtonObject.WhenPressed( IncrementShooterSetSpeed(&m_shooter, 100) );  // Increase shooter speed //?: dpad right
  f310.dpadLeftButtonObject.WhenPressed( IncrementShooterSetSpeed(&m_shooter, -100) );  // Decrease shooter speed //?: dpad left
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return new frc2::SequentialCommandGroup { 
    frc2::ParallelRaceGroup  {
      DriveForward(&m_drivetrain, 60.0),  // Drive forward to ball
      IntakeCargo(&m_intake)              // While intaking, as soon as we reach ball, we'll stop intake
    },
    DriveForward(&m_drivetrain, -60.0),   // Drive back to the wall
    RunShooter(&m_shooter)                
  };
}