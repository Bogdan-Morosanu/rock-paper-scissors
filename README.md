# Rock-Paper-Scissors

Simple rock paper scissors game set in a space themed text adventure.

Has been tested with:
Microsoft (R) C/C++ Optimizing Compiler Version 19.28.29914 for x64
gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)

Contains cmake files to facilitate the build, requires c++14 (mostly for `std::make_unique`)

A docker file is provided that builds an ubuntu system capable of building and running the game as well.
(The game is already compiled in the docker build step, so you just need to start the container and run the game).
```
cd docker
docker build -t rps-docker -f Dockerfile ..
```
then to run
```
docker run -it --rm rps-docker bash
```
and inside the docker run rps with
```
/rps/build/rps
```

Enjoy, and good luck!