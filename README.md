### Angry drivers game's server
Server parts of 2D multiplayer car fighting  simulator 

WIP

#### Implementation details:
   Network communication is implemented as JSON over WebSocket (libwebsocket) for simplicity. 
   It inefficient but works on LAN pretty well. 
   Binary protocol and delta compression is necessary to implement here.
   
   Physics world is simulated by Box2D engine.

#### Building:
    git clone 
    git submodule update --init
    cmake .
    make
    
#### Running:
    ./angryDriverServer
    
Use --help options to see available options
    
    
#### Client side
![Demo](clientTest/demo.gif)

Client side is just dummy for testing. Open clientTest/index.html in your browser to try. 
Use WASD to control your car.

