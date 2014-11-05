//
// Created by Daniel Rinser on 29.04.14.
// Copyright (c) 2014 Jacky Media. All rights reserved.
//
// The software is provided "as-is", without warranty of any kind, express or implied,
// including but not limited to the warranties of merchantability, fitness for a particular
// purpose and non-infringement. In no event shall the authors or copyright holders be liable
// for any claim, damages or other liability, whether in an action of contract, tort or
// otherwise, arising from, out of or in connection with the software or the use or other
// dealings in the software.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/**
Defines several available animations for presenting/dismissing interstitials.
*/
typedef NS_ENUM(NSUInteger, JKYInterstitialAnimation) {
    /** Zoom the interstitial in/out from/to the center of the screen. */
    JKYInterstitialAnimationZoom,
    /** Slide the interstitial in/out from/to the bottom of the screen. */
    JKYInterstitialAnimationSlide,
    /** Perspective animation from left/to right */
    JKYInterstitialAnimationPerspective
};


/**
This is a simple value class that represents the visual appearance of an interstitial.

You can either set a custom appearance globally (see `<[JKYAffiliateManager setDefaultInterstitialAppearance:]>`),
or override the default by specifying an instance of this class when showing an interstitial (see
`<[JKYAffiliateManager showInterstitialWithAppearance:error:]>`).
*/
@interface JKYInterstitialAppearance : NSObject


/**
================================================================================
@name   Create
================================================================================
*/

/**
Create a new instance with default values.
@return A new instance of `JKYInterstitialAppearance`.
*/
+ (instancetype)appearance;


/**
================================================================================
@name   Properties
================================================================================
*/

/**
The color of the background overlay behind the interstitial.

Default is black with 60% alpha.
*/
@property (nonatomic, strong) UIColor *backgroundColor;


/**
The width (i.e. thickness) of the border around the interstitial in pt.

Default is 5pt.
*/
@property (nonatomic, assign) CGFloat borderWidth;


/**
The color of the border around the interstitial

Default is black.
*/
@property (nonatomic, strong) UIColor *borderColor;


/**
The background color of the close button.

Default is black with 90% alpha.
*/
@property (nonatomic, strong) UIColor *closeButtonCircleFillColor;


/**
The foreground color of the close button (i.e. the cross).

Default is white.
*/
@property (nonatomic, strong) UIColor *closeButtonCrossColor;


/**
The animation used when showing/hiding the interstitial. See `<JKYInterstitialAnimation>` for an explanation of available animations.

Default is `<JKYInterstitialAnimationZoom>`.
*/
@property (nonatomic, assign) JKYInterstitialAnimation animation;


@end
