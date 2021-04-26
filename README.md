# quaternions

This repo contains some code that I wrote exploring quaternions.
Note that the contents of */deps* are from a course that I took on computer graphics taught by Dr. David Millman at Montana State University.

In the */src/* directory, there are two subdirectories: */su2/* and */so3/*.

*/su2/* contains code that keeps the quaternions in their full glory as the set SU(2), a subset of the ring of 2 by 2 matrices over the complex numbers.
This code is written for things that involve only pure rotations.

*/so3/* implements quaternions as the classical vector space over 1, i, j, and k.
This is more computationally efficient and easier to normalize back to a unit quaternion.
Additionally, it is very extensible, since we can map a quaternion to SO(3) and then compose rotations really nicely with scaling and translations.
