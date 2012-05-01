#include "img/root_file.h"
#include <string>
#include <streambuf>
#include <memory>

namespace service {
  using namespace std;
  using namespace img;

  struct FileCreator
  {
    FileCreator( const shared_ptr<ResourceManager> rm,
                 const string &sdir, const string &type, const string &owner,
                 streambuf *data, const size_t size )
    : _rm( rm ), _sdir( sdir ), _type( type ), _owner( owner ), _data( data ), _size( size ) {}
    
    inline virtual const string operator() () {
      return RootFile( _sdir, _type, _owner, _data, _size )->save();
    }
  private:
    shared_ptr<ResourceManager> _rm;
    string _sdir, _type, _owner;
    streambuf *_data;
    size_t _size;
  };
  
}
