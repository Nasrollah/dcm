// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "common/Builder.hpp"

#include "dcm/scalar/LinearAdvection1D.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace cf3 {
namespace dcm {
namespace scalar {

//////////////////////////////////////////////////////////////////////////////

common::ComponentBuilder<LinearAdvection1D,Term,LibScalar> linear_advection1d_builder;

/////////////////////////////////////////////////////////////////////////////

} // scalar
} // dcm
} // cf3
