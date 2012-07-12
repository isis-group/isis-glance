// #define BOOST_TEST_MODULE IOFactoryTest

// #include <boost/test/unit_test.hpp>

#include "data/io_factory.hpp"
#include "util/generic_plugin_loader.hpp"
#include "util/widget_base.hpp"

int main( int /*argc*/, char **argv )
{
	//  ENABLE_LOG( isis::glance::data::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	//  ENABLE_LOG( isis::glance::util::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	//  ENABLE_LOG( isis::glance::data::Runtime, isis::util::DefaultMsgPrint, isis::verbose_info );

	isis::util::slist paths;
	paths.push_back( argv[1] );

	boost::timer timer;

	//  isis::glance::data::Image::signal_content_changed.get().connect( &printPath );
	//  isis::glance::data::IOFactory::setUseProposedDataType( true );
	//  isis::glance::data::IOFactory::setProposedDataType( isis::glance::data::ImageDataProperties::SCALAR, isis::glance::data::types::BOOL );
	isis::glance::data::Image::SharedPointer image = isis::glance::data::IOFactory::load( paths ).front();

	const isis::glance::data::Volume &vol = image->operator[]( 0 );

	isis::glance::data::Volume::fvec perp;
	perp[0] = 1;
	perp[1] = 0;
	perp[2] = 0;
	isis::glance::data::Volume::size_type coords;
	coords[0] = image->image_size[0] / 2;
	coords[1] = image->image_size[1] / 2;
	coords[2] = image->image_size[2] / 2;

	timer.restart();
	//  for( unsigned int i = 0; i < 30000; i++ )
	isis::glance::data::Slice slice = vol.extractSlice( perp, coords );
	std::cout << timer.elapsed() << " seconds sagittal" << std::endl;



	isis::data::Chunk chunk( slice,  slice.getSizeAsVector()[0], slice.getSizeAsVector()[1], 1, 1, true );
	isis::data::Image imageOut( chunk );

	isis::data::IOFactory::write( imageOut, "/tmp/gna.nii" );



	return 0;
}
// }
// }
// }
