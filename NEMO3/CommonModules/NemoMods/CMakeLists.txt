# - CMakeLists.txt script for NemoMods Module 
#
#----------------------------------------------------------------------------
# Needed includes
#
include_directories(${Hereward_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Glob the main headers and sources
# NB: note the warning in the README about globbing...
#
file(GLOB NEMOMODS_HEADERS NemoMods/*.h)
file(GLOB NEMOMODS_SOURCES src/*.cpp)

#----------------------------------------------------------------------------
# Add the library target, force it to be shared
#
add_library(NemoMods SHARED ${NEMOMODS_SOURCES} ${NEMOMODS_HEADERS})
target_link_libraries(NemoMods NemoObjects SuperNemoTracking ${MYSQL_CLIENT_LIBS}
${N3DB_LIBS} $ENV{FORTRAN_2_C_LIB} gfortran)

#----------------------------------------------------------------------------
# Install the library and headers
# Note that we export the library for use by other projects
#
install(TARGETS NemoMods 
    EXPORT SNemoSoftLibraryDepends    
    DESTINATION ${INSTALL_LIB_DIR})

export(TARGETS NemoMods 
    APPEND FILE "${PROJECT_BINARY_DIR}/SNemoSoftLibraryDepends.cmake")

install(FILES ${NEMOMODS_HEADERS} DESTINATION
    ${INSTALL_INCLUDE_DIR}/NemoMods)
