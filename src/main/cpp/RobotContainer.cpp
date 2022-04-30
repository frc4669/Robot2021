// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>

#include <commands/Autonomous/DriveForward.h>
#include <commands/Drivetrain/ShiftGear.h>
#include <commands/Shooter/RunShooter.h>
#include <commands/Climber/ExtendArms.h>
#include <commands/Drivetrain/InverseMode.h>
#include <commands/Intake/ManipulateIntakeArm.h>
#include <commands/Intake/RunFeeder.h>

#include <commands/Intake/IntakeCargo.h>
#include <commands/Autonomous/PrimeHoodToHub.h>
#include <commands/Shooter/IncrementShooterSetSpeed.h>
#include <commands/Drivetrain/CurvatureDriveToggle.h>

#include <frc2/command/ParallelCommandGroup.h>
#include <commands/Shooter/MoveHood.h>



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
  i_f310.leftShoulderButton.WhenHeld( IntakeCargo(&m_intake) );         // Reverse feeder //?: left shoulder
  i_f310.rightShoulderButton.WhenPressed( ManipulateIntakeArm(&m_intake) );            // Intake cargo   //?: right shoulder

  i_f310.greenButton.WhenPressed( CurvatureDriveToggle(&m_drivetrain) );    // Switch front     //?: start button

  // Colour buttons


  i_extreme3.triggerButton.WhenHeld( RunShooter(&m_shooter) );
  i_extreme3.sideTriggerButton.WhenHeld( RunFeeder(&m_intake, false) );
  i_extreme3.topLeftJoyButton.WhenHeld( RunFeeder(&m_intake, true) );

  i_extreme3.topRightJoyButton.WhenPressed( ManipulateIntakeArm(&m_intake) );

  i_extreme3.topLeftButton.WhenHeld( MoveHood(&m_shooter, 0.20) );
  i_extreme3.topRightButton.WhenHeld( MoveHood(&m_shooter, -0.20) );

  i_extreme3.middleLeftButton.WhenPressed( IncrementShooterSetSpeed(&m_shooter, -100) );
  i_extreme3.middleRightButton.WhenPressed( IncrementShooterSetSpeed(&m_shooter, 100) );

  i_extreme3.bottomLeftButton.WhenHeld( ExtendArms(&m_climber, true, false, false) );
  i_extreme3.bottomRightButton.WhenHeld( ExtendArms(&m_climber, false, true, true) );

  i_extreme3.bottomLeftJoyButton.WhenHeld( ExtendArms(&m_climber, false, false, true) );
  i_extreme3.bottomRightJoyButton.WhenHeld( ExtendArms(&m_climber, true, true, false ) );
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return new frc2::ParallelCommandGroup  {
    RunShooter(&m_shooter),             // start shooter
    IntakeCargo(&m_intake),             // run feeder
    DriveForward(&m_drivetrain, 75.0)   // drive forward
  };
}