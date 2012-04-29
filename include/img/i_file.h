#include <string>

namespace img {
  using namespace std;

  struct IFile
  {
    virtual ~IFile() {}
    
    virtual const string & uid() const = 0;
    virtual const string & type() const = 0;
    virtual const string & owner() const = 0;
    virtual const string & version() const = 0;
    virtual const string & data() const = 0;
    virtual const size_t size() const = 0;
  };

  struct IRootFile : public IFile
  {
    virtual ~IRootFile() {}
    virtual const string save() = 0;
  };
  
}
