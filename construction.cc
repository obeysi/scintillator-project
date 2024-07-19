#include "construction.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
    nCols = 100;
    nRows = 100;

    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

    fMessenger->DeclareProperty("nCols", nCols, "Number of cols");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");
    fMessenger->DeclareProperty("scintillator", isScintillator, "Construct Scintillator");
    fMessenger->DeclareProperty("detector", isDetector, "Construct Detector");
    fMessenger->DeclareProperty("truck", isTruck, "Construct Truck");
    fMessenger->DeclareProperty("source", isSource, "Construct Source");
    fMessenger->DeclareProperty("cisim", isSource, "Construct Cisim");

    DefineMaterials();

    isScintillator = true;
    isDetector = true;
    isTruck = false;
    isSource = false;
    isCisim = true;	

    xWorld = 9.*m;
    yWorld = 9.*m;
    zWorld = 9.*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    
    G4NistManager *nist = G4NistManager::Instance();

    C = nist->FindOrBuildElement("C");
    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    
    asphaltMaterial = nist->FindOrBuildMaterial("G4_CONCRETE");
    
    glassMaterial = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
    
	Al = nist->FindOrBuildElement("Al");
	Aluminum = new G4Material("Aluminum", 2.7 * g/cm3, 1);
	Aluminum->AddElement(Al, 1);
	
	Uranium = new G4Material("Uranium", 19.1 * g/cm3, 1);
	U = nist->FindOrBuildElement("U");
	Uranium->AddElement(U, 1);
	
	N = nist->FindOrBuildElement("N");
	O = nist->FindOrBuildElement("O");
	Ar = nist->FindOrBuildElement("Ar");

	atmosphere = new G4Material("Atmosphere", 1.225 * mg/cm3, 3, kStateGas);
	atmosphere->AddElement(N, 0.78);  
	atmosphere->AddElement(O, 0.21);  
	atmosphere->AddElement(Ar, 0.01); 

	Fe = nist->FindOrBuildElement("Fe");
    Cr = nist->FindOrBuildElement("Cr");
  	Ni = nist->FindOrBuildElement("Ni");

	stainlessSteel = new G4Material("StainlessSteel", 7.8 * g/cm3, 3);
    stainlessSteel->AddElement(Fe, 0.74);  
    stainlessSteel->AddElement(Cr, 0.18);  
    stainlessSteel->AddElement(Ni, 0.08); 
	
	C4H6 = new G4Material("C4H6", 1.0*g/cm3, 2);
    C4H6->AddElement(nist->FindOrBuildElement("C"), 4);
    C4H6->AddElement(nist->FindOrBuildElement("H"), 6);

    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);
    /*
    G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4double rindexNaI[2] = {1.78, 1.78};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
*/
    Na = nist->FindOrBuildElement("Na");
    I = nist->FindOrBuildElement("I");
    NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(Na, 1);
    NaI->AddElement(I, 1);
    
 	C9H10 = new G4Material("C9H10", 1.032*g/cm3, 2);

    C9H10->AddElement(nist->FindOrBuildElement("C"), 9);
    C9H10->AddElement(nist->FindOrBuildElement("H"), 10);
    
    C8H10 = new G4Material("C8H10", 1.01*g/cm3, 2);
    
    C8H10->AddElement(nist->FindOrBuildElement("C"), 8);
    C8H10->AddElement(nist->FindOrBuildElement("H"), 10);

 /*   G4double fraction[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
    mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
    mptNaI->AddProperty("FASTCOMPONENT", energy, fraction, 2); 
    mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);
    mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptNaI->AddConstProperty("FASTTIMECONSTANT", 250.*ns);
    mptNaI->AddConstProperty("YIELDRATIO",1.);
    NaI->SetMaterialPropertiesTable(mptNaI);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    mirrorSurface = new G4OpticalSurface("mirrorSurface");

    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

    G4double reflectivity[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);

    mirrorSurface->SetMaterialPropertiesTable(mptMirror);*/


}

void MyDetectorConstruction::ConstructTruck()
{
	//Tır ve Dorse
	
	solidTruck = new G4Box("solidTruck", 2.35*m, 2.37*m, 5.9*m);
	logicTruck = new G4LogicalVolume(solidTruck, Aluminum, "logicalTruck");
	physTruck = new G4PVPlacement(0, G4ThreeVector(0 * cm, -5.93 * m, -2.1*m), logicTruck, "physTruck", logicWorld, false, 0, true);
	
	solidTruckIc = new G4Box("solidTruckIc", 2.33*m, 2.35*m, 5.8*m);
	logicTruckIc= new G4LogicalVolume(solidTruckIc, worldMat, "logicalTruckIc");
	physTruckIc = new G4PVPlacement(0, G4ThreeVector(0 * cm, -5.93 * m, -2.1*m), logicTruckIc, "physTruckIc", logicWorld, false, 0, true);
	
	solidAraba1 = new G4Box("solidAraba1", 2.41*m,10*cm,8*m);
	logicAraba1 = new G4LogicalVolume(solidAraba1, stainlessSteel, "logicalAraba1");
	physAraba1 = new G4PVPlacement(0, G4ThreeVector(0 * cm, -8.4 * m, 0.*m), logicAraba1, "physAraba1", logicWorld, false, 0, true); 
    
    G4VisAttributes* Araba1VisAtt = new G4VisAttributes(G4Color(0.0, 0.5, 1.0));
	Araba1VisAtt->SetForceSolid(true);
	logicAraba1->SetVisAttributes(Araba1VisAtt);
    
    solidAraba2 = new G4Box("solidAraba2", 2.35*m,2.37*m,1.6*m);
	logicAraba2 = new G4LogicalVolume(solidAraba2, stainlessSteel, "logicalAraba2");
	physAraba2 = new G4PVPlacement(0, G4ThreeVector(0 * cm, -5.93 * m, 6.4*m), logicAraba2, "physAraba2", logicWorld, false, 0, true); 
	
    G4VisAttributes* Araba2VisAtt = new G4VisAttributes(G4Color(0.0, 0.5, 1.0));
	Araba2VisAtt->SetForceSolid(true);
	logicAraba2->SetVisAttributes(Araba2VisAtt);
	
	//Lastikler
	
	G4double WheelRadius = 50.0 * cm;
	G4double WheelHeight = 35.0 * cm;
	solidWheel = new G4Tubs("solidWheel", 0.0, WheelRadius, 0.5 * WheelHeight, 0.0, 2.0 * M_PI);
	logicWheel = new G4LogicalVolume(solidWheel, C4H6, "logicWheel");
	
	G4VisAttributes* wheelVisAtt = new G4VisAttributes(G4Color(0.5, 0.5, 0.5)); 
    wheelVisAtt->SetForceSolid(true);
    logicWheel->SetVisAttributes(wheelVisAtt);
	
	G4RotationMatrix* rotation = new G4RotationMatrix();
	rotation->rotateY(90. * deg); 
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(2.45*m, -8.5*m, -4*m), logicWheel, "physWheel1", logicWorld, false, 0, true);
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(2.45*m, -8.5*m, -5.5*m), logicWheel, "physWheel2", logicWorld, false, 0, true);
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(2.45*m, -8.5*m, 1*m), logicWheel, "physWheel3", logicWorld, false, 0, true);
	
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(-2.45*m, -8.5*m, -4*m), logicWheel, "physWheel5", logicWorld, false, 0, true);
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(-2.45*m, -8.5*m, -5.5*m), logicWheel, "physWheel6", logicWorld, false, 0, true);
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(-2.45*m, -8.5*m, 1*m), logicWheel, "physWheel7", logicWorld, false, 0, true);
	
	G4double Wheel1Radius = 80.0 * cm;
	G4double Wheel1Height = 50.0 * cm;
	solidWheel1 = new G4Tubs("solidWheel1", 0.0, Wheel1Radius, 0.5 * Wheel1Height, 0.0, 2.0 * M_PI);
	logicWheel1 = new G4LogicalVolume(solidWheel1, C4H6, "logicWheel1");
	
	G4VisAttributes* wheel1VisAtt = new G4VisAttributes(G4Color(0.5, 0.5, 0.5)); 
    wheel1VisAtt->SetForceSolid(true);
    logicWheel1->SetVisAttributes(wheel1VisAtt);
	
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(2.4*m, -8.2*m, 6.2*m), logicWheel1, "physWheel8", logicWorld, false, 0, true);
	physWheel = new G4PVPlacement(rotation, G4ThreeVector(-2.4*m, -8.2*m, 6.2*m), logicWheel1, "physWheel9", logicWorld, false, 0, true);
    
    //Ön Cam 
    
    solidGlass = new G4Box("solidGlass", 200*cm,120*cm,0.1*cm);
	logicGlass = new G4LogicalVolume(solidGlass, glassMaterial, "logicalGlass");
	physGlass = new G4PVPlacement(0, G4ThreeVector(0., -550 * cm, 8.02*m), logicGlass, "physGlass", logicWorld, false, 0, true); 
    
    G4VisAttributes* GlassVisAtt = new G4VisAttributes(G4Color(1, 1, 1));
	GlassVisAtt->SetForceSolid(true);
	logicGlass->SetVisAttributes(GlassVisAtt);
	
	//Asfalt
	
	solidAsphalt = new G4Box("solidAsphalt", 9*m,0.0000001*cm,9*m);
	logicAsphalt = new G4LogicalVolume(solidAsphalt, asphaltMaterial, "logicalAsphalt");
	physAsphalt = new G4PVPlacement(0, G4ThreeVector(0., -9 * m, 0.), logicAsphalt, "physAsphalt", logicWorld, false, 0, true); 
    
    G4VisAttributes* AsphaltVisAtt = new G4VisAttributes(G4Color(0.3, 0.3, 0.3));
	AsphaltVisAtt->SetForceSolid(true);
	logicAsphalt->SetVisAttributes(AsphaltVisAtt);
	
}

void MyDetectorConstruction::ConstructSource()
{
	G4double sourceRadius = 60.0 * cm;
	G4double sourceHeight = 200.0 * cm;
	solidSource = new G4Tubs("solidSource", 0.0, sourceRadius, 0.5 * sourceHeight, 0.0, 2.0 * M_PI);
	logicSource = new G4LogicalVolume(solidSource, Uranium, "logicalSource");
	G4RotationMatrix* rotation = new G4RotationMatrix();
	rotation->rotateX(90. * deg); 
	physSource = new G4PVPlacement(rotation, G4ThreeVector(0.8*m, -7.25*m, -6*m), logicSource, "physSource1", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(0.8*m, -7.25*m, -4*m), logicSource, "physSource2", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(0.8*m, -7.25*m, -2*m), logicSource, "physSource3", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(0.8*m, -7.25*m, 0.*m), logicSource, "physSource4", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(0.8*m, -7.25*m, 2*m), logicSource, "physSource5", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(-0.8*m, -7.25*m, -6*m), logicSource, "physSource1a", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(-0.8*m, -7.25*m, -4*m), logicSource, "physSource2a", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(-0.8*m, -7.25*m, -2*m), logicSource, "physSource3a", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(-0.8*m, -7.25*m, 0.*m), logicSource, "physSource4a", logicWorld, false, 0, true);
	physSource = new G4PVPlacement(rotation, G4ThreeVector(-0.8*m, -7.25*m, 2*m), logicSource, "physSource5a", logicWorld, false, 0, true);
	
	G4VisAttributes* SourceVisAtt = new G4VisAttributes(G4Color(0.8, 0.6, 0.0));
	SourceVisAtt->SetForceSolid(true);
	logicSource->SetVisAttributes(SourceVisAtt);
	  
}

void MyDetectorConstruction::ConstructScintillator()
{

    solidScintillator = new G4Box("solidScintillator", 100 * cm, 10 * cm, 10 * cm);

    logicScintillator = new G4LogicalVolume(solidScintillator, C8H10, "logicalScintillator");
    
    G4VisAttributes* scintillatorVisAtt = new G4VisAttributes(G4Color(0,0,128)); 
    logicScintillator->SetVisAttributes(scintillatorVisAtt);
    
    G4RotationMatrix* rotYz = new G4RotationMatrix();
    rotYz->rotateY(90 * deg);
    rotYz->rotateZ(90 * deg);
    physScintillator = new G4PVPlacement(rotYz, G4ThreeVector(8*m, 0*m, 0 * cm), logicScintillator, "physScintillator1", logicWorld, false, 0, true);
    /*
    G4RotationMatrix* rotY2z2 = new G4RotationMatrix();
    rotY2z2->rotateY(90 * deg);
    rotY2z2->rotateZ(90 * deg);
    physScintillator = new G4PVPlacement(rotY2z2, G4ThreeVector(-4.175*m, -7.2*m, 0*cm), logicScintillator, "physScintillator2", logicWorld, false, 0, true);
    */
	G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

    solidCase = new G4Box("solidCase", 148*cm, 15*cm, 10*cm);
    logicCase = new G4LogicalVolume(solidCase, Aluminum, "logicalCase");
    
    physCase = new G4PVPlacement(rotYz, G4ThreeVector(8*m, 0*m, 0 * cm), logicCase, "physCase1", logicWorld, false, 0, true);
   //physCase = new G4PVPlacement(rotYz, G4ThreeVector(0*m, 0*m, 0 * cm), logicCase, "physCase2", logicWorld, false, 0, true);
  
}

void MyDetectorConstruction::ConstructCisim()
{
    // Cismin solid (katı) geometrisini tanımla
    G4Box* solidCisim = new G4Box("solidCisim", 1*m, 1*m, 1*m);

    // Cismin mantıksal (logical) hacmini oluştur ve içine Uranium malzemesini koy
    G4Material* Uranium = G4NistManager::Instance()->FindOrBuildMaterial("G4_U"); // Örnek olarak uranyum malzemesi seçildi, siz kendi malzemenizi kullanabilirsiniz.
    G4LogicalVolume* logicCisim = new G4LogicalVolume(solidCisim, Uranium, "logicalCisim");

    // Cismin fiziksel (physical) yerleşimini oluştur
    G4RotationMatrix* rotation = nullptr;  // Döndürme matrisi (varsayılan olarak nullptr kullanılabilir)
    G4ThreeVector position(6*m, 0*m, 0*m);  // Yerleştirme konumu

    G4VPhysicalVolume* physCisim = new G4PVPlacement(
        rotation,            // Döndürme matrisi
        position,            // Konum vektörü
        logicCisim,          // Mantıksal hacim
        "physCisim",         // Fiziksel birimin adı
        logicWorld,          // Fiziksel dünya (yerleştirilecek yer)
        false,               // Yerleştirme süslemesi (sensitivite)
        0,                   // Kopma numarası
        true                 // Hacim yerleştirme optimizasyonu
    );
}
void MyDetectorConstruction::ConstructDetector()
{
solidDetector = new G4Box("solidDetector", 100. * cm, 10. * cm, 10 * cm);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    G4RotationMatrix* rotY3z3 = new G4RotationMatrix();
    rotY3z3->rotateY(90 * deg);
    rotY3z3->rotateZ(90 * deg);
    physDetector = new G4PVPlacement(rotY3z3, G4ThreeVector(8*m, 0*m, 0*cm), logicDetector, "physDetector1", logicWorld, false, 0, true);

  /*  G4RotationMatrix* rotY4z4 = new G4RotationMatrix();
    rotY4z4->rotateY(90 * deg);
    rotY4z4->rotateZ(90 * deg);
    physDetector = new G4PVPlacement(rotY4z4, G4ThreeVector(-4.175*m, -7.2*m, 0 * cm), logicDetector, "physDetector2", logicWorld, false, 0, true);
  */ 
    fScoringVolume = logicDetector;  
} 

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);


    if(isDetector)
        ConstructDetector();
    
    if(isScintillator)
        ConstructScintillator();
        
	if(isTruck)
        ConstructTruck(); 
    
    if(isSource)
    	ConstructSource();
    
    if(isCisim)
    	ConstructCisim();

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    if(logicDetector != NULL)
        logicDetector->SetSensitiveDetector(sensDet);
}
