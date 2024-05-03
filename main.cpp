#include <BipedalLocomotion/ParametersHandler/StdImplementation.h>
#include <BipedalLocomotion/RobotInterface/YarpRobotControl.h>
#include <BipedalLocomotion/RobotInterface/YarpSensorBridge.h>

#include <filesystem>
#include <gz/common/Console.hh>
#include <gz/sim/Entity.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/sim/EventManager.hh>
#include <gz/sim/Joint.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/TestFixture.hh>
#include <gz/sim/Util.hh>
#include <gz/sim/World.hh>
#include <gzyarp/DeviceRegistry.hh>
#include <iostream>
#include <memory>
#include <sdf/Element.hh>
#include <string>
#include <vector>
#include <yarp/dev/PolyDriverList.h>

int main()
{
    auto sdfPath = std::filesystem::path(CMAKE_CURRENT_SOURCE_DIR) / "single_pendulum_world.sdf";
    std::cerr << "SDF path: " << sdfPath << std::endl;

    gz::sim::TestFixture testFixture{sdfPath};
    gz::common::Console::SetVerbosity(4);
    bool configured = false;
    std::vector<std::string> deviceKeys{};
    yarp::dev::PolyDriverList polyDriverList{};

    testFixture
        .OnConfigure([&](const gz::sim::Entity& _worldEntity,
                         const std::shared_ptr<const sdf::Element>& /*_sdf*/,
                         gz::sim::EntityComponentManager& _ecm,
                         gz::sim::EventManager& /*_eventMgr*/) {
            gz::sim::World world(_worldEntity);
            auto modelEntity = world.ModelByName(_ecm, "single_pendulum");
            // deviceKeys = gzyarp::DeviceRegistry::getHandler()->getDevicesKeys(_ecm);

            auto ok = gzyarp::DeviceRegistry::getHandler()
                          ->getDevicesAsPolyDriverList(_ecm,
                                                       scopedName(modelEntity, _ecm),
                                                       polyDriverList,
                                                       deviceKeys);
            if (!ok)
            {
                std::cerr << "Unable to get devices as PolyDriverList." << std::endl;
                return;
            }

            std::cerr << "# of retrieved devices keys: " << deviceKeys.size() << std::endl;
            configured = true;
        })
        .Finalize();

    if (!configured)
    {
        std::cerr << "Unable to configure the test fixture." << std::endl;
        return 1;
    }

    // Configure YarpSensorBridge parameters
    auto paramHandler = std::make_shared<BipedalLocomotion::ParametersHandler::StdImplementation>();
    // paramHandler->setParameter();

    // Instantiate and initialize YarpSensorBridge

    // auto sensorBridge = std::make_unique<BipedalLocomotion::RobotInterface::YarpSensorBridge>();
    // if (!sensorBridge->initialize(paramHandler->getGroup("SENSOR_BRIDGE")))
    // {
    //     std::cerr << "Unable to initialize the sensor bridge." << std::endl;
    //     return 1;
    // }

    // Instantiate and initialize YarpRobotControl
    return 0;
}
