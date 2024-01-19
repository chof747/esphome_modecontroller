#ifndef ESPHOME_MODECONTROLLER_ORCHESTRATOR_H
#define ESPHOME_MODECONTROLLER_ORCHESTRATOR_H

#include <map>
#include <memory>
#include "esphome/core/component.h"


namespace esphome 
{
  namespace modecontroller
  {
    class ModeController;
    
    class Orchestrator : public esphome::Component
    {
      public:
        void addController(std::string name, ModeController* controller);
        void setInitialController(std::string name);
        std::shared_ptr<ModeController> activate(std::string name);

        void setup();
        void loop();

        std::shared_ptr<ModeController> getActive() { return activeController; }

      private:

        void activateInitialController_();

        std::map<std::string, std::shared_ptr<ModeController>> controllers;

        std::shared_ptr<ModeController> activeController{nullptr};
        std::shared_ptr<ModeController> initialController{nullptr};
    };

    template<class ControllerType> std::shared_ptr<ControllerType> getActiveController(Orchestrator* o)
    {
      dynamic_cast<std::shared_ptr<ControllerType>>(o->getActive());
    } 

  };
};

#endif //ESPHOME_MODECONTROLLER_ORCHESTRATOR_H