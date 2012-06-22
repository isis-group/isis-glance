#include <data/image.hpp>
#include <DataStorage/image.hpp>
#include <boost/timer.hpp>

using namespace isis;

int main()
{
	boost::timer timer;
	isis::data::MemChunk<int16_t> mChunk( 100, 101, 102, 103 );
	mChunk.voxel<int16_t>( 12, 2, 30, 2 ) = -32;
	mChunk.voxel<int16_t>( 12, 2, 33, 2 ) = 1331;
	mChunk.setPropertyAs<std::string>( "file_path", std::string( "/this/is/a/path/or/file.gna" ) );
	mChunk.setPropertyAs<util::fvector4>( "rowVec", util::fvector4( 0.995058, -0.0465222, 0.087724 ) );
	mChunk.setPropertyAs<util::fvector4>( "columnVec", util::fvector4( 0.0784591, -0.173113, -0.981772 ) );
	mChunk.setPropertyAs<util::fvector4>( "sliceVec", util::fvector4( 0.0608603, 0.983803, -0.168607 ) );
	mChunk.setPropertyAs<util::fvector4>( "indexOrigin", util::fvector4( -87.9776, -28.3009, 100.674 ) );
	mChunk.setPropertyAs<util::fvector4>( "voxelSize", util::fvector4( 1, 1, 1, 1 ) );
	mChunk.setPropertyAs<util::fvector4>( "voxelGap", util::fvector4( .7, .3, 1.5, .1 ) );
	mChunk.setPropertyAs<uint16_t>( "sequenceNumber", 1 );
	mChunk.setPropertyAs<uint32_t>( "acquisitionNumber", 0 );

	isis::data::Image isisImage = isis::data::Image( mChunk );
	timer.restart();
	isis::glance::data::Image gImage( isisImage );
	std::cout << "Created glance::image with " << gImage.size()
			  << " volumes from an isis::image with size "
			  << gImage.image_size << " in "
			  << timer.elapsed() << " seconds." << std::endl;

};