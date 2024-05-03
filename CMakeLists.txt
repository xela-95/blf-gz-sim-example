cmake_minimum_required(VERSION 3.16)

project(blf-gz-sim)

find_package(YARP REQUIRED)
find_package(gz-sim8 REQUIRED)
find_package(gz-sim-yarp-plugins COMPONENTS gz-sim-yarp-device-registry REQUIRED)
find_package(BipedalLocomotionFramework 
    COMPONENTS  RobotInterface 
                ParametersHandlerYarpImplementation 
                RobotInterfaceYarpImplementation
    REQUIRED)

add_executable(blf-gz-sim main.cpp)

target_link_libraries(blf-gz-sim PRIVATE BipedalLocomotion::RobotInterface)
target_link_libraries(blf-gz-sim PRIVATE gz-sim-yarp-plugins::gz-sim-yarp-device-registry)
target_compile_definitions(blf-gz-sim PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
