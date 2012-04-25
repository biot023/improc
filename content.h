#include <cppcms/view.h>
#include <cppcms/form.h>
#include <cppcms/http_file.h>
#include <string>

namespace content {
  using namespace cppcms;
  using namespace std;

  struct UploadedFileForm : public form
  {
    UploadedFileForm()
    {
      add( file );
    }
    widgets::file file;
  };

  struct UploadedFile : public base_content
  {
    string type, owner, data;
    UploadedFileForm upload_form;
  };
  
}
