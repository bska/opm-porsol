//===========================================================================
//
// File: rockjfunc_test.cpp
//
// Created: Tue Jul 20 15:28:39 2010
//
// Author(s): Atgeirr F Rasmussen <atgeirr@sintef.no>
//            B�rd Skaflestad     <bard.skaflestad@sintef.no>
//
// $Date$
//
// $Revision$
//
//===========================================================================

/*
  Copyright 2010 SINTEF ICT, Applied Mathematics.
  Copyright 2010 Statoil ASA.

  This file is part of The Open Reservoir Simulator Project (OpenRS).

  OpenRS is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenRS is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenRS.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"

#include "../RockJfunc.hpp"
#include <opm/porsol/common/Matrix.hpp>
#include <opm/core/utility/Units.hpp>

#include <iostream>

using namespace Opm;

int main(int argc, char** argv)
try
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " file\n";
        return 1;
    }
    RockJfunc r;
    r.read("", argv[1]);

    OwnCMatrix perm(3,3,(double*)0);
    eye(perm);
    perm *= 100*Opm::prefix::milli*Opm::unit::darcy;
    double poro = 0.2;

    double sat;
    std::cout << "sat = " << std::flush;
    std::cin >> sat;
    double cp = r.capPress(perm, poro, sat);
    std::cout << "cap press = " << cp << std::endl;
    double sat2 = r.satFromCapPress(perm, poro, cp);
    std::cout << "sat2 = " << sat2 << std::endl;
}
catch (const std::exception &e) {
    std::cerr << "Program threw an exception: " << e.what() << "\n";
    throw;
}

