// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Vision.h"

Vision::Vision() {

}

// This method will be called once per scheduler run
void Vision::Periodic() {

}

photonlib::PhotonPipelineResult Vision::GetShooterCamData() {
	return m_shooterCamera.GetLatestResult();
}

photonlib::PhotonPipelineResult Vision::GetIntakeCamData() {
	return m_intakeCamera.GetLatestResult();
}

bool Vision::HasTargets(photonlib::PhotonPipelineResult* result) {
	return result->HasTargets();
}

photonlib::PhotonTrackedTarget Vision::GetBestTarget(photonlib::PhotonPipelineResult* result) {
	return result->GetBestTarget();
}