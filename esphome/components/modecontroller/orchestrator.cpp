#include "orchestrator.h"
#include "modecontroller.h"

using namespace esphome::modecontroller;

void Orchestrator::addController(ModeController* controller)
{
  controllers.emplace_back(controller);
}