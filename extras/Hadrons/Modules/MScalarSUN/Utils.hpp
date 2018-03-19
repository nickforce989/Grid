/*************************************************************************************

Grid physics library, www.github.com/paboyle/Grid 

Source file: extras/Hadrons/Modules/MScalarSUN/Utils.hpp

Copyright (C) 2015-2018

Author: Antonin Portelli <antonin.portelli@me.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

See the full license in the file "LICENSE" in the top level distribution directory
*************************************************************************************/
/*  END LEGAL */
#ifndef Hadrons_MScalarSUN_Utils_hpp_
#define Hadrons_MScalarSUN_Utils_hpp_

#include <Grid/Hadrons/Global.hpp>
#include <Grid/Hadrons/Module.hpp>

BEGIN_HADRONS_NAMESPACE

BEGIN_MODULE_NAMESPACE(MScalarSUN)

GRID_SERIALIZABLE_ENUM(DiffType, undef, forward, 1, backward, 2, central, 3);

template <typename Field>
inline void dmu(Field &out, const Field &in, const unsigned int mu, const DiffType type)
{
    auto & env = Environment::getInstance();

    if (mu >= env.getNd())
    {
        HADRON_ERROR(Range, "Derivative direction out of range");
    }
    switch(type)
    {
        case DiffType::backward:
            out = in - Cshift(in, mu, -1);
            break;
        case DiffType::forward:
            out = Cshift(in, mu, 1) - in;
            break;
        case DiffType::central:
            out = 0.5*(Cshift(in, mu, 1) - Cshift(in, mu, -1));
            break;
        default:
            HADRON_ERROR(Argument, "Derivative type invalid");
            break;
    }
}

template <typename Field>
inline void dmuAcc(Field &out, const Field &in, const unsigned int mu, const DiffType type)
{
    auto & env = Environment::getInstance();

    if (mu >= env.getNd())
    {
        HADRON_ERROR(Range, "Derivative direction out of range");
    }
    switch(type)
    {
        case DiffType::backward:
            out += in - Cshift(in, mu, -1);
            break;
        case DiffType::forward:
            out += Cshift(in, mu, 1) - in;
            break;
        case DiffType::central:
            out += 0.5*(Cshift(in, mu, 1) - Cshift(in, mu, -1));
            break;
        default:
            HADRON_ERROR(Argument, "Derivative type invalid");
            break;
    }
}

inline std::string varName(const std::string name, const unsigned int mu)
{
    return name + "_" + std::to_string(mu);
}

inline std::string varName(const std::string name, const unsigned int mu, 
                           const unsigned int nu)
{
    return name + "_" + std::to_string(mu) + "_" + std::to_string(nu);
}

END_MODULE_NAMESPACE

END_HADRONS_NAMESPACE

#endif // Hadrons_MScalarSUN_Utils_hpp_
