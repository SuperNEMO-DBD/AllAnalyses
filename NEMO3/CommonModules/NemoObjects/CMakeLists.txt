# - CMakeLists.txt script for NemoObjects Module 
#

#----------------------------------------------------------------------------
# Needed includes
#
include_directories(./)


#----------------------------------------------------------------------------
# Glob the main headers and sources
# NB: note the warning in the README about globbing...
#
file(GLOB NEMOOBJECTS_HEADERS NemoObjects/*.h)
file(GLOB NEMOOBJECTS_SOURCES src/*.cpp)

#----------------------------------------------------------------------------
# We need a ROOT dict to be generated, so we use the macro supplied by
# the FindROOT module
#
# NB: WE DON'T ACTUALLY DO THIS FOR NOW AS THE DICTIONARY DOESN'T BUILD
# CORRECTLY...

set(NEMOOBJECTS_LINKDEF_FILE dict/Linkdef.h)
set(NEMOOBJECTS_DICTIONARY_FILE ${PROJECT_BINARY_DIR}/_NemoObjects_dict.cxx)

ROOT_GENERATE_DICTIONARY(
    "${NEMOOBJECTS_HEADERS}"
    "${NEMOOBJECTS_LINKDEF_FILE}" 
    "${NEMOOBJECTS_DICTIONARY_FILE}"
    "${CMAKE_CURRENT_SOURCE_DIR};${Hereward_INCLUDE_DIRS}")

set(NEMOOBJECTS_DICTIONARIES ${PROJECT_BINARY_DIR}/_NemoObjects_dict.cxx)

#----------------------------------------------------------------------------
# Add the library target, force it to be shared
#
add_library(NemoObjects SHARED ${NEMOOBJECTS_SOURCES}
${NEMOOBJECTS_HEADERS} ${STORABLECONTAINERS_HEADERS} ${CLHEP_LIBRARIES})

# It uses, ROOT libraries, so we must link to them
# Note that this results in significant overlinking...
# Needs a better componetized FindROOT..
target_link_libraries(NemoObjects NemoObjects_dict ${Hereward_LIBRARIES} ${CLHEP_LIBRARIES})

add_library(NemoObjects_dict SHARED ${NEMOOBJECTS_DICTIONARIES})
target_link_libraries(NemoObjects_dict ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Install the library and headers
# Note that we export the library for use by other projects
#
install(TARGETS NemoObjects NemoObjects_dict
    EXPORT SNemoSoftLibraryDepends    
    DESTINATION ${INSTALL_LIB_DIR})

export(TARGETS NemoObjects NemoObjects_dict
    APPEND FILE "${PROJECT_BINARY_DIR}/SNemoSoftLibraryDepends.cmake")

install(FILES ${NEMOOBJECTS_HEADERS} DESTINATION
    ${INSTALL_INCLUDE_DIR}/NemoObjects)


