cmake_minimum_required(VERSION 3.5)
project(angryDriverServer)
set(CMAKE_CXX_STANDARD 11)

# Box2D physics engine.
option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" ON)
set(BOX2D_BUILD_EXAMPLES OFF)
add_subdirectory(Box2D/Box2D)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D)

# libwebsockets dependency.
add_subdirectory(libwebsockets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libwebsockets/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libwebsockets/)
include_directories(src/server/transport)

# rapidjson dependency.
add_definitions(-DRAPIDJSON_HAS_STDSTRING=1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include)


set(SOURCE_FILES
        src/main.cpp
        src/server/utils/Logger.cpp
        src/server/utils/Logger.h
        src/server/transport/WSServer.cpp
        src/server/transport/WSServer.h
        src/server/transport/Client.h
        src/server/game/Object.h
        src/server/game/Engine.cpp
        src/server/game/Engine.h
        src/server/game/Level.cpp
        src/server/game/Level.h
        src/server/game/PhysicsObject.cpp
        src/server/game/PhysicsObject.h
        src/server/game/physics/Model.h
        src/server/game/physics/Model.cpp
        src/server/transport/WSClient.h
        src/server/game/Player.cpp
        src/server/game/Player.h
        src/server/game/physics/Box.cpp
        src/server/game/physics/Box.h
        src/server/game/Object.cpp
        src/server/game/physics/car/CarTire.h
        src/server/game/physics/car/CarTire.cpp
        src/server/game/physics/car/CarBody.h
        src/server/game/physics/car/CarBody.cpp)

add_executable(angryDriverServer ${SOURCE_FILES})
target_link_libraries(angryDriverServer websockets Box2D)