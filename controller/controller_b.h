#ifndef CONTROLLER_B_H
#define CONTROLLER_B_H

#include <esphome/core/log.h>
#include <base.h>

namespace esphome
{
  namespace modecontroller
  {
    class ControllerB : public BaseController
    {
    public:
      virtual void loopInactive()
      {
        static int cnt = 0;
        if (0 == ((cnt++) % 500))
        {
          ESP_LOGD(TAG, "B inactive");
        }
      } 

      virtual void setup() override;
      virtual void activate() override;

      virtual void btnPressed() override;

    private:
      const char *TAG{"controller_b"};
    };
  }
}

void esphome::modecontroller::ControllerB::setup()
//****************************************************************************************
{
  ESP_LOGD(TAG, "Setup Controller B ");
}

void esphome::modecontroller::ControllerB::activate()
//****************************************************************************************
{
  ESP_LOGD(TAG, "Controller B Activated");
}

void esphome::modecontroller::ControllerB::btnPressed()
//************************************************x****************************************
{
  ESP_LOGD(TAG, "Buttton Pressed");
  orchestrator->activate("esphome::modecontroller::ControllerA");
}



#endif // CONTROLLER_B_H