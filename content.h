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
      file.non_empty();
      file.limits( 0, 6291456 );
      file.error_message( "Must be not empty and 6 megabytes or less in size" );
      add( file );
    }
    widgets::file file;
  };
  
}
