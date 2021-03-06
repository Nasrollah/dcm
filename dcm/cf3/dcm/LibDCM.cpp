// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "cf3/common/RegistLibrary.hpp"

#include "cf3/dcm/LibDCM.hpp"
#include "cf3/common/Link.hpp"

namespace cf3 {
namespace dcm {

using namespace common;

cf3::common::RegistLibrary<LibDCM> LibDCM;

void LibDCM::initiate()
{
  if(m_is_initiated)
    return;

  Handle<Component> lib = Core::instance().libraries().get_child("cf3.dcm");
  cf3_assert(lib);

  m_is_initiated = true;
}


} // dcm
} // cf3
