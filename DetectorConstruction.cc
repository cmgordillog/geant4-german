#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Materials
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* ge = nist->FindOrBuildMaterial("G4_Ge");
    G4Material* al = nist->FindOrBuildMaterial("G4_Al");
    G4Material* cu = nist->FindOrBuildMaterial("G4_Cu");
    G4Material* pb = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    // World
    G4double world_sizeXYZ = 1.5 * m;
    G4Box* solidWorld = new G4Box("World", world_sizeXYZ, world_sizeXYZ, world_sizeXYZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // Germanium detector
    G4double detector_radius = 33.15 * mm;
    G4double detector_height = 51.3 * mm;
    G4Tubs* solidDetector = new G4Tubs("Detector", 0, detector_radius, detector_height / 2, 0, 360 * deg);
    G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, ge, "Detector");
    new G4PVPlacement(0, G4ThreeVector(), logicDetector, "Detector", logicWorld, false, 0);

    // Aluminum casing
    G4double casing_thickness = 1 * mm;
    G4Tubs* solidCasing = new G4Tubs("Casing", detector_radius + 3 * mm, detector_radius + 3 * mm + casing_thickness, detector_height / 2 + casing_thickness, 0, 360 * deg);
    G4LogicalVolume* logicCasing = new G4LogicalVolume(solidCasing, al, "Casing");
    new G4PVPlacement(0, G4ThreeVector(), logicCasing, "Casing", logicWorld, false, 0);

    // Copper shielding
    G4double copper_thickness = 50 * mm;
    G4Tubs* solidCopper = new G4Tubs("Copper", detector_radius + 3 * mm + casing_thickness, detector_radius + 3 * mm + casing_thickness + copper_thickness, detector_height / 2 + casing_thickness + copper_thickness, 0, 360 * deg);
    G4LogicalVolume* logicCopper = new G4LogicalVolume(solidCopper, cu, "Copper");
    new G4PVPlacement(0, G4ThreeVector(), logicCopper, "Copper", logicWorld, false, 0);

    // Lead shielding
    G4double lead_thickness = 100 * mm;
    G4Tubs* solidLead = new G4Tubs("Lead", detector_radius + 3 * mm + casing_thickness + copper_thickness, detector_radius + 3 * mm + casing_thickness + copper_thickness + lead_thickness, detector_height / 2 + casing_thickness + copper_thickness + lead_thickness, 0, 360 * deg);
    G4LogicalVolume* logicLead = new G4LogicalVolume(solidLead, pb, "Lead");
    new G4PVPlacement(0, G4ThreeVector(), logicLead, "Lead", logicWorld, false, 0);

    // Scintillator
    G4double scintillator_sizeXY = 1 * m;
    G4double scintillator_thickness = 5 * cm;
    G4Box* solidScintillator = new G4Box("Scintillator", scintillator_sizeXY / 2, scintillator_sizeXY / 2, scintillator_thickness / 2);
    G4LogicalVolume* logicScintillator = new G4LogicalVolume(solidScintillator, plastic, "Scintillator");
    new G4PVPlacement(0, G4ThreeVector(0, 0, detector_height / 2 + casing_thickness + copper_thickness + lead_thickness + scintillator_thickness / 2), logicScintillator, "Scintillator", logicWorld, false, 0);

    return physWorld;
}
