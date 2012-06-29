# add_executable( imagePropertiesTest imageProperties.cpp )
add_executable( threadTest threadTest.cpp )

# target_link_libraries( imagePropertiesTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance  )
target_link_libraries(threadTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance  )

############################################################
# add ctest targets
############################################################

# add_test(NAME imagePropertiesTest COMMAND imagePropertiesTest)
# add_test(NAME threadTest COMMAND threadTest)