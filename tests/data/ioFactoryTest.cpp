// #define BOOST_TEST_MODULE IOFactoryTest

// #include <boost/test/unit_test.hpp>

#include "data/io_factory.hpp"

// namespace isis
// {
// namespace glance
// {
// namespace test
// {

// BOOST_AUTO_TEST_CASE( io_factory_test )#
void printPath( const std::string &path) {
	std::cout << "PATH: " << path << std::endl;
}
int main()
{
	//  ENABLE_LOG( isis::glance::data::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	ENABLE_LOG( isis::glance::util::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );

	isis::util::slist paths;
	//  paths.push_back("/SCR/DATA/viewerImages/my_mni.v");
	//  paths.push_back("/SCR/DATA/viewerImages/t1.v");
	//  paths.push_back("/SCR/DATA/viewerImages/BK1T_091112_FLASH_mag.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/BK1T_091126_FLASH_mag.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/BK1T_091203_FLASH_mag.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/out.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/x.v");
	//  paths.push_back("/SCR/DATA/viewerImages/zz.v");
	//  paths.push_back("/SCR/DATA/viewerImages/my_mni.v");
	//  paths.push_back("/SCR/DATA/viewerImages/t1.v");
	//  paths.push_back("/SCR/DATA/viewerImages/BK1T_091112_FLASH_mag.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/BK1T_091126_FLASH_mag.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/BK1T_091203_FLASH_mag.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/out.nii");
	//  paths.push_back("/SCR/DATA/viewerImages/x.v");
	//  paths.push_back("/SCR/DATA/viewerImages/zz.v");
	paths.push_back( "/SCR/DATA/ana9_contrast1_s16bit.nii" );
	paths.push_back( "/SCR/DATA/ana9_contrast1_u16bit.nii" );

	boost::timer timer;
	timer.restart();

	isis::glance::data::IOFactory::signal_start_loading_path.get().connect( &printPath );
	
	std::cout << isis::glance::data::IOFactory::load( paths ).size() << std::endl;
	
	std::cout << timer.elapsed() << " seconds" << std::endl;
	return 0;
}
// }
// }
// }
