/*
transforms.cpp, part of ogrubik, <http://github.com/stoffie/ogrubik>

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include "transforms.h"

namespace ogrubik {

Ogre::Quaternion Transforms::getCornerClockwiseTwist(int x, int y, int z)
{
	Ogre::Quaternion q =
		Ogre::Quaternion(Ogre::Degree(-90 * x), Ogre::Vector3::UNIT_X) +
		Ogre::Quaternion(Ogre::Degree(-90 * y), Ogre::Vector3::UNIT_Y) +
		Ogre::Quaternion(Ogre::Degree(-90 * z), Ogre::Vector3::UNIT_Z);
	return q * q;
}

// NOTE: using this function is not the best way to describe all the permutations,
// but once they have been all written, ther's no sense changing them
Ogre::Quaternion Transforms::getRotation(int x, int y, int z)
{
	Ogre::Quaternion q =
		Ogre::Quaternion(Ogre::Degree(x), Ogre::Vector3::UNIT_X) *
		Ogre::Quaternion(Ogre::Degree(y), Ogre::Vector3::UNIT_Y) *
		Ogre::Quaternion(Ogre::Degree(z), Ogre::Vector3::UNIT_Z);
	return q;
}

const Ogre::Quaternion
Transforms::cornerClockwiseTwists[Cube::NumberOfCornerCubies] = {
	getCornerClockwiseTwist(+1, +1, +1), // UFR
	getCornerClockwiseTwist(-1, +1, +1), // UFL
	getCornerClockwiseTwist(-1, +1, -1), // UBL
	getCornerClockwiseTwist(+1, +1, -1), // UBR
	getCornerClockwiseTwist(+1, -1, +1), // DFR
	getCornerClockwiseTwist(-1, -1, +1), // DFL
	getCornerClockwiseTwist(-1, -1, -1), // DBL
	getCornerClockwiseTwist(+1, -1, -1)  /* DBR */ };

const Ogre::Quaternion
Transforms::edgeTwists[Cube::NumberOfEdgeCubies] = {
	getRotation( 90, 180,	0),
	getRotation(180,   0,  90),
	getRotation(-90, 180,	0),
	getRotation(180,   0, -90),
	getRotation(-90, 180,	0),
	getRotation(180,   0, -90),
	getRotation( 90, 180,	0),
	getRotation(180,   0,  90),
	// Middle slice edges begin here
	getRotation(180,  90,	0),
	getRotation(180, -90,	0),
	getRotation(180,  90,	0),
	getRotation(180, -90,	0)};

const Ogre::Quaternion
Transforms::cornerPermutations[Cube::NumberOfCornerCubies][Cube::NumberOfCornerCubies] =
{
	{
		getRotation(  0,   0, 0),
		getRotation(  0, -90, 0),
		getRotation(  0, 180, 0),
		getRotation(  0,  90, 0),
		getRotation(180,  90, 0),
		getRotation(180, 180, 0),
		getRotation(180, -90, 0),
		getRotation(180,   0, 0)
	},{
		getRotation(  0,  90, 0),
		getRotation(  0,   0, 0),
		getRotation(  0, -90, 0),
		getRotation(  0, 180, 0),
		getRotation(180, 180, 0),
		getRotation(180, -90, 0),
		getRotation(180,   0, 0),
		getRotation(180,  90, 0)
	},{
		getRotation(  0, 180, 0),
		getRotation(  0,  90, 0),
		getRotation(  0,   0, 0),
		getRotation(  0, -90, 0),
		getRotation(180, -90, 0),
		getRotation(180,   0, 0),
		getRotation(180,  90, 0),
		getRotation(180, 180, 0)
	},{
		getRotation(  0, -90, 0),
		getRotation(  0, 180, 0),
		getRotation(  0,  90, 0),
		getRotation(  0,   0, 0),
		getRotation(180,   0, 0),
		getRotation(180,  90, 0),
		getRotation(180, 180, 0),
		getRotation(180, -90, 0)
	},{
		getRotation(180,  90, 0),
		getRotation(180, 180, 0),
		getRotation(180, -90, 0),
		getRotation(180,   0, 0),
		getRotation(0,	   0, 0),
		getRotation(0,	 -90, 0),
		getRotation(0,	 180, 0),
		getRotation(0,	  90, 0)
	},{
		getRotation(180, 180, 0),
		getRotation(180, -90, 0),
		getRotation(180,   0, 0),
		getRotation(180,  90, 0),
		getRotation(  0,  90, 0),
		getRotation(  0,   0, 0),
		getRotation(  0, -90, 0),
		getRotation(  0, 180, 0)
	},{
		getRotation(180, -90, 0),
		getRotation(180,   0, 0),
		getRotation(180,  90, 0),
		getRotation(180, 180, 0),
		getRotation(  0, 180, 0),
		getRotation(  0,  90, 0),
		getRotation(  0,   0, 0),
		getRotation(  0, -90, 0)
	},{
		getRotation(180,   0, 0),
		getRotation(180,  90, 0),
		getRotation(180, 180, 0),
		getRotation(180, -90, 0),
		getRotation(  0, -90, 0),
		getRotation(  0, 180, 0),
		getRotation(  0,  90, 0),
		getRotation(  0,   0, 0)
	}
};

const Ogre::Quaternion
Transforms::edgePermutations[Cube::NumberOfEdgeCubies][Cube::NumberOfEdgeCubies] =
{
	{
		getRotation(  0,   0,	0),
		getRotation(  0, -90,	0),
		getRotation(  0, 180,	0),
		getRotation(  0,  90,	0),
		getRotation(180, 180,	0),
		getRotation(180, -90,	0),
		getRotation(180,   0,	0),
		getRotation(180,  90,	0),

		getRotation(  0,   0, -90),
		getRotation(  0,   0,  90),
		getRotation(  0, 180, -90),
		getRotation(  0, 180,  90),
	},{
		getRotation(  0,  90,	0),
		getRotation(  0,   0,	0),
		getRotation(  0, -90,	0),
		getRotation(  0, 180,	0),
		getRotation(180, -90,	0),
		getRotation(180,   0,	0),
		getRotation(180,  90,	0),
		getRotation(180, 180,	0),

		getRotation( 90,   0, -90),
		getRotation(-90,   0,  90),
		getRotation( 90,   0,  90),
		getRotation(-90,   0, -90),
	},{
		getRotation(  0, 180,	0),
		getRotation(  0,  90,	0),
		getRotation(  0,   0,	0),
		getRotation(  0, -90,	0),
		getRotation(180,   0,	0),
		getRotation(180,  90,	0),
		getRotation(180, 180,	0),
		getRotation(180, -90,	0),

		getRotation(  0, 180,  90),
		getRotation(  0, 180, -90),
		getRotation(  0,   0,  90),
		getRotation(  0,   0, -90)
	},{
		getRotation(  0, -90,	0),
		getRotation(  0, 180,	0),
		getRotation(  0,  90,	0),
		getRotation(  0,   0,	0),
		getRotation(180,  90,	0),
		getRotation(180, 180,	0),
		getRotation(180, -90,	0),
		getRotation(180,   0,	0),

		getRotation(-90,   0, -90),
		getRotation( 90,   0,  90),
		getRotation(-90,   0,  90),
		getRotation( 90,   0, -90)
	},{
		getRotation(180, 180,	0),
		getRotation(180, -90,	0),
		getRotation(180,   0,	0),
		getRotation(180,  90,	0),
		getRotation(  0,   0,	0),
		getRotation(  0, -90,	0),
		getRotation(  0, 180,	0),
		getRotation(  0,  90,	0),

		getRotation(  0,   0,  90),
		getRotation(  0,   0, -90),
		getRotation(  0, 180,  90),
		getRotation(  0, 180, -90)
	},{
		getRotation(180, -90,	0),
		getRotation(180,   0,	0),
		getRotation(180,  90,	0),
		getRotation(180, 180,	0),
		getRotation(  0,  90,	0),
		getRotation(  0,   0,	0),
		getRotation(  0, -90,	0),
		getRotation(  0, 180,	0),

		getRotation(-90,   0,  90),
		getRotation( 90,   0, -90),
		getRotation(-90,   0, -90),
		getRotation( 90,   0,  90)
	},{
		getRotation(180,   0,	0),
		getRotation(180,  90,	0),
		getRotation(180, 180,	0),
		getRotation(180, -90,	0),
		getRotation(  0, 180,	0),
		getRotation(  0,  90,	0),
		getRotation(  0,   0,	0),
		getRotation(  0, -90,	0),

		getRotation(  0, 180, -90),
		getRotation(  0, 180,  90),
		getRotation(  0,   0, -90),
		getRotation(  0,   0,  90)
	},{
		getRotation(180,  90,	0),
		getRotation(180, 180,	0),
		getRotation(180, -90,	0),
		getRotation(180,   0,	0),
		getRotation(  0, -90,	0),
		getRotation(  0, 180,	0),
		getRotation(  0,  90,	0),
		getRotation(  0,   0,	0),

		getRotation( 90,   0,  90),
		getRotation(-90,   0, -90),
		getRotation( 90,   0, -90),
		getRotation(-90,   0,  90)
	},{
		getRotation(  0,   0,  90),
		getRotation(  0, -90,  90),
		getRotation(  0, 180,  90),
		getRotation(  0,  90,  90),
		getRotation(  0,   0, -90),
		getRotation(  0, -90, -90),
		getRotation(  0, 180, -90),
		getRotation(  0,  90, -90),

		getRotation(  0,   0,	0),
		getRotation(  0,   0, 180),
		getRotation(  0, 180,	0),
		getRotation(180,   0,	0)
	},{
		getRotation(  0,   0, -90),
		getRotation(  0, -90, -90),
		getRotation(  0, 180, -90),
		getRotation(  0,  90, -90),
		getRotation(  0,   0,  90),
		getRotation(  0, -90,  90),
		getRotation(  0, 180,  90),
		getRotation(  0,  90,  90),

		getRotation(  0,   0, 180),
		getRotation(  0,   0,	0),
		getRotation(180,   0,	0),
		getRotation(  0, 180,	0)
	},{
		getRotation(180,   0,  90),
		getRotation(  0,  90, -90),
		getRotation(  0,   0, -90),
		getRotation(  0, -90, -90),
		getRotation(180,   0, -90),
		getRotation(  0,  90,  90),
		getRotation(  0,   0,  90),
		getRotation(  0, -90,  90),

		getRotation(  0, 180,	0),
		getRotation(180,   0,	0),
		getRotation(  0,   0,	0),
		getRotation(  0,   0, 180)
	},{
		getRotation(180,   0, -90),
		getRotation(  0,  90,  90),
		getRotation(  0,   0,  90),
		getRotation(-90, -90,	0),
		getRotation(180,   0,  90),
		getRotation(-90,  90,	0),
		getRotation(  0,   0, -90),
		getRotation( 90, -90,	0),

		getRotation(180,   0,	0),
		getRotation(  0, 180,	0),
		getRotation(  0,   0, 180),
		getRotation(  0,   0,	0)
	}
};

} // namespace ogrubik
