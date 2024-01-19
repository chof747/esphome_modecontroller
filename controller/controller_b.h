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
      virtual void loopActive()
      {
      } 

      virtual void setup() override;

      virtual void activate() override;

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

#endif // CONTROLLER_B_H