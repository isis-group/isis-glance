add_executable( imagePropertiesTest imageProperties.cpp )

target_link_libraries( imagePropertiesTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance  )

############################################################
# add ctest targets
############################################################

add_test(NAME imagePropertiesTest COMMAND imagePropertiesTest)