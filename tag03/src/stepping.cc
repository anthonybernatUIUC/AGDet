// #include "stepping.hh"
// #include "G4RunManager.hh"
// #include "G4Gamma.hh"

// MySteppingAction::MySteppingAction(EventAction *eventAction) {
// 	fEventAction = eventAction;
// }

// MySteppingAction::~MySteppingAction() {}

// void MySteppingAction::UserSteppingAction(const G4Step *step)
// {
// 	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

// 	G4ParticleDefinition *part = step->GetTrack()->GetDefinition();

// 	const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*>(
// 		G4RunManager::GetRunManager()->GetUserDetectorConstruction());

// 	G4LogicalVolume *fGeScoringVolume = detectorConstruction->GetGeScoringVolume();
// 	G4LogicalVolume *fSiScoringVolume = detectorConstruction->GetSiScoringVolume();

// 	// G4cout << "Volume: " << volume << G4endl;

// 	//Add deposited energy at each step within the detector
// 	if (volume == fGeScoringVolume && part == G4Gamma::Gamma()) {
// 		G4double edep = step->GetTotalEnergyDeposit();
// 		fEventAction->AddEdepGe(edep);
// 		// G4cout << "Gamma edep: " << edep << G4endl;
// 	}
// }


#include "stepping.hh"
#include "G4RunManager.hh"
#include "G4Gamma.hh"
#include "G4ParticleTypes.hh"

MySteppingAction::MySteppingAction(EventAction *eventAction) {
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

	G4ParticleDefinition* part = step->GetTrack()->GetDefinition();

	const DetectorConstruction* detectorConstruction = static_cast<const DetectorConstruction*>(
		G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	G4LogicalVolume* fGeScoringVolume = detectorConstruction->GetGeScoringVolume();
	G4LogicalVolume* fSiScoringVolume = detectorConstruction->GetSiScoringVolume();

	// Add deposited energy at each step within the detector
	if (volume == fGeScoringVolume && part != G4Alpha::Alpha()) {
		G4double edep = step->GetTotalEnergyDeposit();
		fEventAction->AddEdepGe(edep);
		// G4cout << "Particle: " << part->GetParticleName() << G4endl;
	}
	if (volume == fSiScoringVolume && (part == G4Alpha::Alpha() || part->GetParticleName() == "Li7")) {
		G4double edep = step->GetTotalEnergyDeposit();
		fEventAction->AddEdepSi(edep);
		// G4cout << "Particle: " << part->GetParticleName() << G4endl;
		// G4cout << "Alpha edep: " << edep << G4endl;
	}
}


