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
      add( file );
      add( key );
    }
    widgets::file file;
    widgets::text key;
  };

  struct UploadedFile : public base_content
  {
    string type, key;
    UploadedFileForm form;
  };
  
}
