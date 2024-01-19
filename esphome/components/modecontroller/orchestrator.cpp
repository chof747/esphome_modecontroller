#include "orchestrator.h"
#include "modecontroller.h"

#include <esphome/core/log.h>

using namespace esphome::modecontroller;

void Orchestrator::addController(std::string name, ModeController *controller)
//****************************************************************************************
{
  controllers[name] = std::unique_ptr<ModeController>(controller);
  controller->setOrchestrator(this);
}

void Orchestrator::setInitialController(std::string name)
//****************************************************************************************
{
  if (controllers.find(name) == controllers.end())
  {
    ESP_LOGE("orchestrator", "not found initial");
    return;
  }
  else
  {
    ESP_LOGD("orchestrator", "set initial to %s", name.c_str());
    initialController = controllers[name];
  }
}

void Orchestrator::setup()
//****************************************************************************************
{
  for (auto &entry : controllers)
  {
    entry.second->setup();
  }
}

void Orchestrator::loop()
//****************************************************************************************
{
  if (nullptr == activeController)
  {
    activateInitialController_();
  }

  activeController->loopActive();
  for (auto &entry : controllers)
  {
    if (entry.second != activeController)
    {
      entry.second->loopInactive();
    }
  }
}

std::shared_ptr<ModeController> Orchestrator::activate(std::string name)
//****************************************************************************************
{
  if (controllers.find(name) == controllers.end())
  {
    return nullptr;
  }

  if (nullptr != activeController)
  {
    activeController->deactivate();
  }

  activeController = controllers[name];
  activeController->activate();
  return activeController;
}

void esphome::modecontroller::Orchestrator::activateInitialController_()
//****************************************************************************************
{
  activeController = initialController;
  initialController->activate();
}
