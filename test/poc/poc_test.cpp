#include "gmock/gmock.h"
#include <iostream>
#include <string>
#include <memory>

/* Compile:
 * g++-mp-4.7 -c -std=gnu++11 -dynamic -Wall -g -Iinclude -Igmock/include -Igmock/gtest/include -I/usr/local/include -o test/poc/poc_test.o test/poc/poc_test.cpp
 * g++-mp-4.7 -c -std=gnu++11 -dynamic -Wall -g -Iinclude -Igmock/include -Igmock/gtest/include -I/usr/local/include -o test/test_runner.o test/test_runner.cpp
 * g++-mp-4.7 -Igmock/gtest/include -Igmock/gtest -Igmock/include -Igmock -c gmock/gtest/src/gtest-all.cc -o gmock/gtest/gtest-all.o
 * g++-mp-4.7 -Igmock/gtest/include -Igmock/gtest -Igmock/include -Igmock -c gmock/src/gmock-all.cc -o gmock/gmock-all.o
 * ar -rv gmock/libgmock.a gmock/gtest/gtest-all.o gmock/gmock-all.o
 *
 * Link:
 * g++-mp-4.7 test/poc/poc_test.o test/test_runner.o gmock/libgmock.a -lbooster -lcppcms -lssl -lcrypto -o test/test_runner
 *
 * Run:
 * ./test/test_runner
 *
 * Or all with Rakefile:
 * rake test CFILTER="poc_test"
 */

namespace poc {
  using namespace std;

  struct IPoc1
  {
    virtual ~IPoc1() {}
    virtual const string get_str() const = 0;
  };
  
  struct Poc1 : public IPoc1
  {
    Poc1() : _msg( "Default Message" ) {}
    Poc1( const string &msg ) : _msg( msg ) {}
    virtual const string get_str() const { return _msg; }
  private:
    string _msg;
  };

  struct IPoc2
  {
    virtual ~IPoc2() {}
    virtual const string get_str() const = 0;
  };

  struct Poc2 : public IPoc2
  {
    virtual const string get_str() const { return _get_poc1()->get_str(); }
  private:
    virtual shared_ptr<const IPoc1> _get_poc1() const {
      return make_shared<const Poc1>();
    }
  };
  
}

namespace {
  using namespace std;
  using namespace poc;
  using ::testing::Test;
  using ::testing::Return;
  using ::testing::Invoke;
  using ::testing::Const;
  using ::testing::Pointee;

  struct MockPoc1 : public IPoc1
  {
    MOCK_CONST_METHOD0( get_str, const string() );
  };

  struct PartMockPoc2 : public Poc2
  {
    PartMockPoc2()
    {
      ON_CALL( *this, get_str() )
        .WillByDefault( Invoke( this, &PartMockPoc2::_pclass_get_str ) );
    }
    MOCK_CONST_METHOD0( get_str, const string() );
    MOCK_CONST_METHOD0( _get_poc1, shared_ptr<const IPoc1>() );
  private:
    const string _pclass_get_str() const { return Poc2::get_str(); }
  };

  struct PocTest : public Test
  {
  protected:
    string _msg;
    shared_ptr<const MockPoc1> _poc1;
    PartMockPoc2 _poc2;
    PocTest() :
      _msg( "mock poc1 string" ),
      _poc1( make_shared<const MockPoc1>() )
    {
      EXPECT_CALL( *_poc1, get_str() )
        .Times( 1 )
        .WillOnce( Return( _msg ) );
      EXPECT_CALL( _poc2, _get_poc1() )
        .Times( 1 )
        .WillOnce( Return( shared_ptr<const IPoc1>( _poc1 ) ) );
      EXPECT_CALL( _poc2, get_str() );
    }
  };

  // Should instantiate a poc1 and return the result of it's get_str() function
  TEST_F( PocTest,
          ShouldInstantiateAPoc1AndReturnTheResultOfItsGetStrFunction ) {
    EXPECT_EQ( _msg, _poc2.get_str() );
  }
}
