// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/controller/PIDController.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <subsystems/Drivetrain.h>
#include <subsystems/Vision.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AlignToHub : public frc2::CommandHelper<frc2::CommandBase, AlignToHub> {
 public:
  AlignToHub(Drivetrain* drivetrain, Vision* vision);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drivetrain* drivetrain;
  Vision* vision;
  photonlib::PhotonPipelineResult pipelineResult;
  photonlib::PhotonTrackedTarget trackedTarget;
  double targetYaw;
  frc2::PIDController PIDontroller{.1, 0, 0}; //low p
};
