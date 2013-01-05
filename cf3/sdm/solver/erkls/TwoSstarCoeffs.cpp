// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include <cmath>
#include <sstream>
#include <iomanip>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "cf3/common/Builder.hpp"
#include "cf3/common/OptionList.hpp"
#include "cf3/common/OptionT.hpp"

#include "cf3/sdm/solver/erkls/TwoSstarCoeffs.hpp"

using namespace cf3::common;
using namespace cf3::common::XML;

namespace cf3 {
namespace sdm {
namespace solver {
namespace erkls {

///////////////////////////////////////////////////////////////////////////////////////

TwoSstarCoeffs::TwoSstarCoeffs(const std::string& name)
  : common::Component(name)
{
  options().add("alpha", std::vector<Real>())
      .description("Coefficients alpha")
      .link_to(&m_coeffs.alpha)
      .attach_trigger( boost::bind( &TwoSstarCoeffs::configure_nb_stages, this) );
  
  options().add("beta", std::vector<Real>())
      .description("Coefficients beta")
      .link_to(&m_coeffs.beta);

  options().add("gamma", std::vector<Real>())
      .description("Coefficients gamma")
      .link_to(&m_coeffs.gamma);

  options().add("order", m_coeffs.order)
      .link_to(&m_coeffs.order);
}

////////////////////////////////////////////////////////////////////////////////

void TwoSstarCoeffs::set(const Coefficients& coeffs)
{
  options().set("alpha",coeffs.alpha);
  options().set("beta",coeffs.beta);
  options().set("gamma",coeffs.gamma);
  options().set("order",coeffs.order);
}

////////////////////////////////////////////////////////////////////////////////

bool TwoSstarCoeffs::check_throw() const
{
  if (m_coeffs.order == 0u)
  {
    throw SetupError( FromHere(), "order of coefficients is not configured" );
    return false;
  }
  if (m_coeffs.nb_stages == 0u)
  {
    throw SetupError( FromHere(), "nb_stages of coefficients is zero, configure coefficients \"alpha\"" );
    return false;
  }
  if (m_coeffs.beta.size() != m_coeffs.nb_stages)
  {
    throw SetupError( FromHere(), "mismatch between beta and nb_stages in coefficients" );
    return false;
  }
  if (m_coeffs.gamma.size() != m_coeffs.nb_stages)
  {
    throw SetupError( FromHere(), "mismatch between gamma and nb_stages in coefficients" );
    return false;
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////

void TwoSstarCoeffs::configure_nb_stages()
{
  m_coeffs.nb_stages = m_coeffs.alpha.size();
}

////////////////////////////////////////////////////////////////////////////////

std::string TwoSstarCoeffs::str() const
{
  std::stringstream ss;
  for (int i=0; i<nb_stages(); ++i)
  {
    ss << std::setw(2) << i << ": " 
       << std::setw(9) << alpha(i) 
       << std::setw(9) << beta(i)
       << std::setw(9) << gamma(i);
    ss << std::endl;
  }
  return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

} // erkls
} // solver
} // sdm
} // cf3
