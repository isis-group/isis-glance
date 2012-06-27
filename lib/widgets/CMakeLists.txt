############################################################
# The ISIS-glance project
#
# CMake configuration file of the ISIS-glance widget plugins
#
# Author: Erik Tuerke <etuerke@googlemail.com>
# Date: Wed, 27 Jun 2012 10:27:10 +0200
#
############################################################

############################################################
# include the ISIS-glance core header files
############################################################
include_directories(${CMAKE_SOURCE_DIR}/lib/core)

############################################################
# add global options
############################################################
option(ISIS_GLANCE_WIDGET_PLUGIN_QT "Enable Qt widget plugin" ON )


############################################################
# QT widget plugin
############################################################
if( ISIS_GLANCE_WIDGET_PLUGIN_QT )
add_subdirectory(qt_widget)
endif( ISIS_GLANCE_WIDGET_PLUGIN_QT )