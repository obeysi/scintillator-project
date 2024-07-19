#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4UserLimits.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();
    void ConstructScintillator();
    void ConstructDetector();
    void ConstructMaterials();
    void ConstructTruck();
    void ConstructSource();	
    void ConstructCisim();

private:
    G4Tubs *solidSource, *solidWheel, *solidWheel1;
    G4Box *solidWorld, *solidDetector, *solidTruck, *solidTruckIc, *solidScintillator, *solidAraba1, *solidAraba2, *solidAsphalt, *solidGlass, *solidCase, *solidCisim;
    G4LogicalVolume *logicWorld, *logicDetector, *logicTruck, *logicTruckIc, *logicSource, *logicScintillator, *logicAraba1, *logicAraba2, *logicAsphalt, *logicGlass, *logicWheel, *logicWheel1, *logicCase, *logicCisim;
    G4VPhysicalVolume *physWorld, *physDetector, *physTruck, *physTruckIc, *physSource, *physScintillator, *physAraba1, *physAraba2, *physAsphalt, *physGlass, *physWheel, *physWheel1, *physCase, *physCisim;

    G4OpticalSurface *mirrorSurface;

    G4Material *SiO2, *H2O, *Aerogel, *worldMat, *C9H10, *NaI, *Aluminum, *glassMaterial, *stainlessSteel, *asphaltMaterial, *C4H6, *Cobalt60, *atmosphere, *Uranium, *C8H10;
    G4Element *C, *Na, *I, *O, *N, *Cr, *Ni, *Fe, *Ar, *U, *Al;

    void DefineMaterials();
    virtual void ConstructSDandField();

    G4GenericMessenger *fMessenger;

    G4LogicalVolume *fScoringVolume;

    G4int nRows, nCols;

    G4double xWorld, yWorld, zWorld;

    G4bool isScintillator, isDetector, isTruck, isSource, isCisim;
};

#endif
