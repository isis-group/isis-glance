add_executable( imagePropertiesStressTest imagePropertiesStressTest.cpp )
add_executable( imageStressTest imageStressTest.cpp )

target_link_libraries( imagePropertiesStressTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance )
target_link_libraries( imageStressTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance )