# CPPND: AirForce

This is a repo for the Capstone project on Udacity. The game AirForce uses SFML for graphics and audio rendering. 
The Player (Hero) has the capabilites to move around and fire Bullets to kill the Enemy. As the Game progresses, the difficulty increases. 
There are Coins to upgrade the powers: lives and Player's speed. These components, such as Game, Player, Coins etc., are divided into classes. 

Game class takes the responsibility of managing the interaction between the different classes. 
Menu class serves as a maintenance/service area during the initial-pause-gameover states. 
Player class exists as long as the Game class exists. 

The aim of the game is to score as high as possible. Enjoy playing AirForce!

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

1. Make a build directory (if it does not exist) in the top level directory and step-in: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./AirForce`.

## Special Instruction for MacOS

Execution fails on MacOS due to the app being "unverified" [Visit this link to resolve](https://github.com/hashicorp/terraform/issues/23033)

