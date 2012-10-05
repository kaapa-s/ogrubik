#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include <Ogre.h>

#include "kcube/cube.h"

namespace ogrubik {

class Transforms
{
public:
	static const Ogre::Quaternion cornerClockwiseTwists[Cube::NumberOfCornerCubies];
	static const Ogre::Quaternion edgeTwists[Cube::NumberOfEdgeCubies];

	static const Ogre::Quaternion cornerPermutations[Cube::NumberOfCornerCubies][Cube::NumberOfCornerCubies];
	static const Ogre::Quaternion edgePermutations[Cube::NumberOfEdgeCubies][Cube::NumberOfEdgeCubies];

private:
	static Ogre::Quaternion getCornerClockwiseTwist(int x, int y, int z);
	static Ogre::Quaternion getRotation(int x, int y, int z);

};

} // namespace ogrubik

#endif
