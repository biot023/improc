#include "img/i_file.h"

namespace img {

  struct RootFile : public IRootFile
  {
    RootFile( const string &storage_dir,
              const string &type,
              const string &owner,
              streambuf *source,
              const size_t size )
      : _uid( "" ), _storage_dir( storage_dir ), _type( type ), _owner( owner ),
        _source( source ), _size( size )
    {
      // TODO
    }
    virtual ~RootFile() { cout << "~RootFile()" << endl; }

    virtual const string & uid() const { return _uid; }
    virtual const string & type() const { return _type; }
    virtual const string & owner() const { return _owner; }
    virtual const string & version() const { return ""; }
    virtual const string & data() const { return _data; }
    virtual const size_t size() const { return _size; }
    virtual const string save() { return false; }
  private:
    string _uid, _storage_dir, _type, _owner, _data;
    streambuf *_source;
    size_t _size;
  };
  
}
