#ifndef ESPHOME_MODECONTROLLER_ORCHESTRATOR_H
#define ESPHOME_MODECONTROLLER_ORCHESTRATOR_H

#include <vector>
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
        void addController(ModeController* controller);


      private:
        std::vector<std::unique_ptr<ModeController>> controllers;
    };
  };
};

#endif //ESPHOME_MODECONTROLLER_ORCHESTRATOR_H