#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

namespace esphome
{
  namespace modecontroller
  {
    class BaseController: public ModeController {
      public:
        virtual void btnPressed() {}
    };
  };
};

#endif //BASE_CONTROLLER_H