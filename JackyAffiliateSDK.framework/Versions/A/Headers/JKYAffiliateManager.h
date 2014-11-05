//
// Created by Daniel Rinser on 25.04.14.
// Copyright (c) 2014 Jacky Media. All rights reserved.
//
// The software is provided "as-is", without warranty of any kind, express or implied,
// including but not limited to the warranties of merchantability, fitness for a particular
// purpose and non-infringement. In no event shall the authors or copyright holders be liable
// for any claim, damages or other liability, whether in an action of contract, tort or
// otherwise, arising from, out of or in connection with the software or the use or other
// dealings in the software.
//


#import <UIKit/UIKit.h>

extern NSString * const JKYAffiliateSDKVersion;


@class JKYInterstitialAppearance;

typedef void (^JKYCompletionBlock) (NSError *error);

extern NSString * const JKYAffiliateErrorDomain;

/**
All errors returned by methods of this SDK (e.g. as parameters to completion blocks) are in the
`JKYAffiliateErrorDomain` error domain and have one of the following error codes.

In most cases, the errors contain a human-readable description in `NSError`'s `localizedDescription`
(although that description is only provided in English - thus, you should not display those error
descriptions to your users - they are rather intended to give developers using this SDK a better
chance to understand what's wrong).
*/
typedef NS_ENUM(NSInteger, JKYAffiliateErrorCode) {
    /** A generic network error. This can be caused by missing connectivity, timeout, or an error in the Jacky backend. */
    JKYAffiliateErrorNetworkOperationFailed         = 0,

    /** The operation has been cancelled explicitly (e.g. via `<[JKYAffiliateManager cancelLoadingInterstitial]>` */
    JKYAffiliateErrorOperationCancelled             = 1,

    /** No app credentials (API key and API secret) specified */
    JKYAffiliateErrorMissingAppCredentials          = 100,

    /** Trying to show an interstitial on an unsupported device */
    JKYAffiliateErrorUnsupportedDevice              = 101,

    /** Advertising identifier not available. This is expected behavior on iOS version < 6.0. If running on iOS 6.0+, make sure the AdSupport framework is linked. */
    JKYAffiliateErrorMissingAdvertisingIdentifier   = 102,

    /** Trying to show an interstitial while already showing another interstitial. */
    JKYAffiliateErrorNoConcurrentInterstitials      = 200,

    /** There is no advertisement available */
    JKYAffiliateErrorNoAdvertisementAvailable       = 201,

    /** There is no preloaded advertisement. You need to call `<[JKYAffiliateManager preloadInterstitialWithCompletionBlock:]>` before showing an interstitial. */
    JKYAffiliateErrorNoAdvertisementPreloaded       = 202,

    /** There is a preloaded advertisement, but it has the wrong orientation (this happens if the user rotates the device between preloading and showing the interstitial). Please call `<[JKYAffiliateManager preloadInterstitialWithCompletionBlock:]>` again. */
    JKYAffiliateErrorWrongAdvertisementOrientation  = 203,

    /** Invalid API key. Please double-check the key you provided to `<[JKYAffiliateManager startWithAPIKey:andAPISecret:]>`. */
    JKYAffiliateErrorInvalidAPIKey                  = 300,

    /** Invalid API secret. Please double-check the secret you provided to `<[JKYAffiliateManager startWithAPIKey:andAPISecret:]>`. */
    JKYAffiliateErrorInvalidAPISecret               = 301,

    /** The event has not yet been verified. Please track this event once with test mode enabled, to verify it and allow tracking. */
    JKYAffiliateErrorEventNotVerified               = 302,
};


/**
This class is the main entry point into the SDK.

### Setup

To use the SDK to show any interstitials, you first have to identify your app.

In your app delegate's `application:didFinishLaunchingWithOptions:`, call `<startWithAPIKey:andAPISecret:>` to setup the Jacky Affiliate SDK:

    [[JKYAffiliateManager sharedManager] startWithAPIKey:@"<YOUR API KEY>"
                                            andAPISecret:@"<YOUR API SECRET>"];

That's all you have to do. You can find your API key and secret in the [Jacky Affiliate dashboard](https://www.jackymedia.com/affiliate).


### Loading interstitials

To ensure a good user experience, we require you to always preload advertisements before showing them. This way, your users won't see any loading delay
after you decide that it's a good time to show an interstitial.

Preload an interstitial via the `<preloadInterstitialWithCompletionBlock:>` method:

    [[JKYAffiliateManager sharedManager] preloadInterstitialWithCompletionBlock:nil];

Since this is an asynchronous operation, you can optionally pass a completion block to be notified when it has
finished loading and whether loading was successful or not:

    [[JKYAffiliateManager sharedManager] preloadInterstitialWithCompletionBlock:^(NSError *error) {
        // [...]
        if(error) {
            NSLog(@"Error loading interstitial: %@", [error localizedDescription]);
        }
    }];

You can always cancel a running loading operation via `<cancelLoadingInterstitial>`. To query if there currently is a preloaded
interstitial available, use `<hasPreloadedInterstitial>`.


### Showing interstitials

Once you have successfully preloaded an interstitial, you can show that interstitial in your app whenever you want. Showing an interstitial is a
synchronous operation.

In the most simple case, you can just use `<showInterstitialWithError:>` to show an interstitial with the default appearance, which looks like this:

<img src="../images/interstitial-default-appearance.png"/>


If you want, you can customize certain aspects of that appearance, like the border color, border width, background color or show/hide animation.
Interstitial appearances are represented by instances of `<JKYInterstitialAppearance>` and can be configured globally, as well as
overridden for individual interstitials.

To configure a custom interstitial appearance globally, see `<defaultInterstitialAppearance>`. Alternatively (or additionally), you can
use `<showInterstitialWithAppearance:error:>` to override the global default for that individual interstitial instance.

*/
@interface JKYAffiliateManager : NSObject


/**
================================================================================
@name   Shared Instance
================================================================================
*/

/**
Get the shared instance of the `JKYAffiliateManager`.
Use this method to access this class from anywhere in your project.

@return The `JKYAffiliateManager` shared instance.
*/
+ (JKYAffiliateManager *)sharedManager;


/**
================================================================================
@name   Initialize
================================================================================
*/


/**
Initialize the Jacky Affiliate SDK for your app.

Typically, you want to do that in your app delegate's `application:didFinishLaunchingWithOptions:`.
You can obtain the required API key and secret in your [Jacky Affiliate dashboard](https://www.jackymedia.com/affiliate) after creating an affiliate account.

@param  apiKey      Your API key.
@param  apiSecret   Your API secret.

@warning **Important:** You need to call this method prior to executing any actions (like loading or showing interstitials).
*/
- (void)startWithAPIKey:(NSString *)apiKey
           andAPISecret:(NSString *)apiSecret;


/**
================================================================================
@name   Configure
================================================================================
*/

/**
Set a custom default interstitial appearance.

You can specify a custom default instance of `<JKYInterstitialAppearance>`, that will be used as the default when showing interstitials.
Of course, you can still override this default for individual interstitials via `<showInterstitialWithAppearance:error:>`.

The predefined default interstitial appearance defines a 5px black border.
*/
@property (nonatomic, strong) JKYInterstitialAppearance *defaultInterstitialAppearance;


/**
Control if advertised apps should be displayed in an in-app AppStore screen, rather than switching to the external AppStore app (default: `YES`).

If set to `YES` (the default), when tapping an ad of an iOS app, the SDK will show that app's description via an in-app `SKStoreProductViewController`,
rather than opening the external iOS AppStore app. This has the advantage of driving less users away from your app.

The `SKStoreProductViewController` will be presented modally on the application's key window's root view controller.

@warning **Please note:** Make sure to (weakly) link the `StoreKit` framework, otherwise this feature won't be available.
*/
@property (nonatomic) BOOL allowInAppAppStoreScreen;


/**
Enable or disable test mode. This mode is intended for testing purposes to get you started quickly with Jacky.

If test mode is enabled, only demo interstitials will be presented. No partnership or further configuration of your affiliate account is necessary.

Defaults to `NO`.

@warning **Please note:** Even with test mode enabled, you still need a Jacky affiliate account and call `<startWithAPIKey:andAPISecret:>` with your API key and API secret!
*/
@property (nonatomic) BOOL testModeEnabled;


/**
Control automatic reloading of preloaded interstitials when the interface orientation changes (default: `YES`).

The advertisements that are displayed in interstitials are orientation-dependent. When you preload an interstitial, the SDK
will always load an interstitial for the *current* interface orientation. Thus, if the user rotates the device between your calls
to `<preloadInterstitialWithCompletionBlock:>` and `<showInterstitialWithError:>`, the cached interstitial has the wrong orientation
and you will receive a `JKYAffiliateErrorWrongAdvertisementOrientation` error.

However, if automatic reloading on orientation change is enabled (which it is by default), the SDK will automatically detect
orientation changes and refresh any cached interstitials for the new interface orientation.
*/
@property (nonatomic) BOOL automaticallyReloadInterstitialOnOrientationChange;


/**
================================================================================
@name   Show Interstitials
================================================================================
*/


/**
Check *general* preconditions for showing interstitials. This checks things such as if the device is supported, everything is initialized etc.

You can use this method, if you need to check up-front if Jacky interstitials are generally available. However, you don't need
to call this prior to calling other methods like `<showInterstitialWithError:>`. Those methods will check the
preconditions themselves and pass an appropriate error to their completion blocks if the check fails.

@warning **Important:** This method only checks the **general** ability to show interstitials, but does not tell anything about
the **specific** availability of ads. Thus, even if this method returns `YES`, it might very well happen that there is no
suitable ad available, and thus `<preloadInterstitialWithCompletionBlock:>` returns an error.

@return `YES` if all general preconditions are fulfilled; `NO` otherwise.
*/
- (BOOL)canShowInterstitials;


/**
Show an interstitial with the default appearance (see `<defaultInterstitialAppearance>`).
@param  error   If you pass a reference to an `NSError` instance, this will contain an appropriate error in case of failure (out param).
@return `YES` if the interstitial could be successfully shown; `NO` otherwise (in this case, the error out-param will contain an appropriate error).
*/
- (BOOL)showInterstitialWithError:(NSError * __autoreleasing *)error;


/**
Show an interstitial with the specified custom appearance.
@param  interstitialAppearance  The custom appearance to use when presenting the interstitial.
@param  error   If you pass a reference to an `NSError` instance, this will contain an appropriate error in case of failure (out param).
@return `YES` if the interstitial could be successfully shown; `NO` otherwise (in this case, the error out-param will contain an appropriate error).
*/
- (BOOL)showInterstitialWithAppearance:(JKYInterstitialAppearance *)interstitialAppearance
                                 error:(NSError * __autoreleasing *)error;


/**
================================================================================
@name   Preload Interstitials
================================================================================
*/

/**
Preload an interstitial to have it available immediately when calling `<showInterstitialWithError:>` later.
@param  completionBlock An optional completion block. Called in case of success (with `nil` as `error` argument), or failure (with appropriate `error` argument, see `<JKYAffiliateErrorCode>`).

@warning **Important:** To not cause unnecessary (mobile) traffic for your users, you should only preload an interstitial
if you know that you will show it shortly after! Moreover, preloaded **interstitials will expire** after some time (the exact
time should be considered an implementation detail, but expect "a few minutes").
*/
- (void)preloadInterstitialWithCompletionBlock:(JKYCompletionBlock)completionBlock;


/**
Cancel any pending asynchronous loading of interstitials (that has been triggered via `<preloadInterstitialWithCompletionBlock:>`).

Any pending preload completion blocks will be called with a `JKYAffiliateErrorOperationCancelled` error code.
*/
- (void)cancelLoadingInterstitial;


/**
Query if a preloaded interstitial is available. If this method returns `NO`, you won't be able to show interstitials.
*/
- (BOOL)hasPreloadedInterstitial;


@end
