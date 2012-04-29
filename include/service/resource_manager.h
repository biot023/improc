#include "img/root_file.h"
#include <string>
#include <streambuf>
#include <memory>

namespace service {
  using namespace std;
  using namespace img;

  struct ResourceManager {
    virtual ~ResourceManager() { cout << "~ResourceManager()" << endl; }
    
    inline virtual shared_ptr<IRootFile> root_file( const string &sdir,
                                                    const string &type, const string &owner,
                                                    streambuf *data, const size_t size ) {
      return make_shared<RootFile>( sdir, type, owner, data, size );
    }
    
  };
  
}
