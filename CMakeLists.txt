cmake_minimum_required(VERSION 3.23)
project(MachineLearningExperiments VERSION 1.0)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
include(CheckCCompilerFlag)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64)
set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;arm64")
check_c_compiler_flag("-arch arm64" arm64Supported)
set(CMAKE_CXX_STANDARD 20)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND arm64Supported MATCHES 1)
    set(CMAKE_OSX_ARCHITECTURES arm64)
ENDIF ()


FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG c1064bae925693667c7a34cad264bd5ea3ece177
)

FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SFML 2.6.0 COMPONENTS system window graphics network audio)

IF (WIN32)
    link_directories($ENV{BOOST_LIB})
ELSE()
    find_package(Boost
            1.76.0
            REQUIRED
            COMPONENTS filesystem
            )

ENDIF()

add_executable(MachineLearningExperiments main.cpp src/framework/Framework.h src/framework/Framework.cpp src/framework/engine/world/World.h src/framework/engine/world/World.cpp src/framework/engine/world/WorldItem.cpp src/framework/engine/world/WorldItem.h src/framework/engine/constants.h src/experiment/00-test/Test.cpp src/experiment/00-test/Test.h src/framework/Experiment.h src/framework/Experiment.cpp src/framework/engine/world/world_items/Being.cpp src/framework/engine/world/world_items/Being.h src/framework/Utils.h src/framework/engine/NeuronalNetwork.cpp src/framework/engine/NeuronalNetwork.h)

IF (WIN32)
    target_include_directories(MachineLearningExperiments PUBLIC $ENV{BOOST_ROOT})
    target_link_libraries(MachineLearningExperiments sfml-graphics sfml-audio sfml-window sfml-system)
    target_link_directories(MachineLearningExperiments PUBLIC $ENV{BOOST_LIB})
    file(COPY ./external_bin/openal32.dll DESTINATION ./)
ELSE()
    target_link_libraries(MachineLearningExperiments sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES})
    target_include_directories(MachineLearningExperiments PUBLIC ${Boost_INCLUDE_DIRS})
ENDIF()

file(COPY ./resources DESTINATION ./)
