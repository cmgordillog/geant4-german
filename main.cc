#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4PhysListFactory.hh"

// El valor de MACRO_PATH será definido en el CMakeLists.txt y pasado al compilador.
int main(int argc, char** argv) {
    // Crear el run manager
    G4RunManager* runManager = new G4RunManager();

    // Configurar la construcción del detector
    runManager->SetUserInitialization(new DetectorConstruction());

    // Configurar la lista de físicas
    G4PhysListFactory factory;
    G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("FTFP_BERT");
    runManager->SetUserInitialization(physicsList);

    // Configurar el generador de partículas primarias
    runManager->SetUserAction(new PrimaryGeneratorAction());

    // Inicializar el kernel de Geant4
    runManager->Initialize();

    // Configurar la interfaz de usuario
    G4UIExecutive* ui = nullptr; // Interfaz de usuario (modo interactivo)
    G4UImanager* UImanager = G4UImanager::GetUIpointer(); // Administra comandos

    if (argc == 1) {
        // Crear la ruta completa al archivo de macro usando MACRO_PATH
        G4String macroFile = G4String(MACRO_PATH) + "/init_vis.mac";

        // Modo interactivo con visualización
        ui = new G4UIExecutive(argc, argv);
        G4VisManager* visManager = new G4VisExecutive();
        visManager->Initialize();

        // Ejecutar el archivo de macro
        UImanager->ApplyCommand("/control/execute " + macroFile);

        // Iniciar la sesión interactiva
        ui->SessionStart();

        // Limpiar memoria
        delete visManager;
    } else {
        // Modo batch: ejecuta el archivo de macro pasado como argumento
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // Limpiar memoria
    delete runManager;
    delete ui;

    return 0;
}

