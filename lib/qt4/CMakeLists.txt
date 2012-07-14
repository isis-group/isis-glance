file(GLOB ISIS_GLANCE_QT4_HDR_FILES "*.hpp")
set(ISIS_GLANCE_QT4_MOC_HPP widget_component.hpp)
set(ISIS_GLANCE_QT4_SRC_FILES widget_component.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/core)

############################################################
# qt4 stuff
############################################################
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui REQUIRED)

set(QT_USE_QTUITOOLS TRUE)

INCLUDE(${QT_USE_FILE})

QT4_ADD_RESOURCES(ISIS_GLANCE_QT4_RESOURCE_FILES ${RESOURCE_FILES})
qt4_wrap_cpp(ISIS_GLANCE_QT4_MOC_FILES ${ISIS_GLANCE_QT4_MOC_HPP} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)
# QT4_WRAP_UI(vast_UIS_H ${UI_FILES})

############################################################
# the qt4 library shared and static build
############################################################
set(ISIS_GLANCE_QT4_BUILD_PROPERTIES CLEAN_DIRECT_OUTPUT 1)

macro( build_qt4 name type)
    add_library( ${name} ${type} ${ISIS_GLANCE_QT4_SRC_FILES} )
	target_link_libraries( ${name} ${CMAKE_DL_LIBS} ${QT_LIBRARIES})
    set_target_properties( ${name} PROPERTIES
		${ISIS_GLANCE_QT4_BUILD_PROPERTIES}
		SOVERSION ${ISIS_GLANCE_QT4_VERSION_SO}
		VERSION ${ISIS_GLANCE_QT4_VERSION_API}
		INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
		OUTPUT_NAME "isis_glance_qt4")
    set(target_list ${target_list} ${name})
endmacro( build_qt4 )

#for packaging purpose we want to build both, shared and static with one build_command
#however this capability is not provided by an option in the cmake menu
if(ISIS_GLANCE_BUILD_STATIC_AND_SHARED)
    build_qt4( isis_glance_qt4_static STATIC)
    build_qt4( isis_glance_qt4 SHARED)
else(ISIS_GLANCE_BUILD_STATIC_AND_SHARED)
    if(ISIS_GLANCE_BUILD_STATIC)
		build_qt4( isis_glance_qt4 STATIC)
    else(ISIS_GLANCE_BUILD_STATIC)
		build_qt4( isis_glance_qt4 SHARED)
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

install(FILES ${ISIS_GLANCE_QT4_HDR_FILES} DESTINATION include/isis-glance/qt4 COMPONENT Development)
