cmake_minimum_required(VERSION 3.16)
project(RadarSim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CORE_SOURCES
    src/core/Vector2D.cpp
    src/core/SimulationClock.cpp
    src/core/ObjectManager.cpp
    src/core/SimulationEngine.cpp
    src/core/FlyingObjectFactory.cpp
    src/core/ScenarioLoader.cpp
)

set(UI_SOURCES
    src/ui/RadarWidget.cpp
    include/ui/RadarWidget.h
)

set(MOC_HEADERS
    include/core/SimulationClock.h
)

set(DOMAIN_SOURCES
    src/domain/FlyingObject.cpp
    src/domain/Aircraft.cpp
    src/domain/Helicopter.cpp
    src/domain/UAV.cpp
)

set(RADAR_SOURCES
    src/radar/IFFSystem.cpp
    src/radar/Radar.cpp
    src/radar/ThreatAnalyzer.cpp
    src/radar/TrackPredictor.cpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${CORE_SOURCES}
    ${DOMAIN_SOURCES}
    ${RADAR_SOURCES}
    ${UI_SOURCES}
    ${MOC_HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    SCENARIOS_DIR="${CMAKE_SOURCE_DIR}/scenarios"
)

# nlohmann/json
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Google Test

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(RadarSim_tests
    tests/test_vector2d.cpp
    src/core/Vector2D.cpp
)
target_link_libraries(RadarSim_tests PRIVATE GTest::gtest_main)
target_include_directories(RadarSim_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
include(GoogleTest)
gtest_discover_tests(RadarSim_tests)
