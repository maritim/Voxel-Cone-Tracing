Voxel Cone Tracing
==========

A real-time global illumination implementation using voxel cone tracing based on <a href="https://github.com/maritim/LiteEngine" >Lite Engine</a>. 

<img src="https://raw.githubusercontent.com/maritim/Voxel-Cone-Tracing/gh-pages/vct-result1.png" width="720px"/>
<img src="https://raw.githubusercontent.com/maritim/Voxel-Cone-Tracing/gh-pages/vct-result2.png" width="720px"/>

Project Health
=================

| Service | System | Compiler | Status |
| ------- | ------ | -------- | ------ |
| [Travis CI](https://travis-ci.org/maritim/Voxel-Cone-Tracing)| Linux 64 bits  | GCC 4.8.4 | [![Travis CI](https://travis-ci.org/maritim/Voxel-Cone-Tracing.svg?branch=master)](https://travis-ci.org/maritim/Voxel-Cone-Tracing)
| [AppVeyor](https://ci.appveyor.com/project/maritim/voxel-cone-tracing)| Windows 64 | Visual Studio 2015 | [![AppVeyor](https://ci.appveyor.com/api/projects/status/7w692jvfu0ol6gjy?svg=true)](https://ci.appveyor.com/project/maritim/voxel-cone-tracing)

Debian Install Guide
=================

Get the project from GitHub
--------------------

* Install git

        sudo apt-get install -y git

* Create a local directory for the project

        mkdir VoxelConeTracing && cd VoxelConeTracing
    
* Clone the project

        git clone https://github.com/maritim/Voxel-Cone-Tracing

Install and configure dependecies
--------------------

* Install dependecies

        sudo chmod +x setup.sh
        sudo ./setup.sh
    
Build
-----

* Compile the project

        make CONFIG=RELEASE
        
* Run the application using a prototype scene

        ./Demo.out --startscene Assets/Scenes/Sponza.scene 
