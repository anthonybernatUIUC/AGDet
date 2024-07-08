//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "detector.hh"

DetectorConstruction::DetectorConstruction() {
	fWorldSize = 1*m;
	isShielded = true;
	isHydrogen = false;
	halfShell = true;
	rThickness = 5;
	dDiameter = 8;
	zLength = 3;
	outerShieldDiameter = 8;

	DefineMaterials();
}

DetectorConstruction::~DetectorConstruction() {}

void DetectorConstruction::DefineMaterials() {
	
	man = G4NistManager::Instance();
	Galactic = man->FindOrBuildMaterial("G4_Galactic");
	Ge = man->FindOrBuildMaterial("G4_Ge");
	Si = man->FindOrBuildMaterial("G4_Si");
	BC = man->FindOrBuildMaterial("G4_BORON_CARBIDE");
}

/* void DetectorConstruction::ConstructAlShield(G4RotateY3D rotTheta, G4RotateZ3D rotPhi) {
	// Shell
	G4double distAl1 = zLength / 2;
	Sidel = distAl1 + 1;
	G4Translate3D shiftZAl1(0, 0, (distDet + distAl1)*cm);
	G4Transform3D transformAl1 = rotPhi * rotTheta * shiftZAl1;
	solidAl1 = new G4Tubs(
		"solidAl1", (dDiameter / 2 + 1)*cm, (dDiameter / 2 + 1.1)*cm, Sidel*cm, 0*deg, 360*deg);
	logicAl1 = new G4LogicalVolume(solidAl1, Al, "logicAl1");
	physAl1 = new G4PVPlacement(transformAl1, logicAl1, "physAl1", logicWorld, false, 0, false);

	// Caps
	Capl = .1;
	G4double distAl2_1 = (zLength / 2) + (Sidel + Capl / 2);
	G4double distAl2_2 = (zLength / 2) - (Sidel + Capl / 2);
	G4Translate3D shiftZAl2_1(0, 0, (distDet + distAl2_1)*cm);
	G4Transform3D transformAl2_1 = rotPhi * rotTheta * shiftZAl2_1;
	G4Translate3D shiftZAl2_2(0, 0, (distDet + distAl2_2)*cm);
	G4Transform3D transformAl2_2 = rotPhi * rotTheta * shiftZAl2_2;
	solidAl2 = new G4Tubs("solidAl1", 0, (dDiameter / 2 + 1.1)*cm, Capl*mm / 2, 0*deg, 360*deg);
	logicAl2 = new G4LogicalVolume(solidAl2, Al, "logicAl2");
	physAl2_1 = new G4PVPlacement(transformAl2_1, logicAl2,"physAl2_1", logicWorld, false, 0, false);
	physAl2_2 = new G4PVPlacement(transformAl2_2, logicAl2, "physAl2_2", logicWorld, false, 0, false);
}

void DetectorConstruction::ConstructIsoSphere(G4RotateY3D rotTheta, G4RotateZ3D rotPhi) {
	innerShellRadius = 18.52;
	ShellThickness = 1;
	ShellSweep = halfShell ? 90*deg : 180*deg;

	G4Translate3D shiftZIsoSphere(0, 0, (distDet + zLength / 2)*cm);
	G4Transform3D transformIsoSphere = rotPhi * rotTheta * shiftZIsoSphere;
	solidIsoSphere = new G4Sphere(
		"solidIsoSphere", innerShellRadius*cm, (innerShellRadius + ShellThickness)*cm, 
		0*deg, 360*deg, 0*deg, ShellSweep);
	logicIsoSphere = new G4LogicalVolume(solidIsoSphere, IsotopeShellMat,"logicIsoSphere");
	physIsoSphere = new G4PVPlacement(
		transformIsoSphere, logicIsoSphere, "physIsoSphere",logicWorld, false, 0, false);
}

void DetectorConstruction::ConstructShielding(G4RotateY3D rotTheta, G4RotateZ3D rotPhi) {
	// Shield 1 (Lead)
	Di1 = 1; // Inches
	Do1 = 5;
	zL1 = 2;
	DistOrigin1 = (zL1 / 2) + zLength / 2.54;
	G4Translate3D shiftZShield1(0, 0, (distDet + DistOrigin1 * 2.54)*cm);
	G4Transform3D transformShield1 = rotPhi * rotTheta * shiftZShield1;
	solidShield1 = new G4Tubs(
		"solidShield1", (Di1 * 2.54 / 2)*cm, (Do1 * 2.54 / 2)*cm, (zL1 * 2.54 / 2)*cm, 0*deg, 360*deg);
	logicShield1 = new G4LogicalVolume(solidShield1, Pb, "logicShield1");
	physShield1 = new G4PVPlacement(
		transformShield1, logicShield1, "physShield1", logicWorld, false, 0, false);

	// Shield 2 (Copper)
	Di2 = 4.125; // Inches
	Do2 = 4.25;
	zL2 = zLength / 2.54 + 0.5;
	DistOrigin2 = (zL2 / 2);
	G4Translate3D shiftZShield2(0, 0, (distDet + DistOrigin2 * 2.54)*cm);
	G4Transform3D transformShield2 = rotPhi * rotTheta * shiftZShield2;
	solidShield2 = new G4Tubs(
		"solidShield2", (Di2 * 2.54 / 2)*cm, (Do2 * 2.54 / 2)*cm, (zL2 * 2.54 / 2)*cm, 0*deg, 360*deg);
	logicShield2 = new G4LogicalVolume(solidShield2, Cu, "logicShield2");
	physShield2 = new G4PVPlacement(
		transformShield2, logicShield2, "physShield2", logicWorld, false, 0, false);

	//Shield 3 (Lead)
	Di3 = 5.125; 
	Do3 = outerShieldDiameter; // Inches
	zL3 = zL1 + zLength / 2.54; 
	DistOrigin3 = (zL3 / 2);
	G4Translate3D shiftZShield3(0, 0, (distDet + DistOrigin3 * 2.54)*cm);
	G4Transform3D transformShield3 = rotPhi * rotTheta * shiftZShield3;
	solidShield3 = new G4Tubs(
		"solidShield3", (Di3 * 2.54 / 2)*cm, (Do3 * 2.54 / 2)*cm, (zL3 * 2.54 / 2)*cm, 0*deg, 360*deg);
	logicShield3 = new G4LogicalVolume(solidShield3, Pb, "logicShield3");
	physShield3 = new G4PVPlacement(
		transformShield3, logicShield3, "physShield3", logicWorld, false, 0, false);
} */

void DetectorConstruction::ConstructTarget() {
	TarLength = 10*cm;
	TarWidth = 10*um;
	solidTarget = new G4Box("solidTarget", TarLength / 2, TarLength / 2, TarWidth / 2);
	logicTarget = new G4LogicalVolume(solidTarget, BC, "logicTarget");
	physTarget = new G4PVPlacement(
		0, G4ThreeVector(0, 0, 0), logicTarget, "physTarget", logicWorld, false, 0, false);
}

void DetectorConstruction::ConstructTarget(G4RotateY3D rotTheta, G4RotateZ3D rotPhi) {

	G4Transform3D transformTarget = rotPhi * rotTheta;
	TarLength = 10*cm;
	TarWidth = 10*um;
	solidTargetCyl = new G4Tubs("solidTargetCyl", 0, TarLength / 2, TarWidth / 2, 0*deg, 360*deg);
	logicTargetCyl = new G4LogicalVolume(solidTargetCyl, BC, "logicTargetCyl");
	physTargetCyl = new G4PVPlacement(
		transformTarget, logicTargetCyl, "physTargetCyl", logicWorld, false, 0, false);
}

void DetectorConstruction::ConstructSiDetector(G4RotateY3D rotTheta, G4RotateZ3D rotPhi) {

	G4Translate3D shiftZSiDet(0, 0, distDet*cm);
	G4Transform3D transformSiDet = rotPhi * rotTheta * shiftZSiDet;
	solidSiDet = new G4Tubs("solidSiDet", 0, 2.5*cm, 10*um, 0*deg, 360*deg);
	logicSiDet = new G4LogicalVolume(solidSiDet, Si, "logicSiDet");
	fSiScoringVolume = logicSiDet;
	physSiDet = new G4PVPlacement(
		transformSiDet, logicSiDet, "physSiDet", logicWorld, false, 0, false);
}

void DetectorConstruction::ConstructHPGeDetector(G4RotateY3D rotTheta, G4RotateZ3D rotPhi) {
	G4Translate3D shiftZGeDet(0, 0, (distDet + zLength / 2)*cm);
	G4Transform3D transformGeDet = rotPhi * rotTheta * shiftZGeDet;
	solidGeDet = new G4Tubs("solidGeDet", 0, (dDiameter / 2)*cm, (zLength / 2)*cm, 0*deg, 360*deg);
	logicGeDet = new G4LogicalVolume(solidGeDet, Ge, "logicGeDet");
	fGeScoringVolume = logicGeDet;
	physGeDet = new G4PVPlacement(transformGeDet, logicGeDet, "physGeDet", logicWorld, false, 0, false);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {

	distDet = 10;

	solidWorld = new G4Box("World", fWorldSize / 2, fWorldSize / 2, fWorldSize / 2);
	logicWorld = new G4LogicalVolume(solidWorld, Galactic, "World");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

	G4RotateY3D rotThetaSi(45*deg);
	G4RotateZ3D rotPhiSi(-45*deg);
	ConstructTarget(rotThetaSi, rotPhiSi);
	ConstructSiDetector(rotThetaSi, rotPhiSi);
	
	G4RotateY3D rotThetaHPGe1(90*deg);
	G4RotateZ3D rotPhiHPGe1(90*deg);
	G4RotateY3D rotThetaHPGe2(90*deg);
	G4RotateZ3D rotPhiHPGe2(-90*deg);
	ConstructHPGeDetector(rotThetaHPGe1, rotPhiHPGe1);
	ConstructHPGeDetector(rotThetaHPGe2, rotPhiHPGe2);

	return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
	
	MySiDet* sensDetSi = new MySiDet("SiSensitiveDetector");
	MyGeDet* sensDetGe = new MyGeDet("GeSensitiveDetector");
	if (logicSiDet) {
		G4cout << "ooplesnoops" << G4endl;
		logicSiDet->SetSensitiveDetector(sensDetSi);
	}
	if (logicGeDet) {
		G4cout << "hello vro" << G4endl;
		logicGeDet->SetSensitiveDetector(sensDetGe);
	}
}

