file(GLOB XMA_PLUGIN_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  )

set(XMA_PLUGIN_ALL_SRC
  ${XMA_PLUGIN_FILES}
  )

add_library(xma2plugin SHARED ${XMA_PLUGIN_ALL_SRC})

set_target_properties(xma2plugin PROPERTIES VERSION ${XMA_VERSION_STRING}
  SOVERSION ${XMA_SOVERSION})

install(TARGETS xma2plugin
  LIBRARY DESTINATION ${XMA_INSTALL_DIR}/lib NAMELINK_SKIP
  RUNTIME DESTINATION ${XMA_INSTALL_DIR}/bin
)

install(TARGETS xma2plugin
  ARCHIVE DESTINATION ${XMA_INSTALL_DIR}/lib COMPONENT ${XRT_DEV_COMPONENT}
  LIBRARY DESTINATION ${XMA_INSTALL_DIR}/lib COMPONENT ${XRT_DEV_COMPONENT} NAMELINK_ONLY
)
