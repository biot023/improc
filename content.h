#include <cppcms/view.h>
#include <cppcms/form.h>
#include <string>

namespace content {
  using namespace cppcms;
  using namespace std;

  struct UploadedFileForm : public form
  {
    UploadedFileForm()
    {
      add( owner );
      add( data );
    }
    widgets::text owner;
    widgets::file data;
  };

  struct UploadedFile : public base_content
  {
    string type, owner, data;
    UploadedFileForm ufform;
  };
  
}
