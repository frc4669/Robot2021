// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <controllers/Extreme3DJoystick.h>
#include <controllers/GamepadF310.h>

#include <subsystems/Climber.h>
#include <subsystems/Drivetrain.h>
#include <subsystems/Intake.h>
#include <subsystems/Shooter.h>
#include <subsystems/Vision.h>

#include <frc2/command/Command.h>

#include "Constants.h"
#include "commands/ExampleCommand.h"
#include "subsystems/ExampleSubsystem.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // Miscellaneous
  double joyMultiplier = 0.50; // Joystick is too sensitive, multiply the output of the joystick by this value

  // The robot's subsystems and commands are defined here...
  ExampleSubsystem m_subsystem;
  ExampleCommand m_autonomousCommand;

  void ConfigureButtonBindings();

  // Subsystems
  Drivetrain m_drivetrain;
  Shooter m_shooter;
  Intake m_intake;
  Climber m_climber;
  Vision m_vision;

  // Controllers (takes USB port order as seen on FRC Driver Station and optionally axis deadzones)
  GamepadF310 i_f310{ 0 };
  Extreme3DJoystick i_extreme3{ 1 };
};
