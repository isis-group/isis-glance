add_executable( ioFactoryTest ioFactoryTest.cpp )

target_link_libraries(ioFactoryTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance  )

add_test(NAME ioFactoryTest COMMAND ioFactoryTest)