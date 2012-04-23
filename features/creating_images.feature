Feature: Creating images
  In order to: Create images that can be displayed by the service
  As a:        Client of the image service
  I want to:   Upload image data in a form and have it be ready to be displayed

  Scenario: Uploading an image
    Given there are no images of type "zeppelin"
    When I upload the image "img01.jpg" with the following options:
      | Image Type | Key    |
      | zeppelin   | abcdef |
    Then I should receive a 201 response with the image ID

  Scenario: Uploading multiple images
    Given Pending
