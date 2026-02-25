
# WappySav

  

A program for decrypting and encrypting save data from Wappy Dog (DS).

## Building
Building requires the Qt libraries and tools installed, which can be obtained from the installer, or built from source. There are two methods to build WappySav.
(Currently, the program can only be officially compiled for Windows)

 ### 1. Qt Creator(Easiest) 
 Qt Creator is the recommended way of building this app, as it requires little external setup. Just open the CMakeLists.txt file, and build the project with the Release configuration.

 ### 2. Command line
 Building WappySav from the command line can be done using qmake, which is included with Qt. To build, run these commands in the source code directory.
 

     $ (Qt bin Directory)/qmake.exe -makefile 
     
     $ make
     
     $ (Qt bin directory)/windeployqt.exe build/Release



 
