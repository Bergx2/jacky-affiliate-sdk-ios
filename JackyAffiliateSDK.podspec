Pod::Spec.new do |s|
  s.name         = "JackyAffiliateSDK"
  s.version      = "0.9"
  s.summary      = "Affiliate SDK for Jacky Media"
  s.description  = <<-DESC
                   The Jacky Affiliate SDK allows to show affiliate ads.
                   DESC
  s.homepage     = "http://www.jackymedia.com"

  s.license      = { :type => "Copyright", :text => 'Copyright 2014 Jacky Media. All rights reserved.\n\nThe software is provided "as-is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.'  }

  s.author    = "Jacky Media"
  
  s.platform     = :ios
  s.source       = { :git => "https://github.com/jackymedia/jacky-affiliate-sdk-ios.git", :tag => "#{s.version}" }

  s.public_header_files = 'JackyAffiliateSDK.framework/Versions/A/Headers/*.h'
  s.ios.vendored_frameworks = 'JackyAffiliateSDK.framework'

  s.frameworks = "UIKit", "CoreGraphics", "QuartzCore"
  s.weak_frameworks = "AdSupport", "StoreKit"

  s.requires_arc = true
end
