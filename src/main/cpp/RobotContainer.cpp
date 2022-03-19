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
  f310.leftJoyButtonObject.WhenPressed( ShiftGear(&m_drivetrain) );             // Shift gear up/down
  f310.rightJoyButtonObject.WhenPressed( InverseMode(&m_drivetrain) );          // Inverse drive mode

  // Top buttons
  f310.leftShoulderButtonObject.WhenHeld( RunFeeder(&m_intake, true) );         // Reverse feeder
  f310.rightShoulderButtonObject.WhenHeld( IntakeCargo(&m_intake) );            // Intake cargo (spin both intake and feeder)

  // Misc Buttons
  f310.backButtonObject.WhenPressed( AlignToTarget(&m_drivetrain, &m_vision) ); // Align to target
  f310.startButtonObject.WhenPressed( CurvatureDriveToggle(&m_drivetrain) );      // Switch if hood is in brake mode for idle state

  // Colour buttons
  f310.orangeButtonObject.WhenHeld( ManipulateIntakeArm(&m_intake) );           // Move intake arm down/up
  //f310.greenButtonObject.WhenHeld( );

  f310.redButtonObject.WhenHeld( SetHoodAngle(&m_shooter, true) );             // raise hood angle
  f310.blueButtonObject.WhenHeld( SetHoodAngle(&m_shooter, false) );             // lower hood angle

  // POV buttons
  f310.dpadUpButtonObject.WhenHeld( ExtendArms(&m_climber, true) );          // Extend arms
  f310.dpadDownButtonObject.WhenHeld( ExtendArms(&m_climber, false) );       // Retract arms

  f310.dpadRightButtonObject.WhenPressed( IncrementShooterSetSpeed(&m_shooter, 100) );  // Increase shooter speed
  f310.dpadLeftButtonObject.WhenPressed( IncrementShooterSetSpeed(&m_shooter, -100) );  // Decrease shooter speed
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return new frc2::SequentialCommandGroup{ 
    frc2::ParallelCommandGroup{
      DriveForward(&m_drivetrain, 60.0),
      IntakeCargo(&m_intake)
    },
    RunShooter(&m_shooter),
    DriveForward(&m_drivetrain, -60.0),
  };
}