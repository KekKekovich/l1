
#include "../include/Geometry.hh"
#include <G4PVPlacement.hh>

#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4SolidStore.hh>
#include <G4VisAttributes.hh>
Geometry::Geometry() {


    nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_Galactic");


    size = 5 * m;

}


Geometry::~Geometry(){


}

G4VPhysicalVolume* Geometry::Construct() {
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    world = new G4Box("world", size / 2., size / 2., size / 2.);
    world_log = new G4LogicalVolume(world, world_mat, "world_log");
    world_log->SetVisAttributes(G4VisAttributes::Invisible);
    world_VP = new G4PVPlacement(nullptr, G4ThreeVector(), world_log, "world_PV", nullptr, false, 0);


    return world_VP;
}
