# FindISISGlance
# 
# This script search the ISIS-Glance library libsisis_glance.so and the corresponding header files.
# It also looks for the ISIS-Glance build configuration file.
#
#

# Provided variables:
#
# ISIS_GLANCE_FOUND             TRUE if all ISIS-Glance libraries were found, FALSE otherwise.
# ISIS_GLANCE_INCLUDE_DIR       the path to the header directory
# ISIS_GLANCE_SHARED_LIB        the isis shared library (e.g. libisis_glance.so)
# ISIS_GLANCE_STATIC_LIB        the isis static linked library (e.g. libisis_glance.a)
# ISIS_GLANCE_WIDGET_DIR        the path where the widget plugins reside
#
# This script reads the configuration file isis_glance_cfg.cmake provided
# by the isis core package.
#

FIND_PATH(CFG_FILE isis_glance_cfg.cmake
  PATH ./
  DOC "The cmake configuration file containing the isis glance library build settings.")

IF(${CFG_FILE})
  INCLUDE(${CFG_FILE})
ELSE(${CFG_FILE})
  MESSAGE(SEND_ERROR "Error, cannot find isis glance configuration file.")
ENDIF(${CFG_FILE})
