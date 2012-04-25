#include "img/i_file.h"

namespace img {

  template <typename SaveOpts>
    struct RootFile : public IFile
    {
      RootFile( const string &type,
                const string &owner,
                const istream &source,
                const size_t size )
        : _uid( "" ), _type( type ), _owner( owner ), _size( size )
      {
        // TODO
      }

      virtual const string & uid() const { return _uid; }
      virtual const string & type() const { return _type; }
      virtual const string & owner() const { return _owner; }
      virtual const string & version() const { return ""; }
      virtual const string & data() const { return _data; }
      virtual const size_t size() const { return _size; }
    private:
      string _uid, _type, _owner, _data;
      size_t _size;
    };
  
}
