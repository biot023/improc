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
#include <sstream>
#include <memory>
#include "content.h"

/* Compile:
 * g++-mp-4.7 -c -std=gnu++11 -pthread -dynamic -Wall -g -D_GLIBCXX_USE_NANOSLEEP -Iinclude -Igtest/include -I/usr/local/include -o imageserver.o imageserver.cpp -I/opt/local/include/ImageMagick   -I/opt/local/include/ImageMagick   -L/opt/local/lib -lMagick++ -lMagickCore   -L/opt/local/lib -lMagick++ -lMagickCore
 *
 * Link:
 * g++-mp-4.7 imageserver.o -lbooster -lcppcms -lssl -lcrypto -o imageserver -I/opt/local/include/ImageMagick   -I/opt/local/include/ImageMagick   -L/opt/local/lib -lMagick++ -lMagickCore   -L/opt/local/lib -lMagick++ -lMagickCore
 *
 */

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
      file.ufform.load( context() );
      file.owner = file.ufform.owner.value();
      // file.data = file.ufform.data.value();
      cout << "Type: " << file.type << endl;
      cout << "Owner: \"" << file.owner << "\"" << endl;
      cout << "File: " << file.ufform.data.value() << endl;
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
