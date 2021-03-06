#pragma once

#include <memory>

#include "bot_core/atlas_command_t.hpp"

#include "drake/common/drake_copyable.h"
#include "drake/systems/controllers/qp_inverse_dynamics/qp_output_translator_system.h"

namespace drake {
namespace examples {
namespace humanoid_controller {

/**
 * A class that extends QpOutputTranslatorSystem to output an additional
 * bot_core::atlas_command_t.
 */
class AtlasCommandTranslatorSystem
    : public systems::controllers::qp_inverse_dynamics::
          QpOutputTranslatorSystem {
 public:
  DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(AtlasCommandTranslatorSystem)

  /**
   * @param robot A reference to the RigidBodyTree within the plant that is
   * being controlled. The lifespan of this reference must exceed that of this
   * class's instance. @p robot should only contain a single model instance.
   */
  explicit AtlasCommandTranslatorSystem(const RigidBodyTree<double>& robot);

  /**
   * Returns the output port for bot_core::atlas_command_t.
   */
  const systems::OutputPort<double>& get_output_port_atlas_command() const {
    return get_output_port(output_port_index_atlas_cmd_);
  }

 private:
  // Generates an additional bot_core::atlas_command_t output.
  void OutputCommand(const systems::Context<double>& context,
                     bot_core::atlas_command_t* output) const;

  int output_port_index_atlas_cmd_{0};

  // Joint level gains. These are in the actuator order within the
  // RigidBodyTree. These names are chosen to exactly match the API provided
  // by Boston Dynamics for the Atlas robot. ff stands for feedforward, f
  // stands for force.
  VectorX<double> k_q_p_;
  VectorX<double> k_q_i_;
  VectorX<double> k_qd_p_;
  VectorX<double> k_f_p_;
  VectorX<double> ff_qd_;
  VectorX<double> ff_qd_d_;
  VectorX<double> ff_f_d_;
  VectorX<double> ff_const_;
};

}  // namespace humanoid_controller
}  // namespace examples
}  // namespace drake
