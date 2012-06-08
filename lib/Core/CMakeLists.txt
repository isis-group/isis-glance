

file(GLOB GLANCE_CORE_SRC_FILES "*.cpp")
file(GLOB GLANCE_CORE_HDR_FILES "*.hpp")

############################################################
# Build config
############################################################
set(ISIS_GLANCE_BUILD_PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set(ISIS_GLANCE_BUILD_STATIC OFF CACHE BOOL "enable build of the static library. If OFF a dynamic library will be build and linked." )

############################################################
# the core library shared and static build
############################################################
macro( build_core name type)
    add_library( ${name} ${type} ${GLANCE_CORE_SRC_FILES} )
	target_link_libraries( ${name} ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})
    set_target_properties( ${name} PROPERTIES
		${ISIS_GLANCE_BUILD_PROPERTIES}
		SOVERSION ${ISIS_GLANCE_VERSION_SO}
		VERSION ${ISIS_GLANCE_VERSION_API}
		INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
		OUTPUT_NAME "isis_glance")
    set(target_list ${target_list} ${name})
endmacro( build_core )


#for packaging purpose we want to build both, shared and static with one build_command
#however this capability is not provided by an option in the cmake menu
if(ISIS_GLANCE_BUILD_STATIC_AND_SHARED)
    build_core( isis_glance_static STATIC)
    build_core( isis_glance SHARED)
else(ISIS_GLANCE_BUILD_STATIC_AND_SHARED)
    if(ISIS_GLANCE_BUILD_STATIC)
		build_core( isis_glance STATIC)
    else(ISIS_GLANCE_BUILD_STATIC)
		build_core( isis_glance SHARED)
    endif(ISIS_GLANCE_BUILD_STATIC)
endif(ISIS_GLANCE_BUILD_STATIC_AND_SHARED)

############################################################
# Installation
############################################################

# install libraries
install (TARGETS ${target_list}
  LIBRARY DESTINATION lib COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION lib COMPONENT Development
)

install(FILES ${GLANCE_CORE_HDR_FILES} DESTINATION include/isis-glance COMPONENT Development)

# write configuration file
configure_file(cmake/isis_glance_cfg.cmake.in ${CMAKE_BINARY_DIR}/ISISGlanceConfig.cmake @ONLY)

# install cmake configuration files
install(FILES ${CMAKE_BINARY_DIR}/ISISGlanceConfig.cmake DESTINATION share/isis-glance/cmake COMPONENT Development)