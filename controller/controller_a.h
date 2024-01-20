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
      virtual void loopInactive()
      {
        static int cnt = 0;
        if (0 == ((cnt++) % 500))
        {
          ESP_LOGD(TAG, "A inactive");
        }
      }

      virtual void setup() override;
      virtual void btnPressed() override;
      virtual void activate() override;

    private:
      const char *TAG{"controller_a"};
    };
  }
}

void esphome::modecontroller::ControllerA::activate()
//****************************************************************************************
{
  ESP_LOGD(TAG, "Controller A Activated");
}

void esphome::modecontroller::ControllerA::setup()
//************************************************x****************************************
{
  ESP_LOGD(TAG, "Setup Controller A");
}

void esphome::modecontroller::ControllerA::btnPressed()
//************************************************x****************************************
{
  ESP_LOGD(TAG, "Buttton Pressed");
}

#endif // CONTROLLER_A_H