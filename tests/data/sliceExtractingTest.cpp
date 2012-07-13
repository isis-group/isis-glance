#define BOOST_TEST_MODULE SliceExtractingTest
#include <boost/test/unit_test.hpp>
#include <data/image.hpp>
#include <data/slice.hpp>

namespace isis
{
namespace glance
{
namespace test
{

template<typename T>
isis::glance::data::Volume createVolume( size_t row, size_t column, size_t slice, isis::data::dimensions dim )
{
	isis::data::MemChunk<T> chunk( row, column, slice );

	for( size_t z = 0; z < slice; z++ ) {
		for( size_t y = 0; y < column; y++ ) {
			for( size_t x = 0; x < row; x++ ) {
				const isis::util::ivector4 coords( x, y, z );
				static_cast<isis::data::Chunk &>( chunk ).voxel<T>( x, y, z ) = coords[dim];
			}
		}
	}

	const size_t size[] =  { row, column, slice };

	return isis::glance::data::Volume( static_cast<isis::data::Chunk &>( chunk ).asValueArrayBase(), size );

}

template<typename T>
bool checkSlice( isis::glance::data::Slice slice )
{
	isis::glance::data::Slice::size_type size ( slice.getSizeAsVector()[0], slice.getSizeAsVector()[1] );

	for( size_t y = 0; y < size[1]; y++ ) {
		for( size_t x = 0; x < size[0]; x++ ) {
			const size_t dims[] = {x, y};

			if( slice.voxel<T>( dims ) != static_cast<T>( x ) ) {
				return false;
			}
		}
	}

	return true;
}



BOOST_AUTO_TEST_CASE ( slice_extract )
{
	isis::glance::data::Volume::ivec coords;
	isis::glance::data::Volume::fvec perp;

#define TEST_CASE( TYPE, p1,p2,p3, dim, aligned ){  perp[0] = p1; perp[1] = p2; perp[2] = p3; \
		coords[0] = 49; coords[1] = 21; coords[2] = 25; \
		isis::glance::data::Volume vol = createVolume<TYPE>(99,43,51, static_cast<isis::data::dimensions>(dim) ); \
		BOOST_CHECK( checkSlice<TYPE>( vol.extractSlice( perp, coords, aligned ) ) );}

	TEST_CASE( uint8_t, 0, 0, 1, 0, false )
	TEST_CASE( uint8_t, 0, 1, 0, 1, false )
	TEST_CASE( uint8_t, 1, 0, 0, 2, false )
	TEST_CASE( int8_t, 0, 0, 1, 0, false )

}
}
}
}