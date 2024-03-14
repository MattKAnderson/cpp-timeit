cmake_minimum_required(VERSION 3.11.0)
project("timeit" VERSION 0.1.0 
                 DESCRIPTION "A header only c++ library for timing the execution of functions"
                 HOMEPAGE_URL "https://github.com/MattKAnderson/cpp-timeit"
                 LANGUAGES CXX)

include(GNUInstallDirs)

add_library(timeit INTERFACE)
add_library(timeit::timeit ALIAS timeit)

target_include_directories(
    timeit
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(timeit INTERFACE cxx_std_11)

install(
  TARGETS timeit
  EXPORT ${PROJECT_NAME}_Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "timeit-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  EXPORT ${PROJECT_NAME}_Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
  FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION include)