import os
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.cpp_types import std_vector, Component

CONF_CONTROLLER = 'controller'
CONF_INITIAL = 'initial'
CONF_BASECLASS = 'base_class'

modecontroller_ns = cg.esphome_ns.namespace("modecontroller")
Orchestrator = modecontroller_ns.class_("Orchestrator", cg.Component)

include_dir = os.path.dirname(os.path.realpath(__file__))

def initialIsDefined(config):
  initial = config[CONF_INITIAL]
  if not (initial in config[CONF_CONTROLLER]):
    raise cv.Invalid("The initial controller must be defined in the list of controllers")
  return config


CONFIG_SCHEMA = cv.Schema(cv.All({
    cv.GenerateID(): cv.declare_id(Orchestrator),
    cv.Required(CONF_CONTROLLER): cv.ensure_list(cv.string),
    cv.Required(CONF_INITIAL): cv.string,
    cv.Optional(CONF_BASECLASS, "esphome::modecontroller::ModeController"): cv.string
  },
  initialIsDefined
  ))

def set_baseclass(baseclass):
  tokens = baseclass.split("::")
  classname = tokens[-1]
  namespaces = tokens[:-1]

  beginning = " ".join([f"namespace {n} {{" for n in namespaces])
  classdecl = f"class {classname};"
  closing   = " }" * len(namespaces)

  cg.add_global(cg.RawExpression(f'{beginning} {classdecl} {closing}'))

async def to_code(config):

  set_baseclass(config[CONF_BASECLASS])

  #cg.add_global(cg.RawStatement(f'#include "base.h"'))

  var = cg.new_Pvariable(config[CONF_ID], cg.TemplateArguments(
    cg.RawExpression(config[CONF_BASECLASS])))
  await cg.register_component(var, config)

  #add the header file for the controller base class to main.cpp before the components are included
  modecontroller_header_path = os.path.join(include_dir, 'modecontroller.h')
  cg.add_global(cg.RawStatement(f'#include "{modecontroller_header_path}"'))

  for c in config[CONF_CONTROLLER]:
    lambda_code = f"new {c}()"
    cg.add(var.addController(cg.std_string(c), cg.RawExpression(lambda_code)))

  cg.add(var.setInitialController(cg.std_string(config[CONF_INITIAL])))