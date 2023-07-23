cmake_minimum_required(VERSION 3.0.0)
project(Croffle VERSION 0.1.0)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd intellisense

#include(CTest)
#enable_testing()

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

# important names
set(APPNAME ${PROJECT_NAME}) # = Croffle
set(MY_LIBRARY Game)

# setup file structure
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${ROOT_DIR}/src)
set(OBJ_DIR ${ROOT_DIR}/obj)
set(LIB_DIR ${OBJ_DIR}/lib)
set(BIN_DIR ${ROOT_DIR}/bin)
set(RES_DIR ${ROOT_DIR}/res)
set(MAP_DIR ${ROOT_DIR}/map)
set(OGRE_DIR ${ROOT_DIR}/ogre3d)

add_definitions(-DRES_DIR="${RES_DIR}")

# setup Ogre 
find_package(OGRE 
    REQUIRED
    COMPONENTS Bites
    CONFIG
    PATHS ${OGRE_DIR}
)

set(OGRE_CONFIG_DIR ${BIN_DIR})
message(OGRE_CONFIG_DIR=${OGRE_CONFIG_DIR})
message(OGRE_LIBRARIES = ${OGRE_LIBRARIES})

add_executable(${APPNAME} ./main.cpp)

add_subdirectory(${SRC_DIR})

target_link_libraries(${APPNAME}
    ${OGRE_LIRARIES}
    ${MY_LIBRARY}
)
