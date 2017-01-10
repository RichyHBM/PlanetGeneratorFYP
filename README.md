PlanetGeneratorFYP
------------------

![planet-8](https://cloud.githubusercontent.com/assets/5472275/13028300/1e75a414-d263-11e5-88a0-9ccc77c22ab9.png)

On OSX you will need to install the dependencies: brew install sfml AntTweakBar

Ubuntu requires: sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev libsfml-dev libpthread-stubs0-dev
Also, AntTweakBar, 64 bit libs are included

This was developed as part of my final year project during the first 6 months of my final year at university. It consists of various modules, including: mesh generation, noise generation, texturing, lighting, level of detail, camera and movement systems, atmosphere simulation and, on the correct hardware, 3d/VR display.

The sphere generation is done by subdividing a cube into a number of segments and normalizing all the vertices to turn the cube into a sphere. A "noise" amount is generated and applied to the length of each vertex to achieve a more realistic planet shape.

Texturing and lighting are applied via shaders, the variables of which can be controlled using the user interface. The level of detail is achieved via quadtree subdivision of the planets mesh.

The system was developed to run using a variety of controllers via a simple interface structure. The requirements for this came for the necessity for the program to run on a 3d projection system, where the scene is rendered to each projector with a small variation in its camera in order to achieve 3d display, and where just using a mouse & keyboard wouldn't be possible.

![terrain-1](https://cloud.githubusercontent.com/assets/5472275/13028309/1e8e4f50-d263-11e5-9815-e03173cf4580.png)
![terrain-2](https://cloud.githubusercontent.com/assets/5472275/13028311/1e908afe-d263-11e5-8f51-72e6e97fdeba.png)
![terrain-3](https://cloud.githubusercontent.com/assets/5472275/13028308/1e8e0400-d263-11e5-8169-e4d253bb4f08.png)
![planet-1](https://cloud.githubusercontent.com/assets/5472275/13028295/1e5dc632-d263-11e5-8ec1-e56825be3c29.png)
![planet-2](https://cloud.githubusercontent.com/assets/5472275/13028297/1e5dfc9c-d263-11e5-9e5a-7b45bde98897.png)
![planet-3](https://cloud.githubusercontent.com/assets/5472275/13028296/1e5df6a2-d263-11e5-9450-005d9c001f90.png)
![planet-4](https://cloud.githubusercontent.com/assets/5472275/13028294/1e5d2358-d263-11e5-9b53-60ef31e737ee.png)
![planet-5](https://cloud.githubusercontent.com/assets/5472275/13028299/1e60d39a-d263-11e5-9aa9-53a68b73be21.png)
![planet-6](https://cloud.githubusercontent.com/assets/5472275/13028298/1e606950-d263-11e5-9f38-2efcf5a981b7.png)
![planet-7](https://cloud.githubusercontent.com/assets/5472275/13028302/1e763604-d263-11e5-83c7-33ef787ee217.png)
![planet-9](https://cloud.githubusercontent.com/assets/5472275/13028301/1e7627d6-d263-11e5-8e20-56e879f5dc00.png)
![planet-10](https://cloud.githubusercontent.com/assets/5472275/13028303/1e77b628-d263-11e5-836e-a65e75f169af.png)
![planet-11](https://cloud.githubusercontent.com/assets/5472275/13028304/1e790582-d263-11e5-98d3-c70c3dcf9529.png)
![planet-12](https://cloud.githubusercontent.com/assets/5472275/13028305/1e79701c-d263-11e5-83d2-3b63698ad84c.png)
![planet-13](https://cloud.githubusercontent.com/assets/5472275/13028307/1e8db770-d263-11e5-9156-90f3a7e6eef5.png)
![planet-14](https://cloud.githubusercontent.com/assets/5472275/13028306/1e8b6f38-d263-11e5-995c-3d6c1656c6e7.png)
![planet-15](https://cloud.githubusercontent.com/assets/5472275/13028310/1e8ecf84-d263-11e5-8407-7738b31eecb5.png)
