#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <booster/shared_ptr.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include "content.h"

using namespace std;

class ImageServer : public cppcms::application {
public:
  ImageServer( cppcms::service &srv ) :
    cppcms::application( srv )
  {
    dispatcher().assign( "/([a-z0-9]*)", &ImageServer::create, this, 1 );
    mapper().assign( "create", "/{1}" );
    mapper().root( "/imageserver" );
  }

  void create( string type )
  {
    content::UploadedFile file;
    file.type = type;
    if ( request().request_method() == "POST" ) {
      file.form.load( context() );
      file.form.key.value();
      // file.key = file.form.key.value();
      // cout << "Type: " << file.type << endl;
      // cout << "Key: " << file.key << endl;
      // cout << "File Data: " << file.form.file.value() << endl;
      response().status( 201 );
      response().out() << "<h1>Monkeys</h1>" << endl;
    } else {
      response().status( 201 );
      response().out() << "Didn't work, somehow";
    }
  }
  
  // virtual void main( std::string url )
  // {
  //   response().out() <<
  //     "<html>\n"
  //     "<body>\n"
  //     "  <h1>Hello, World!</h1>\n"
  //     "<h2>" << request().path_info() << "</h2>\n"
  //     "</body>\n"
  //     "</html>\n";
  // }
};

int main( int argc, char *argv[] )
{
  try {
    cppcms::service srv( argc, argv );
    srv.applications_pool().mount( cppcms::applications_factory<ImageServer>() );
    srv.run();
  } catch ( const std::exception &e ) {
    std::cerr << e.what() << std::endl;
  }
}
