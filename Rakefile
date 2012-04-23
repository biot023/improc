CXX = ENV["CXX"] || "g++-4.7"
LD  = ENV["LD"] || CXX
AR  = "ar -rv"
RM  = "rm -f"

INCLUDE_DIRS = [ "include",
                 "gtest/include",
                 "/usr/local/include" ]
TESTSRC          = FileList[ "test/**/*.cpp" ]
HEADERS      = FileList[ "include/**/*.h" ]
TESTOBJ      = TESTSRC.ext( "o" )
LIBS         = [ "-lbooster", "-lcppcms", "-lssl", "-lcrypto" ]
TESTLIBS     = FileList[ "gtest/libgtest.a" ]
CLEANLIST    = FileList[ "server", "test/test_runner", "**/*.o", "tmp/**/*" ]

CXXFLAGS = %w( -std=gnu++11 -pthread -dynamic -Wall -g -D_GLIBCXX_USE_NANOSLEEP ) +
  INCLUDE_DIRS.map { |idir| "-I#{ idir }" }
# CXXFLAGS = %w( -pthread -Wall -g -D_GLIBCXX_USE_NANOSLEEP ) +
#   INCLUDE_DIRS.map { |idir| "-I#{ idir }" }
MXXFLAGS = `Magick++-config --cxxflags --cppflags --ldflags --libs`
  .gsub( "\n", " " )

def j( collection )
  collection.join( " " )
end

task :default => :imageserver

desc "Generate and run the unit tests runner"
task :test => [ :set_test_cfilter, "test/test_runner" ] do
  if ENV["TFILTER"]
    sh "./test/test_runner --gtest_filter=#{ ENV["TFILTER"] }"
  else
    sh "./test/test_runner"
  end
end

task :set_test_cfilter do
  if ENV["CFILTER"]
    test_prereqs = Rake::application["test/test_runner"]
      .instance_variable_get( :@prerequisites )
    new_test_prereqs = test_prereqs.reject do |fname|
      fname =~ /_test\.o$/ && fname !~ /#{ ENV["CFILTER"] }/
    end
    Rake::application["test/test_runner"].
      instance_variable_set( :@prerequisites, new_test_prereqs );
  end
end

desc "Clean up all generated files"
task :clean do
  sh "#{ RM } #{ CLEANLIST.join( " " ) }" if CLEANLIST.size > 0
end

# ----- FILES -----------------------------------
#
file "gtest/src/gtest-all.o" do |f|
  sh "#{ CXX } -Igtest/include -Igtest -c gtest/src/gtest-all.cc -o gtest/src/gtest-all.o"
end

file "gtest/libgtest.a" => "gtest/src/gtest-all.o" do |f|
  sh "#{ AR } gtest/libgtest.a gtest/src/gtest-all.o"
end

file "test/test_runner" => TESTOBJ + TESTLIBS do |f|
  sh( "#{ LD } #{ j f.prerequisites } #{ j LIBS } -o #{ f.name } #{ MXXFLAGS }" )
end

file "imageserver" => [ "imageserver.o" ] do |f|
  sh( "#{ LD } #{ j f.prerequisites } #{ j LIBS } -o #{ f.name } #{ MXXFLAGS }" )
end

# ----- RULES -----------------------------------
#
rule ".o" => [ ".cpp" ] + HEADERS do |t|
  sh "#{ CXX } -c #{ j CXXFLAGS } -o #{ t.name } #{ t.source } #{ MXXFLAGS }"
end
