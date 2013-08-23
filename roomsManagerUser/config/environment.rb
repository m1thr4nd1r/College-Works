# Load the rails application
require File.expand_path('../application', __FILE__)

# Initialize the rails application
RoomsManager::Application.initialize!

ActionMailer::Base.smtp_settings = {
  :user_name => 'app16998112@heroku.com',
  :password => 'M4rc0sM4SS@!',
  :domain => 'web.com',
  :address => 'smtp.sendgrid.net',
  :port => 587,
  :authentication => :plain,
  :enable_starttls_auto => true
}
