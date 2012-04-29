#include "gmock/gmock.h"
#include <iostream>
#include <string>

namespace poc {
  using namespace std;
  
  struct Poc1
  {
    Poc1( const string &msg ) : _msg( msg ) {}
    virtual ~Poc1() {}
    virtual const string get_str() const { return _msg; }
  private:
    string _msg;
  };

  struct Poc2
  {
    Poc2( Poc1 &poc1 ) : _poc1( poc1 ) {}
    virtual ~Poc2() {}
    virtual const string get_str() { return _poc1.get_str(); }
  private:
    Poc1 _poc1;
  };
  
}

namespace {
  using namespace std;
  using namespace poc;
  using ::testing::Test;
  using ::testing::AtLeast;
  using ::testing::_;
  using ::testing::MatcherCast;
  using ::testing::SafeMatcherCast;
  using ::testing::Return;

  struct MockPoc1 : public Poc1
  {
    MockPoc1() : Poc1( "poc1 string" ) {}
    MOCK_METHOD0( get_str, const string() );
  };

  struct PocTest : public Test
  {
  protected:
    string _msg;
    MockPoc1 _poc1;
    Poc2 _poc2;
    PocTest() :
      _msg( "mock poc1 string" ),
      _poc2( _poc1 )
    {
      EXPECT_CALL( _poc1, get_str() )
        .Times( 1 )
        .WillOnce( Return( _msg ) );
    }
  };

  // Should return the message returned from poc1
  TEST_F( PocTest,
          ShouldReturnTheMessageReturnedFromPoc1 ) {
    EXPECT_EQ( _msg, _poc2.get_str() );
  }
}
