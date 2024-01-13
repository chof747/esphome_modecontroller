import os
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.cpp_types import std_vector, Component

CONF_CONTROLLER = 'controller'

modecontroller_ns = cg.esphome_ns.namespace("modecontroller")
Orchestrator = modecontroller_ns.class_("Orchestrator", cg.Component)

include_dir = os.path.dirname(os.path.realpath(__file__))


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Orchestrator),
    cv.Required(CONF_CONTROLLER): cv.ensure_list(cv.string),
})

async def to_code(config):
  var = cg.new_Pvariable(config[CONF_ID])
  await cg.register_component(var, config)

  modecontroller_header_path = os.path.join(include_dir, 'modecontroller.h')
  cg.add_global(cg.RawStatement(f'#include "{modecontroller_header_path}"'))

  for c in config[CONF_CONTROLLER]:
    lambda_code = f"new {c}()"
    cg.add(var.addController(cg.RawExpression(lambda_code)))