#include "gtest/gtest.h"
#include "img/root_file.h"
#include <iostream>
#include <string>
#include <vector>

namespace {
  using namespace std;
  using namespace img;
  
  struct RootFileTest : public ::testing::Test
  {
  protected:
    string _sdir, _type, _owner, _data;
    size_t _size;
    istringstream _source;
    RootFileTest() :
      _sdir( "tmp" ), _type( "item" ), _owner( "monty" ),
      _data( "abcdef" ), _size( _data.size() ),
      _source( _data )
    {}
  };

  // Should generate uid from type and owner
  TEST_F( RootFileTest,
          ShouldGenerateUIDFromTypeAndOwner ) {
    vector<RootFile> rfiles;
    for ( size_t i( 0 ) ; i < 10 ; ++ i )
      rfiles.push_back( RootFile( _sdir, _type, _owner, _source, _size ) );
    for ( size_t i( 0 ) ; i < 10 ; ++ i )
      for ( size_t j( 0 ) ; j < 10 ; ++ j )
        if ( i != j )
          EXPECT_NE( rfiles[j].uid(), rfiles[i].uid() );
  }

  // Should store the type
  
  // Should store the owner
  
  // Should have an empty version
  
  // Should be able to return the file's data
  
  // Should store the size
  
}
