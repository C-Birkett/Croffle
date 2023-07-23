add_library(${MY_LIBRARY}
  Application.h
  Application.cpp
  Camera.h
  Camera.cpp
  CameraManager.h
  CameraManager.cpp
  GuiManager.h
  GuiManager.cpp
  KeypressManager.h
  KeypressManager.cpp
  PlayerController.h
  PlayerController.cpp
)

target_include_directories(${MY_LIBRARY}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${MY_LIBRARY}
    ${OGRE_LIBRARIES}
)
