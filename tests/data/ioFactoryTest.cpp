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
void printPath( const isis::glance::util::SharredPointer<isis::glance::data::Image> &, const isis::glance::data::Image::ImageContentType & )
{
	std::cout << "PATH: " /*<< path*/ << std::endl;
}
int main(int argc, char** argv)
{
	//  ENABLE_LOG( isis::glance::data::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	ENABLE_LOG( isis::glance::util::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	ENABLE_LOG( isis::glance::data::Runtime, isis::util::DefaultMsgPrint, isis::verbose_info );

	isis::util::slist paths;
// 	paths.push_back( "/SCR/DATA/ana9_contrast1_s16bit.nii" );
// 	paths.push_back( "/SCR/DATA/ana9_contrast1_u16bit.nii" );
	paths.push_back(argv[1]);
	
	boost::timer timer;
	timer.restart();

	//  isis::glance::data::Image::signal_content_changed.get().connect( &printPath );
	isis::glance::data::IOFactory::setUseProposedDataType( true );
	isis::glance::data::IOFactory::setProposedDataType( isis::glance::data::ImageDataProperties::SCALAR, isis::glance::data::types::BOOL );
	isis::glance::data::ImageVector images = isis::glance::data::IOFactory::load( paths );

	images.front()->synchronize( isis::glance::data::ImageBase::ALL );
	std::cout << timer.elapsed() << " seconds" << std::endl;
	return 0;
}
// }
// }
// }
