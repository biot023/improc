Given /^there are no images of type "([^\"]*)"$/ do |type|
  Dir.glob( "tmp/#{ type }/*" ).size.should == 0
end

When /^I upload the image "([^\"]*)" with the following options:$/ do |fname, table|
  type, owner = table.rows.flatten
  @easy = Curl::Easy.new( "http://localhost:8080/imageserver/#{ type }/#{ owner }" )
  @easy.multipart_form_post = true
  @easy.http_post( Curl::PostField.file( "_1", "features/fixtures/#{ fname }" ) )
end

Then /^I should receive a (\d+) response with the UID$/ do |code|
  @easy.response_code.should == code.to_i
  @uid = @easy.body_str
  @uid.should match( /^[a-z0-9]{16,}$/ )
end
