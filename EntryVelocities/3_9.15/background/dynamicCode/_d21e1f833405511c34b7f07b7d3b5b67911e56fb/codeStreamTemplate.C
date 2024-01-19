/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) YEAR AUTHOR, AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Description
    Template for use with codeStream.

\*---------------------------------------------------------------------------*/

#include "dictionary.H"
#include "Ostream.H"
#include "Pstream.H"
#include "unitConversion.H"

//{{{ begin codeInclude
#include "fvCFD.H"
//}}} end codeInclude

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

extern "C" void codeStream_d21e1f833405511c34b7f07b7d3b5b67911e56fb(Ostream& os, const dictionary& dict)
{
//{{{ begin code
    const IOdictionary& d = static_cast<const IOdictionary&>(dict.parent().parent());
                    const fvMesh& mesh = refCast<const fvMesh>(d.db());
                    const label id = mesh.boundary().findPatchID("inlet");
                    const fvPatch& patch = mesh.boundary()[id];
    
                    //vectorField U(mesh.boundary()[id].size(), vector(0, 0, 0));
                    vectorField U(patch.size(), vector(0, 0, 0));
    
                    forAll(U, i)
                    {
                        const scalar z = patch.Cf()[i][2];
                        const scalar depth 	= 1.4;		//水深
                        const scalar U0 	= -1.525;	//风速和最上层流速
                        const scalar slope 	= U0/depth;	//变化率
    
                        U[i] = vector(U0, 0., 0.);
    
                        if (z <= 0)
                        {
                            U[i] = vector(U0+z*slope, 0, 0.);
                        }
                    }
    
                    U.writeEntry("", os);
//}}} end code
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

