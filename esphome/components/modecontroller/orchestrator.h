#ifndef ESPHOME_MODECONTROLLER_ORCHESTRATOR_H
#define ESPHOME_MODECONTROLLER_ORCHESTRATOR_H

#include <map>
#include <memory>
#include <esphome/core/component.h>
#include <esphome/core/log.h>

#include "ctrlorchestrator.h"

namespace esphome
{
  namespace modecontroller
  {

    template <class ControllerType>
    class Orchestrator : public esphome::Component, public ControllerOrchestrator
    {
    public:
      typedef std::shared_ptr<ControllerType> ctrlPtr_type;

      void addController(std::string name, ControllerType *controller)
      //**********************************************************************************
      {
        controllers[name] = ctrlPtr_type(controller);
        controller->setOrchestrator(this);
      }

      void setInitialController(std::string name)
      //**********************************************************************************
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

      ctrlPtr_type activate(std::string name)
      //**********************************************************************************
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

      void setup()
      //**********************************************************************************
      {
        for (auto &entry : controllers)
        {
          entry.second->setup();
        }
      }

      void loop()
      //**********************************************************************************
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

      ctrlPtr_type getActive() { return activeController; }

    private:
      void activateInitialController_()
      //**********************************************************************************
      {
        activeController = initialController;
        initialController->activate();
      }

      std::map<std::string, ctrlPtr_type> controllers;

      ctrlPtr_type activeController{nullptr};
      ctrlPtr_type initialController{nullptr};
    };

  };
};

#endif // ESPHOME_MODECONTROLLER_ORCHESTRATOR_H