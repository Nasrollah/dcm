// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef cf3_sdm_Model_hpp
#define cf3_sdm_Model_hpp

////////////////////////////////////////////////////////////////////////////////

#include "cf3/solver/Model.hpp"
#include "cf3/sdm/LibSDM.hpp"

namespace cf3 {
namespace common { class ActionDirector; }
namespace mesh { class Dictionary; }
namespace solver { class Time; class TimeStepping; class History; class PDE; class PDESolver;class ComputeRHS; }
namespace sdm {

////////////////////////////////////////////////////////////////////////////////

/// @brief Spectral Finite Difference iterative solver
///
/// Spectral Finite Difference solver,
/// combining a forward euler time marching scheme with
/// a high-order spectral finite difference spatial scheme
/// @author Willem Deconinck
class sdm_API Model : public common::Component {

public: // functions

  /// Contructor
  /// @param name of the component
  Model ( const std::string& name );

  /// Virtual destructor
  virtual ~Model();

  /// Get the class name
  static std::string type_name () { return "Model"; }

  Handle<solver::PDE> add_pde( const std::string& name,
                               const std::string& type,
                               const Uint order );

  Handle<solver::PDE> add_pde( const std::string& name,
                               const std::string& type,
                               const Uint order,
                               const std::vector<Handle<common::Component> > &regions);

  Handle<solver::PDESolver> add_solver( const Handle<solver::PDE>& pde,
                                        const std::string& type,
                                        const std::string& time_step );

  const Handle<mesh::Domain>& domain() { return m_domain; }

  const Handle<common::Group>& tools() { return m_tools; }

  const Handle<solver::TimeStepping>& time_stepping() { return m_time_stepping; }

public: // signals

  void signal_add_pde( common::SignalArgs& args);
  void signature_add_pde( common::SignalArgs& args);

  void signal_add_solver( common::SignalArgs& args);
  void signature_add_solver( common::SignalArgs& args);

//  void signal_add_probe(common::SignalArgs& args);
//  void signature_add_probe(common::SignalArgs& args);

public: // functions

  Handle<mesh::Dictionary> create_sd_space(const std::string& name, const Uint& order, const std::vector<Handle<common::Component> > &regions);

private: // functions

  void config_solution();

  void build_faces(cf3::mesh::Mesh &mesh);

private: // data

  Handle<common::Group>                     m_tools;
  Handle<solver::TimeStepping>              m_time_stepping;
  Handle<mesh::Domain>                      m_domain;
  Handle<solver::History>                   m_history;
//  Handle<sdm::ComputeLNorm>                 m_residual_norm_computer;
};

////////////////////////////////////////////////////////////////////////////////

} // sdm
} // cf3

////////////////////////////////////////////////////////////////////////////////

#endif // cf3_sdm_time_integration_solver_hpp
