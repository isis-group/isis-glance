find_path(LibOil_INCLUDE_DIR "liboil/liboil.h" PATH_SUFFIXES "liboil" "liboil-0.3")
find_library(LibOil_LIBRARY NAMES "oil-0.3")
include_directories(${LibOil_INCLUDE_DIR})

add_executable( ioFactoryTest ioFactoryTest.cpp )

target_link_libraries(ioFactoryTest ${Boost_LIBRARIES} ${ISIS_LIB} isis_glance ${LibOil_LIBRARY}  )

add_test(NAME ioFactoryTest COMMAND ioFactoryTest)