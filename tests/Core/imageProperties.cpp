#define BOOST_TEST_MODULE ImagePropertiesTest

#include <boost/test/unit_test.hpp>
#include <DataStorage/chunk.hpp>

#include "Data/image_properties.hpp"

namespace isis
{
namespace glance
{
namespace test
{

BOOST_AUTO_TEST_CASE( image_properties_test )
{
	isis::data::MemChunk<int16_t> mChunk( 100, 12, 33, 10 );
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
	ImageProperties image_props = data::Image( mChunk ) ;
	BOOST_CHECK( image_props.has_one_typeid );
	BOOST_CHECK_EQUAL( image_props.major_type_id, ( int )data::ValueArray<int16_t>::staticID );
	BOOST_CHECK_EQUAL( image_props.file_name, std::string( "file.gna" ) );
	BOOST_CHECK_EQUAL( image_props.file_path, std::string( "/this/is/a/path/or/file.gna" ) );
	BOOST_CHECK_EQUAL( image_props.min_max.first, -32 );
	BOOST_CHECK_EQUAL( image_props.min_max.second, 1331 );
	BOOST_CHECK_EQUAL( image_props.extent, 1363 );
	BOOST_CHECK_EQUAL( image_props.type_group, ImageProperties::SCALAR );
	BOOST_CHECK_EQUAL( image_props.orientation_matrix_latched.getRow( 0 ), util::fvector4( 1, 0, 0 ) );
	BOOST_CHECK_EQUAL( image_props.orientation_matrix_latched.getRow( 1 ), util::fvector4( 0, 0, -1 ) );
	BOOST_CHECK_EQUAL( image_props.orientation_matrix_latched.getRow( 2 ), util::fvector4( 0, 1, 0 ) );
	BOOST_CHECK_EQUAL( image_props.image_size_aligned32, util::ivector4( 100, 12, 36, 12 ) );
	BOOST_CHECK_EQUAL( image_props.voxel_size, util::fvector4( 1.7, 1.3, 2.5, 1.1 ) );
}

} // end namespace test
} // end namespace glance
} // end namespace isis