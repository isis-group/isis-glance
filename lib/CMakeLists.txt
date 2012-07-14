add_subdirectory(core)

option(ISIS_GLANCE_QT4_SUPPORT "Toggles the support for qt4" OFF)

if(ISIS_GLANCE_QT4_SUPPORT)
add_subdirectory(qt4)
endif(ISIS_GLANCE_QT4_SUPPORT)