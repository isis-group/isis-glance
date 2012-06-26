#include <data/image.hpp>
#include <DataStorage/image.hpp>
#include <DataStorage/io_factory.hpp>
#include <boost/timer.hpp>

using namespace isis;

int main(int /*argc*/, const char **argv)
{
	boost::timer timer;

	std::string file_name = argv[1];
	data::Image isisImages = data::TypedImage<uint16_t>( data::IOFactory::load( file_name ).front() );


	isis::glance::data::Image gImage( isisImages, glance::data::FLOAT );

	std::cout << "typeID float: " << glance::data::FLOAT << std::endl;
	std::cout << gImage.operator[](10)->getTypeID() << std::endl;

	std::cout << isisImages.voxel<uint16_t>(10,10,10,10) << std::endl;
	const size_t dims[] = { 10,10,10 };
	std::cout << gImage.operator[](10).voxel<float>(dims) << std::endl;

	gImage.setDataType( glance::data::DOUBLE );
	gImage.synchronize( isis::glance::data::ImageBase::VOXELS );
	

	
	

};