// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "common/Builder.hpp"

#include "sdm/navierstokes/Convection1D.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace cf3 {
namespace sdm {
namespace navierstokes {

//////////////////////////////////////////////////////////////////////////////

common::ComponentBuilder<Convection1D,Term,LibNavierStokes> convection1d_builder;

/////////////////////////////////////////////////////////////////////////////

} // navierstokes
} // sdm
} // cf3
