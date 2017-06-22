#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(sn_hc_simu_analysis VERSION "0.0.1")

set(PROJECT_CXX_FLAGS "-Wall -Wextra -Wshadow -pedantic -Werror -Wfatal-errors")

# - Versioning
set(sn_hc_simu_analysis_VERSION_MAJOR 0)
set(sn_hc_simu_analysis_VERSION_MINOR 1)
set(sn_hc_simu_analysis_VERSION_PATCH 0)
set(sn_hc_simu_analysis_VERSION
  "${sn_hc_simu_analysis_VERSION_MAJOR}.${sn_hc_simu_analysis_VERSION_MINOR}.${sn_hc_simu_analysis_VERSION_PATCH}")

# - Prepend flags to any preexisting ones, allowing user
#   to supply additional ones or override if required
set(CMAKE_CXX_FLAGS "${PROJECT_CXX_FLAGS} ${CMAKE_CXX_FLAGS}")

# - C++ Standard
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-----------------------------------------------------------------------
# - Standard UNIX Tool install paths, including relative paths for use
# by applications requiring resources
include(GNUInstallDirs)

#-----------------------------------------------------------------------
# Falaise is the main external dependency, and we know it will additionally
# search for and provide compatible versions of:
# - Bayeux
# - Boost
# - GSL
# - ROOT
# - Geant4

find_package(Falaise 3.0.0
  REQUIRED
  )

# # Ensure our code can see the Falaise headers
# include_directories(${FALAISE_BUILD_PREFIX}/include)
# include_directories(${FALAISE_BUILD_PREFIX}/include/falaise)

include_directories(${PROJECT_SOURCE_DIR}/source)

set(EXECUTABLE_OUTPUT_PATH BuildProducts/bin/)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#

set(HEADERS
  source/data_statistics_simu.hpp
  source/hc_constants.hpp
  )

set(SOURCES
  source/data_statistics_simu.cpp
  )

set(PROGRAMS
  programs/hc_analysis_data.cxx
  programs/hc_sort_data.cxx
  )

foreach( progfile ${PROGRAMS} )

  get_filename_component( progname "${progfile}" NAME_WE)

  # To add header if wanted :
  #set(_programname "fecom-${_programname}")

  add_executable(${progname}
    ${progfile}
    ${HEADERS} ${SOURCES}
    )

target_link_libraries( ${progname} Falaise::Falaise)

endforeach()
