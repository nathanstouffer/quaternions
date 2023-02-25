# quaternions

This repo contains some code that I wrote exploring quaternions.
Note that the contents of */src/deps/* are from a course that I took on computer graphics taught by Dr. David Millman at Montana State University (big thank you to Dave for teaching me graphics!).
Also a huge thank you goes out to Dr. Jarek Kwapisz for taking the time to go through some quaternion theory in his algebra class!
Thanks to [this](https://ezgif.com/video-to-gif) website for converting mp4 files to gifs to dislay in this README.

In the */src/* directory, there are two subdirectories with code that I wrote: */su2/* and */so3/*.

## SU(2)

*/su2/* contains code that keeps the quaternions in their full glory as the set $SU(2)$, a subset of the ring of 2x2 matrices over $\mathbb C$.
This code is written for things that involve only pure rotations.
Here is a gif of a torus periodically rotating about $(1,1,1) \in \R^3$.
Sorry about the jittery frame rate, it was the best I could get on the readme.
If you want a smoother video, check out the mp4 file.

![rotating torus](/output/su2/torus_2s_25fps.gif)

## ijk

*/ijk/* implements quaternions as the classical vector space over 1, i, j, and k.
This is more computationally efficient and easier to normalize back to a unit quaternion.
Additionally, it is very extensible, since we can map a quaternion to $SO(3)$ and then compose rotations really nicely with scaling and translations.
I chose not to make any graphics since they would pretty much be the same as $SU(2)$.

We can also map $SU(2)$ to $SO(3)$ but I think that it is nice to keep $SU(2)$ all on its own for beauty's sake and separately implement the unit ijk-quaternions with the map to $SO(3)$.
