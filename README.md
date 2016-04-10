# SFML-particles
Simple particle simulation made in C++11 with SFML-2.3

Compiling
---------

You will need an installation of SFML compatible with SFML-2.3.2. If you run Debian or derivatives, you can install SFML by doing
```
sudo apt-get install libsfml-dev
```
After you've done that, you can compile by just doing
```
make
```
in the project directory. This will compile with gcc/g++. 

Running
-------

To run the simulation, do
```
./particle-app <particle count>
```
where particle count is the number of particles. If omitted, it will default to 200 000.

Controls
--------

* Holding left click: particles will attract towards the mouse pointer
* Mouse wheel/scrolling: zoom in/out
