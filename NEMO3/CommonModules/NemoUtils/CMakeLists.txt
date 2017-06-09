# - CMakeLists.txt script for NemoUtils Module 
#

#----------------------------------------------------------------------------
# Needed includes
#
include_directories(./)

#----------------------------------------------------------------------------
# Glob the main headers and sources
# NB: note the warning in the README about globbing...
#
file(GLOB NEMOUTILS_HEADERS NemoUtils/*.h)
file(GLOB NEMOUTILS_SOURCES src/*.cpp)

#----------------------------------------------------------------------------
# Add the library target, force it to be shared
#
add_library(NemoUtils SHARED ${NEMOUTILS_SOURCES}
${NEMOUTILS_HEADERS}
 ${CLHEP_LIBRARIES})
target_link_libraries(NemoUtils ${Hereward_LIBRARIES} ${CLHEP_LIBRARIES})

#----------------------------------------------------------------------------
# Install the library and headers
# Note that we export the library for use by other projects
#
install(TARGETS NemoUtils 
    EXPORT SNemoSoftLibraryDepends    
    DESTINATION ${INSTALL_LIB_DIR})


install(FILES ${NEMOUTILS_HEADERS} DESTINATION
    ${INSTALL_INCLUDE_DIR}/NemoUtils)


