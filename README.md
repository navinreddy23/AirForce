# CPPND: AirForce

This is a repo for the Capstone project on Udacity. The game AirForce uses SFML for graphics and audio rendering. 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
  * On MacOS: `brew install cmake`
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SFML > 2.3, recommended = 2.5.1
  * Linux: Install these dependencies on Linux [Click here] (https://gist.github.com/NoobsArePeople2/8086528)
    It is not required to install SFML on Linux by default.
  * MacOS: [Click here for instruction] (https://giovanni.codes/sfml-2-5-1-setup-on-macos-with-clion/)

On most platforms the installation of SFML is not required as it is provided with this repository.

## Basic Build Instructions

Clone this repo. `git clone https://github.com/navinreddy23/AirForce.git`

Navigate to SFML-2.5.1 directory:

1. Make a build directory (if it does not exist) and step-in to it: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Go back to the root of the project: `cd ../../`

This will build the library files required for the game.

1. Make a build directory (if it does not exist) in the top level directory and step-in: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./AirForce`.

## Special Instruction for MacOS

Execution fails on MacOS due to the app being unverified [Visit this link to resolve](https://github.com/hashicorp/terraform/issues/23033)

