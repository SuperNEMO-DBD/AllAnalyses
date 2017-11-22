# - Basic CMake setup
# Check version meets ou requirements
# Declare project, which will configure compiler for us
cmake_minimum_required(VERSION 3.3)
project(SensitivityModule)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GSL_VERSION "2.4")

find_package(Falaise REQUIRED)

# Ensure our code can see the Falaise headers
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/falaise)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/boost/1.63.0/include/)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/bayeux/3.0.0/include/bayeux/)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/camp/0.8.0/include/)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/clhep/2.1.3.1/include)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/falaise/3.0.0/include/)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/gsl/2.4/include/)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/bayeux/3.0.0/include/)
include_directories(/Users/Lauren/CadfaelBrew/Cellar/root6/6.08.06/include/root/)

link_directories(/Users/Lauren/CadfaelBrew/Cellar/falaise/3.0.0/lib)

# Build a dynamic library from our sources
add_library(SensitivityModule SHARED SensitivityModule.h SensitivityModule.cpp)
target_link_libraries(SensitivityModule PUBLIC Falaise)
# Apple linker requires dynamic lookup of symbols, so we
# add link flags on this platform
if(APPLE)
set_target_properties(SensitivityModule
PROPERTIES LINK_FLAGS "-undefined dynamic_lookup"
)
endif()
