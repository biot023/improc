require "curb"
require "rspec/matchers"

$server = IO.popen( "./imageserver -c test-config.js" )
sleep( 1 )
at_exit do
  # $server.close
  `kill -9 #{ $server.pid }`
end

class Object
  def __debug
    str = self.is_a?( String ) ? self : self.inspect
    puts "\n*** -- #{ str }"
  end
end
