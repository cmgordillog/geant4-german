cmake_minimum_required(VERSION 3.10)
project(g4project)

# Definir la ruta para los archivos de macro
set(MACRO_PATH ${PROJECT_SOURCE_DIR}/macros)

# Pasar MACRO_PATH como definición al compilador
add_definitions(-DMACRO_PATH="${MACRO_PATH}")

# Encontrar el paquete Geant4
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

# Agregar el ejecutable
add_executable(g4project
  main.cc
  DetectorConstruction.cc
  PrimaryGeneratorAction.cc
  # Agrega aquí otros archivos .cc si los tienes
)

# Incluir directorios
target_include_directories(g4project PRIVATE ${PROJECT_SOURCE_DIR})

# Vincular bibliotecas de Geant4
target_link_libraries(g4project ${Geant4_LIBRARIES})

# Copiar los macros al directorio de compilación
configure_file(${MACRO_PATH}/init_vis.mac ${CMAKE_BINARY_DIR}/init_vis.mac COPYONLY)

# Establecer el directorio de salida para el ejecutable
set_target_properties(g4project PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

