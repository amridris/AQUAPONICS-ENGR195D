# Instruction on how to compile and run the code

The team has decided implement the Aquaponics code using **PlatformIO + VS Code**, for its ease of use and library integration. This project will help the next team to be able to immediately install and start coding.

## How to run and edit the code
1. Clone this repositry anywhere in your computer
2. Install and open VS Code
3. Install PlatformIO plugin for VS Code
4. In VS Code, click on file and navigate to open folder. Open the cloned folder in VS Code.
5. VS Code will then automatically parse the platformio.ini file and sets up the project and libraries for this project. 


## How to include Libraries
1. Go to PlatformIO page and check the avaliable libraries
2. Confirm the library you are looking for is in the platformIO library.
3. Once confirmed copy the the name of the library and add it to the platformio.ini file located in the project folder. The library should be added under **lib_deps** line.


## Changing the C++ version
1. Open the platformio.ini file change the following line
build_flags = -std=c++11 
platformio supports c++98 to c++17


