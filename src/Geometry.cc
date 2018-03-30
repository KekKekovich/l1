
#include "../include/Geometry.hh"
#include <G4PVPlacement.hh>

#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4SolidStore.hh>
#include <G4VisAttributes.hh>
Geometry::Geometry() {


    nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    water_mat = nist->FindOrBuildMaterial("G4_WATER");
    


    size = 15 * m;

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

    std:: ofstream fout("../result.txt");

    G4Material* NaI = nist -> FindOrBuildMaterial("G4_SODIUM_IODIDE");
    fout << "For material" << NaI-> GetName() << " :" << G4endl;
    for (unsigned int i=0; i< static_cast<unsigned int>(NaI->GetNumberOfElements()); i++) {
        fout << "Element:" << NaI -> GetElement(i) -> GetName() <<
                                                                  "| Atoms:" << NaI -> GetAtomsVector()[i] << G4endl;
    }

//    fout << '\n' << NaI << '\n';
    fout << nist -> FindOrBuildMaterial("G4_SODIUM_IODIDE");
    fout << nist -> FindOrBuildMaterial("G4_WATER");

    G4Isotope *u235 = new G4Isotope("U235", 92, 235, 235.044*g/mole);
    G4Isotope *u238 = new G4Isotope("U238", 92, 238, 238.051*g/mole);

    G4Element *enrichedU = new G4Element("enrichedU", "U", 2);
    enrichedU -> AddIsotope(u235, 5.0* perCent);
    enrichedU -> AddIsotope(u238, 95.0* perCent);
    G4Element *elF = new G4Element("Fluorine", "F", 9., 18.998*g/mole);

    G4Material *fuel = new G4Material("NuclearFuel", 5.09*g/cm3, 2, kStateSolid, 640*kelvin, 1.5e7*pascal);

    fuel -> AddElement(elF,6);
    fuel -> AddElement(enrichedU,1);

    fout << fuel << G4endl;







    return world_VP;
}