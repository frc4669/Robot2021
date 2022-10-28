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

  std::function<frc::Pose2d()> getPose = [this] () { return m_drivetrain.GetCurrentPose(); };
  std::function<frc::DifferentialDriveWheelSpeeds()> getWheelSpeeds = [this] () { return m_drivetrain.GetWheelSpeeds(); };
  std::function<void(units::volt_t, units::volt_t)> setVoltages = [this] (auto left, auto right) {
    m_drivetrain.SetLeftVoltage(left);
    m_drivetrain.SetRightVoltage(right);
  };

  frc2::RamseteCommand followPathplannerFile {
    m_drivetrain.GetAutoTrajectory(), //Gets the trajectory from pathplannnerlib
    getPose, //Allows the command to repeatedly retrieve the pose from the odometry
    m_drivetrain.GetRamseteController(),
    m_drivetrain.GetFeedforward(),
    m_drivetrain.GetKinematics(),
    getWheelSpeeds, //Allows the command to repeatedly get the speeds of the wheels
    frc2::PIDController(DriveConstants::kp, 0, 0), //PID controller (confirm kp is right)
    frc2::PIDController(DriveConstants::kp, 0, 0), //PID controller (confirm kp is right)
    setVoltages, //Sets voltage of motors based on command output
    { &m_drivetrain }
  };

  m_drivetrain.ResetOdometry(m_drivetrain.GetAutoInitialPose(), m_drivetrain.GetAutoInitialRotation());
  
  return new frc2::SequentialCommandGroup(
    std::move(followPathplannerFile)
  );
}