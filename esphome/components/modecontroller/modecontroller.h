#ifndef ESPHOME_MODECONTROLLER_MODECONTROLLER_H
#define ESPHOME_MODECONTROLLER_MODECONTROLLER_H

#include "ctrlorchestrator.h"

namespace esphome
{
  namespace modecontroller
  {
    class ModeController
    {
    public:
      virtual void setup() {}

      virtual void activate() {}
      virtual void deactivate() {}

      virtual void loopActive() {}
      virtual void loopInactive() {}

      void setOrchestrator(const ControllerOrchestrator *o) { this->orchestrator = o; }

    protected:
      const ControllerOrchestrator *orchestrator{nullptr};
    };

  } // namespace modecontroller

}

#endif // ESPHOME_MODECONTROLLER_MODECONTROLLER_H