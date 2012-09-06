project(DotSceneManager)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

################# Compiler & linker settings
add_definitions(-DOGRE_GCC_VISIBILITY)

if(CMAKE_BUILD_TYPE)
  string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)

  if(CMAKE_BUILD_TYPE_TOLOWER STREQUAL debug)
    add_definitions(-D_DEBUG  -DDEBUG -g -Wall) 
  endif(CMAKE_BUILD_TYPE_TOLOWER STREQUAL debug)

  if(CMAKE_BUILD_TYPE_TOLOWER STREQUAL release)
    add_definitions(-DNDEBUG)
  endif(CMAKE_BUILD_TYPE_TOLOWER STREQUAL release)
endif(CMAKE_BUILD_TYPE)

include (CheckIncludeFileCXX)
include (FindPkgConfig)

if(UNIX)
  find_package(PkgConfig REQUIRED)
  find_package(Gettext)
  
  PKG_CHECK_MODULES(OGRE REQUIRED OGRE)

  if (OGRE_Terrain_FOUND)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES})  
    message(STATUS "Found OGRE_Terrain: ${OGRE_Terrain_LIBRARIES}")
  else (OGRE_Terrain_FOUND)
    message(WARNING "OgreTerrain Library not found.")
  endif(OGRE_Terrain_FOUND)

  if (OGRE_Paging_FOUND)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Paging_LIBRARIES})  
    message(STATUS "Found OGRE_Paging: ${OGRE_Paging_LIBRARIES}")
  else (OGRE_Paging_FOUND)
    message(WARNING "OgrePaging Library not found.")
  endif(OGRE_Paging_FOUND)

  find_library(BOOSTTHREAD_LIBRARIES NAMES boost_thread-mt)
  find_library(TINYXML_LIBRARIES NAMES tinyxml)

endif(UNIX)

include_directories(
  ${OGRE_INCLUDE_DIRS}
  include  
)

link_directories(${OGRE_LIBRARY_DIRS})

################# Project configuration
aux_source_directory(src DOTSCENEMANAGER_SRCS)

add_library(${PROJECT_NAME} SHARED ${DOTSCENEMANAGER_SRCS})
target_link_libraries(${PROJECT_NAME} 
    ${OGRE_LIBRARIES}  
    ${BOOSTTHREAD_LIBRARIES}
    ${TINYXML_LIBRARIES}
) 

################# Runtime configuration

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
  ${CMAKE_CURRENT_SOURCE_DIR}/media
  ${CMAKE_CURRENT_BINARY_DIR}/media
)

################# Process Templates
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc)

################# Installation settings

install(
  DIRECTORY ${OGRE_INCLUDE_DIRS}
  DESTINATION in${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".git" EXCLUDE
)

install(
  DIRECTORY media
  DESTINATION share/${PROJECT_NAME}
  PATTERN ".git" EXCLUDE
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION /usr/lib/pkgconfig
)


