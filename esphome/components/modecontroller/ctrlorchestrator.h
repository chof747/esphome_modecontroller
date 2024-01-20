#ifndef ESPHOME_MODECONTROLLER_CTRLORCHESTRATOR_H
#define ESPHOME_MODECONTROLLER_CTRLORCHESTRATOR_H

namespace esphome
{
  namespace modecontroller 
  {
    class ControllerOrchestrator
    {
      public:
        virtual void activate(std::string name) = 0;
    };
  };
};

#endif //ESPHOME_MODECONTROLLER_CTRLORCHESTRATOR_H