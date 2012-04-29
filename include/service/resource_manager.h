#include "img/root_file.h"
#include <iostream>
#include <memory>

namespace service {
  using namespace std;
  using namespace img;

  struct ResourceManager {
    
    inline virtual shared_ptr<IRootFile> root_file( const string &sdir,
                                                    const string &type, const string &owner,
                                                    istream &data, const size_t size ) {
      return make_shared<RootFile>( sdir, type, owner, data, size );
    }
    
  };
  
}
