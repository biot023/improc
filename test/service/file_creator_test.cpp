#include <string>
#include <iostream>
#include <sstream>
#include "gmock/gmock.h"
#include "service/file_creator.h"

namespace {
  using namespace std;
  using namespace img;
  using namespace service;
  using ::testing::Test;
  using ::testing::AtLeast;
  using ::testing::_;
  using ::testing::Return;

  struct MockRootFile : public RootFile
  {
    MockRootFile( const string &sdir, const string &type, const string &owner,
                  istream &data, const size_t size ) :
      RootFile( sdir, type, owner, data, size ) {}
    MOCK_METHOD0( save, const string() );
  };

  struct MockResourceManager : public ResourceManager
  {
    MOCK_METHOD5( root_file, shared_ptr<IRootFile>( const string &,
                                                    const string &, const string &,
                                                    istream &, const size_t ) );
  };

  struct FileCreatorTest : public Test
  {
  protected:
    string _sdir, _type, _owner;
    stringstream _data;
    size_t _size;
    shared_ptr<MockResourceManager> _rm;
    shared_ptr<MockRootFile> _rf;
    FileCreator _fc;
    string _uid;

    FileCreatorTest() :
      _sdir( "tmp" ), _type( "type" ), _owner( "owner" ),
      _size( 43210 ),
      _rm( make_shared<MockResourceManager>() ),
      _rf( make_shared<MockRootFile>( _sdir, _type, _owner, _data, _size) ),
      _fc( _rm, _sdir, _type, _owner, _data, _size ),
      _uid( "abc123" )
    {
      EXPECT_CALL( *_rm, root_file( _, _, _, _, _ ) ).WillOnce( Return( _rf ) );
      EXPECT_CALL( *_rf, save() ).WillOnce( Return( _uid ) );
    }
  };

  // Should run, at least
  TEST_F( FileCreatorTest,
          ShouldRunAtLeast ) {
    _fc();
  }

  // // Should create a temp root file object
  // TEST_F( FileCreatorTest,
  //         ShouldCreateATempRootFileObject ) {
  //   EXPECT_CALL( *_rm, root_file( _sdir, _type, _owner, _data, _size ) ).
  //     WillOnce( Return( _rf ) );
  //   _fc();
  // }

  // // Should save the temp root file object
  // TEST_F( FileCreatorTest,
  //         ShouldSaveTheTempRootFileObject ) {
  //   EXPECT_CALL( *_rf, save() ).WillOnce( Return( _uid ) );
  //   _fc();
  // }

  // // Should return the UID returned from save
  // TEST_F( FileCreatorTest,
  //         ShouldReturnTheUIDReturnedFromSave ) {
  //   EXPECT_CALL( *_rf, save() ).WillOnce( Return( _uid ) );
  //   EXPECT_EQ( _uid, _fc() );
  // }
}
