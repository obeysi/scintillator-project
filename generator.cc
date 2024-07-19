#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");

    G4ThreeVector pos(0., 0., 0.);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
  	G4double energy = G4UniformRand() * 662. * GeV;

    // Set direction to x-axis
    G4ThreeVector direction(1., 0., 0.);

    // Set position to the origin
    G4ThreeVector position(0., 0., 0.);

    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticleMomentumDirection(direction);
    fParticleGun->SetParticlePosition(position);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
