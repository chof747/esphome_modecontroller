#ifndef CONTROLLER_A_H
#define CONTROLLER_A_H

#include <esphome/core/log.h>
#include "base.h"

namespace esphome
{
  namespace modecontroller
  {
    class ControllerA : public BaseController
    {
    public:
      virtual void loopActive()
      {
      }

      virtual void setup() override;

    private:
      const char *TAG{"controller_a"};
    };
  }
}

void esphome::modecontroller::ControllerA::setup()
//****************************************************************************************
{
  ESP_LOGD(TAG, "Setup Controller A");
}

#endif // CONTROLLER_A_H