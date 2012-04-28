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
 * Call:
 * curl localhost:8080/imageserver/abc/def -F _1=@features/fixtures/img01.jpg
 */

using namespace std;

class ImageServer : public cppcms::application {
public:
  ImageServer( cppcms::service &srv ) :
    cppcms::application( srv )
  {
    dispatcher().assign( "/([a-zA-Z0-9]+)/([a-zA-Z0-9]+)", &ImageServer::create, this, 1, 2 );
    mapper().assign( "create", "/{1}/{2}" );
    mapper().root( "/imageserver" );
  }

  void create( string type, string owner )
  {
    content::UploadedFileForm form;
    if ( request().request_method() == "POST" ) {
      form.load( context() );
      try {
        if ( ! form.validate() ) throw runtime_error( form.file.error_message.str() );
        response().status( 201 );
        response().out()
          << service::FileCreator( type, owner, form.file.value()->data() )();
      } catch ( const exception &e ) {
        response().status( 403 );
        response().out() << e.what();
      }
    } else {
      response().status( 404 );
    }
  }
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
