#include "service/resource_manager.h"
#include <string>
#include <memory>

namespace service {
  using namespace std;
  using namespace img;

  struct FileCreator
  {
    FileCreator( const shared_ptr<ResourceManager> rm,
                 const string &sdir, const string &type, const string &owner,
                 istream &data, const size_t size )
    : _rm( rm ), _sdir( sdir ), _type( type ), _owner( owner ), _data( data ), _size( size ) {}

    inline virtual const string operator() () {
      return _rm->root_file( _sdir, _type, _owner, _data, _size )->save();
    }
  private:
    shared_ptr<ResourceManager> _rm;
    string _sdir, _type, _owner;
    istream &_data;
    size_t _size;
  };
  
}
