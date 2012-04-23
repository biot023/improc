Given /^there are no images of type "([^\"]*)"$/ do |type|
  Dir.glob( "tmp/#{ type }/*" ).size.should == 0
end

When /^I upload the image "([^\"]*)" with the following options:$/ do |fname, table|
  itype, iid = table.rows.flatten
  @easy = Curl::Easy.new( "http://localhost:8080/imageserver/#{ itype }/#{ iid }" )
  @easy.multipart_form_post = true
  @easy.http_post( Curl::PostField.file( "file", "features/fixtures/#{ fname }" ) )
end

Then /^I should receive a (\d+) response with the image ID$/ do |code|
  @easy.response_code.should == code.to_i
  @iid = @easy.body_str
  @iid.should match( /^[a-z0-9]{20}$/ )
end

Then( /^the image "([^"]*)" should have been stored with the image ID at "([^"]*)"$/
      ) do |fname, dir|
  orig = File.read( "features/fixtures/#{ fname }" )
  target = File.read( "#{ dir }/#{ @iid }" )
  target.should == orig
end
