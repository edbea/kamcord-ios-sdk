/*
 *
 * Kamcord Framework for recording and sharing gameplays on iOS.
 *
 */

#import <UIKit/UIKit.h>
#import <CoreAudio/CoreAudioTypes.h>

/*
 *
 * Kamcord protocols to receive callbacks.
 *
 */
#import "KamcordProtocols.h"

/*
 *
 * Import C interface.
 *
 */
#import "Kamcord-C-Interface.h"

/*
 *
 * Core Kamcord video recording.
 *
 */
#import "KamcordRecorder.h"

/*
 *
 * Current version is 1.6.7 (01/26/2014)
 *
 */
FOUNDATION_EXPORT NSString * const KamcordVersion;

/*
 *
 * The Kamcord device blacklist options.
 *
 */
typedef enum
{
    KC_DEVICE_TYPE_IPOD_4G          = 1 << 0,
    KC_DEVICE_TYPE_IPOD_5G          = 1 << 1,
    KC_DEVICE_TYPE_IPHONE_3GS       = 1 << 2,
    KC_DEVICE_TYPE_IPHONE_4         = 1 << 3,
    KC_DEVICE_TYPE_IPHONE_4S        = 1 << 4,
    KC_DEVICE_TYPE_IPAD_1           = 1 << 5,
    KC_DEVICE_TYPE_IPAD_2           = 1 << 6,
    KC_DEVICE_TYPE_IPAD_MINI        = 1 << 7,
    KC_DEVICE_TYPE_IPAD_3           = 1 << 8,
    
    // Equivalent to (KC_DEVICE_TYPE_IPOD_4G | KC_DEVICE_TYPE_IPHONE_3GS | KC_DEVICE_TYPE_IPHONE_4 | KC_DEVICE_TYPE_IPAD_1)
    KC_DEVICE_TYPE_SINGLE_CORE      = (1 << 0 | 1 << 2 | 1 << 3 | 1 << 5)
} KC_DEVICE_TYPE;

/*
 *
 * Keys for skinning the Kamcord UI. For more information, please refer to here:
 * https://github.com/kamcord/kamcord-ios-sdk/wiki/Using-the-Kamcord-API%3A-Skinning-the-Kamcord-UI
 *
 */
typedef enum
{
    KC_NAV_BAR = 0,
    KC_NAV_BAR_TEXT_COLOR,
    KC_TAB_BAR,
    KC_BACKGROUND,
    KC_BACKGROUND_TALL,
    KC_TAB_BAR_SELECTED_COLOR,
    KC_TOOLBAR_BACK_BUTTON,
    KC_TOOLBAR_BACK_BUTTON_LANDSCAPE,
    KC_TOOLBAR_DONE_BUTTON,
    KC_TOOLBAR_DONE_BUTTON_LANDSCAPE,
    KC_TOOLBAR_DONE_BUTTON_TEXT_COLOR,
    KC_TABLE_CELL_BACKGROUND_COLOR,
    KC_TABLE_CELL_TEXT_COLOR,
    KC_TOOLBAR_SHARE_BUTTON,
    KC_TOOLBAR_SHARE_BUTTON_LANDSCAPE,
    KC_TOOLBAR_SHARE_BUTTON_TEXT_COLOR,
    KC_MAIN_SHARE_BUTTON,
    KC_MAIN_SHARE_BUTTON_TEXT_COLOR,
    KC_SHARE_TITLE_PLACEHOLDER_TEXT_COLOR,
    KC_SHARE_TITLE_TEXT_COLOR,
    KC_SHARE_GRID_LABEL_COLOR,
    KC_THUMBNAIL_CELL_COLOR,
    KC_TABLE_CELL_SPLIT_COLOR,
    KC_POWERED_BY_KAMCORD_COLOR,
    KC_SETTINGS_SIGN_IN_BUTTON,
    KC_SETTINGS_SIGN_IN_BUTTON_TEXT_COLOR,
    KC_SETTINGS_SIGN_OUT_BUTTON,
    KC_SETTINGS_SIGN_OUT_BUTTON_TEXT_COLOR,
    KC_NOTIFICATION_CALL_TO_ACTION_BUTTON_TEXT,
    KC_CROSS_PROMO_IMAGE,
} KC_UI_COMPONENT;

/*
 *
 * The Kamcord API
 *
 */
@interface Kamcord : NSObject

// -------------------------------------------------------------------------
// Kamcord Configuration
// -------------------------------------------------------------------------

/*
 *
 * The current version of the Kamcord SDK in the format X.Y.Z.
 *
 * @returns     A string describing the current Kamcord SDK.
 *
 */
+ (NSString *)kamcordSDKVersion;

/*
 *
 * Gracefully disable Kamcord on certain devices. If you use this method,
 * make sure it's the first Kamcord call you make.
 *
 * @param   blacklist       An integer bitmap of KC_DEVICE_TYPE describing the
 *                          devices to disable Kamcord for.
 *
 * e.g. [Kamcord setDeviceBlacklist:(KC_DEVICE_TYPE_IPOD_4G | KC_DEVICE_TYPE_IPHONE_3GS | KC_DEVICE_TYPE_IPAD_1)];
 *
 */
+ (void)setDeviceBlacklist:(NSUInteger)blacklist;

/*
 *
 * Kamcord initialization. Set your developer key, secret, app name,
 * and the UIViewController that will present the Kamcord UI when 
 * you call [Kamcord showView].
 *
 * @param   developerKey            Your Kamcord developer key.
 * @param   developerSecret         Your Kamcord developer secret.
 * @param   appName                 The name of your application.
 * @param   parentViewController    The UIViewController that will present the Kamcord UI.
 *
 */
+ (void)setDeveloperKey:(NSString *)key
        developerSecret:(NSString *)secret
                appName:(NSString *)appName
   parentViewController:(UIViewController *)parentViewController;

/*
 *
 * Returns the developer key, secret, app name, and parent view controller.
 *
 */
+ (NSString *)developerKey;
+ (NSString *)developerSecret;
+ (NSString *)appName;
+ (UIViewController *)parentViewController;

/*
 *
 * Set the UIViewController that will later present
 * the Kamcord UI when you call [Kamcord showView].
 *
 * This should initially be set by setDeveloperKey:developerSecret:appName:parentViewController:
 * but can still be used if your app's parent view controller changes.
 *
 * @param       viewController      The view controller that will present the Kamcord UI.
 *
 */
+ (void)setParentViewController:(UIViewController *)viewController;

/*
 *
 * Returns YES if and only if the device is running iOS 5+ and
 * has not been blacklisted via setDeviceBlacklist.
 *
 * @returns     Whether or not Kamcord is enabled on the current device.
 *
 */
+ (BOOL)isEnabled;

/*
 *
 * Returns the current interface orientation.
 *
 * @returns     The app's current interface orientation.
 *
 */
+ (UIInterfaceOrientation)interfaceOrientation;

/*
 *
 * Turns on and off Kamcord video push notifications.
 *
 * Today, we schedule 4 "Gameplay of the Week" notifications for each of the
 * next 4 weeks.
 *
 * @param       enabled     Whether or not to enable video push notifications.
 *
 */
+ (void)setNotificationsEnabled:(BOOL)enabled;

/*
 *
 * Returns whether or not video push notifications are enabled.
 *
 * @returns     Whether or not video push notifications are enabled.
 *
 */
+ (BOOL)notificationsEnabled;

/*
 *
 * Pass Kamcord the local notifications from didReceiveLocalNotification: and
 * didFinishLaunchingWithOptions: if the notification data has the "Kamcord" key.
 * You can also pass us all your local notifications and we will handle the ones
 * relevant to Kamcord and ignore the rest.
 *
 * @param       notification        The local notification for the Kamcord video push notification.
 *
 */
+ (void)handleKamcordNotification:(UILocalNotification *)notification;

/*
 *
 * Fires a test notification - makes it possible to experience the behavior
 * in an app without waiting for Kamcord's servers to fire a weekly notification.
 * This is intended for test purposes only - do not ship with this.
 *
 */
+ (void)fireTestNotification;

// -------------------------------------------------------------------------
// Video Recording
// -------------------------------------------------------------------------

/*
 *
 * Simple API to start/stop/pause/resume video recording.
 *
 */
+ (void)startRecording;
+ (void)stopRecording;
+ (void)resume;
+ (void)pause;

/*
 *
 * Is a video currently being recorded?
 *
 * @returns     Whether or not a video is currently recording.
 *              The only time this video returns YES is when frames are
 *              in the process of being written to a video.
 *              Note that this will return NO if the video is paused.
 *
 */
+ (BOOL)isRecording;

/*
 *
 * Is the current recording paused?
 *
 * @returns     Whether or not the current video recording has been paused."
 *
 */
+ (BOOL)isPaused;

/*
 *
 * Show the Kamcord share view and watch view inside the previously set parentViewController;
 * This is identical to [Kamcord showViewInViewController:[Kamcord parentViewController]].
 *
 */
+ (void)showView;

/*
 *
 * Show the Kamcord view inside the given UIViewController.
 *
 * @param       parentViewController    The UIViewController that will show the Kamcord UI.
 *
 */
+ (void)showViewInViewController:(UIViewController *)parentViewController;

/*
 *
 * Show the Kamcord watch view inside the previously set parentViewController.
 * This is identical to [Kamcord showWatchViewInViewController:[Kamcord parentViewController]].
 *
 */
+ (void)showWatchView;

/*
 *
 * Show the Kamcord watch view inside the given UIViewController.
 *
 * @param       parentViewController    The UIViewController that will show the Kamcord watch view.
 *
 */
+ (void)showWatchViewInViewController:(UIViewController *)parentViewController;

/*
 *
 * Is a Kamcord view showing?
 *
 * @returns     Whether or not a Kamcord view is showing.
 *
 */
+ (BOOL)isViewShowing;

/*
 *
 * Receive callbacks about the life of a recorded video. Please note that this
 * object is *NOT* retained by Kamcord.
 *
 * The KamcordDelegate protocol is defined in Common/Core/KamcordProtocols.h
 *
 * @param       delegate        The delegate to receive Kamcord callbacks.
 *
 */
+ (void)setDelegate:(id <KamcordDelegate>)delegate;

/*
 *
 * Returns the current Kamcord delegate.
 *
 * @returns     The current Kamcord delegate.
 *
 */
+ (id <KamcordDelegate>)delegate;

/*
 *
 * Set the quality of the recorded video. The default setting
 * is KC_STANDARD_VIDEO_QUALITY;
 *
 * @param   quality     The desired recorded video quality.
 *
 */
+ (void)setVideoQuality:(KC_VIDEO_QUALITY)quality;

/*
 *
 * Returns the quality of the recorded videos.
 *
 * @returns     The quality of the recorded videos.
 *
 */
+ (KC_VIDEO_QUALITY)videoQuality;

/*
 *
 * Set the maximum length of a recorded video in seconds. If the gameplay lasts longer
 * than that, only the last N seconds will get recorded in the final video.
 *
 * @param       seconds     The maximum video length.
 *
 */
+ (void)setMaximumVideoLength:(NSUInteger)seconds;

/*
 *
 * Returns the maximum possible recorded video length.
 *
 * @returns     The maximum possible recorded video length.
 *
 */
+ (NSUInteger)maximumVideoLength;

/*
 *
 * Returns a UIView of the thumbnail cropped to the given width and height.
 * When the thumbnail is tapped, the Kamcord UI will be shown.
 *
 * @param       width                   The desired width of the thumbnail.
 * @param       height                  The desired height of the thumbnail.
 * @param       parentViewController    The UIViewController that will present the Kamcord UI
 *                                      when the thumbnail is tapped.
 *
 * @returns     A UIView which has a thumbnail of the last recorded video. When the user taps
 *              on this UIView, it will present the Kamcord UI in the given parentViewController.
 *
 */
+ (UIView *)getThumbnailViewWithWidth:(NSUInteger)width
                               height:(NSUInteger)height
                 parentViewController:(UIViewController *)parentViewController;

/*
 * Returns true if there is at least one video matching the constraints
 *
 * @param      constraints              A dictionary of (NSString *) metadataDisplayKey ->
 *                                      (NSObject *) value. NSString and NSNumber are supported for value.
 *
 */
+ (BOOL)videoExistsForMetadataConstraints:(NSDictionary *)constraints;

/*
 * Shows a Kamcord Video player playing a video with all metadata conforming to the constraints
 * given
 *
 * @param      constraints              A dictionary of (NSString *) metadataDisplayKey ->
 *                                      (ID *) value. NSString and NSNumber are supported for
 * @param      title                    The desired title to be displayed in the shown player.
 *                                      If nil is passed in, it uses the title the video was shared with.
 *
 */
+ (void)showVideoWithMetadataConstraints:(NSDictionary *)constraints
                              withTitle:(NSString *)title;

/*
 *
 * Shows a Kamcord Video player playing the video corresponding to the Id
 *
 * @param      videoID                  ID of the video to be played.
 * @param      title                    The desired title to be displayed in the shown player.
 *                                      If nil is passed in, it uses the title the video was shared with.
 *
 */
+ (void)showVideoWithVideoID:(NSString *)videoID
                   withTitle:(NSString *)title;


// -------------------------------------------------------------------------
// Audio Recording
// -------------------------------------------------------------------------

/*
 *
 * Note: This method is only to be used for non-OpenAL/Unity game engines.
 *       For cocos2d/cocos2d-x/Unity (and other OpenAL-based sound engines),
 *       Kamcord will figure out the correct asbd set it automatically.
 *       Using this method in those cases will most likely break audio recording.
 *
 * Declare the ASBD of the audio stream. This method MUST be called before
 * any audio data is written and before startRecording is called.
 *
 * @param       asbd        The AudioStreamBasicDescription of the byte stream to record.
 *
 */
+ (void)setASBD:(AudioStreamBasicDescription)asbd;

/*
 *
 * Write the live audio bytes to the recorded video. Again, this is only for custom audio engines.
 * If you use OpenAL or Unity's game engine, there is no need for this method.
 *
 * @param       data        A pointer to the raw PCM bytes to record into the currently recording video.
 *                          The data format of this data must match the previously set asbd.
 * @param       numSamples  The number of PCM samples pointed to by the given data pointer.
 *
 */
+ (void)writeAudioBytes:(void *)data
             numSamples:(UInt32)numSamples;


// -------------------------------------------------------------------------
// Voice Recording
// -------------------------------------------------------------------------
/*
 *
 * This enables voice recording so that either (1) your user can activate it
 * (i.e. turn on microphone voice recording) in the Kamcord Settings UI or
 * (2) you can activate it on behalf of the user by calling 
 * [Kamcord activateVoiceOverlay:YES] (defined below).
 *
 * The main reason this method exists is to disable voice overlay in your games
 * so that your users cannot enable voice overlay via the Kamcord Settings UI.
 *
 */
+ (void)setVoiceOverlayEnabled:(BOOL)enabled;
+ (BOOL)voiceOverlayEnabled;

/*
 *
 * Once voice overlay is enabled, the user must activate it by going to the
 * Kamcord Settings UI and enabling it there. You can also programatically active
 * it with the following API calls.
 *
 * Please note that voice overlay *must* first be enabled before trying to
 * activate it.
 *
 */
+ (void)activateVoiceOverlay:(BOOL)activate;
+ (BOOL)voiceOverlayActivated;

// -------------------------------------------------------------------------
// Video Metadata and Social Media Settings
// -------------------------------------------------------------------------

/*
 *
 * Attach arbitrary key/value metadata to the last recorded video
 * that you can retrieve later from the Kamcord servers.
 *
 * @param       metadata        The dictionary of key-value pairs to attach to the previously recorded video.
 *
 */
+ (void)setVideoMetadata:(NSDictionary *)metadata;

/*
 *
 * Returns the previously set video metadata.
 *
 */
+ (NSDictionary *)videoMetadata;

/*
 *
 * This method will query the Kamcord servers for metadata you've previously
 * associated with an uploaded video via the setVideoMetadata API call.
 * When the server request returns, the original metadata you had set
 * will be returned to you as the first argument of the block.
 * There is also NSError argument in the block that will indicate if the
 * request was successful (for example, if the connection failed due to
 * a poor internet connection). The returned NSDictionary is valid if and only if
 * the NSError object is nil.
 *
 * You can get the Kamcord Video ID to pass to this method by implementing the
 * KamcordDelegate protocol defined in Common/Core/KamcordProtocols.h.
 * Implement the videoFinishedUploadingWithSuccess:kamcordVideoID: callback
 * to get the Kamcord Video ID.
 *
 * @param       kamcordVideoID      The unique Kamcord ID for a previously shared video.
 * @param       completionHandler   A block that handles the returned metadata from the server.
 *
 */
+ (void)retrieveMetadataForVideoWithID:(NSString *)kamcordVideoID
                 withCompletionHandler:(void (^)(NSMutableDictionary *, NSError *))completionHandler;

/*
 *
 * Set the level and score of the last recorded video. This information may be used
 * in the Kamcord Watch View, so we recommend that, if appropriate for your game, you 
 * set it after every [Kamcord stopRecording] and before [Kamcord showView].
 * Set the level and score of the last recorded video.
 * Note: Older API, bias towards setDeveloperMetadata
 *
 * @param       level       The level of the last recorded video.
 * @param       score       The score of the last recorded video.
 *
 */
+ (void)setLevel:(NSString *)level
           score:(NSNumber *)score;

/*
 *
 * Set a piece of metadata for the recorded video
 * All metadata is cleared with the start of a recorded video
 *
 * @param       metadataType       The type of metaData (see KC_METADATA_TYPE for more info)
 * @param       displayKey         Describe what the metadata is
 * @param       displayValue       A string representation of the value for this metadata
 * @param       numericValue       A numeric representation of the value for this metadata
 *
 */
+ (void)setDeveloperMetadata:(KC_METADATA_TYPE)metadataType
                  displayKey:(NSString *)displayKey
                displayValue:(NSString *)displayValue;

+ (void)setDeveloperMetadata:(KC_METADATA_TYPE)metadataType
                  displayKey:(NSString *)displayKey
                displayValue:(NSString *)displayValue
                numericValue:(NSNumber *)numericValue;

/*
 *
 * Return the level and score of the last video (after it's been set).
 *
 */
+ (NSString *)level;
+ (NSNumber *)score;

/*
 *
 * Returns the developer metadata pieces currently set
 *
 */
+ (NSDictionary *)developerMetadata;

/*
 *
 * Set title of the video on Kamcord watch pages and on YouTube.
 * If the user enters their own title in the Kamcord Share UI,
 * their title will override this.
 *
 * @param       title       The title of the video on the Kamcord watch page and on YouTube.
 *
 */
+ (void)setVideoTitle:(NSString *)title;

/*
 *
 * Returns the previously set video tite.
 *
 * @returns     The title of the last video.
 *
 */
+ (NSString *)videoTitle;

/*
 *
 * Set the YouTube description and tags of the shared video.
 *
 * @param       description     The YouTube description for this video.
 * @param       tags            The YouTube tags for this video.
 *
 */
+ (void)setYouTubeDescription:(NSString *)description
                         tags:(NSString *)tags;

/*
 *
 * Returns the previously set YouTube description and tags.
 *
 */
+ (NSString *)youtubeDescription;
+ (NSString *)youtubeTags;

/*
 *
 * For iOS 6+, if you have a Facebook app you'd like to share from, you can set its
 * Facebook App ID here for native iOS 6 sharing. Setting sharedAuth to YES
 * will give Kamcord access to the app's Facebook auth instead of Kamcord requesting
 * its own permissions. To use sharedAuth, you *MUST* request the publish_actions
 * permission and be using Facebook SDK 3.1 or later. The advantage of sharedAuth is
 * that the user is not prompted for auth again. If you aren't using the Facebook SDK
 * in your game, you can set sharedAuth to NO and we'll take care of things using the
 * Kamcord Facebook app.
 *
 * @param       facebookAppId   The Facebook App ID.
 * @param       sharedAuth      Whether Facebook auth should be shared between the app and Kamcord.
 *
 */
+ (void)setFacebookAppID:(NSString *)facebookAppID
              sharedAuth:(BOOL)sharedAuth;

/*
 *
 * By default, all shares to Facebook will be done via the Kamcord Facebook app.
 * However, for iOS 6, if you have a Facebook app you'd like to share from, you can set its
 * Facebook App ID here for native iOS 6 sharing. 
 *
 * @param       facebookAppId   The Facebook App ID.
 *
 */
+ (void)setFacebookAppID:(NSString *)facebookAppID;

/*
 *
 * Returns the previously set Facebook App ID.
 *
 * @returns     The previously set Facebook App ID.
 *
 */
+ (NSString *)facebookAppID;

/*
 *
 * Returns whether Facebook authentication is shared between the app and Kamcord.
 *
 * @returns     The previously set Facebook shared auth.
 *
 */
+ (BOOL)facebookAuthShared;

/*
 *
 * Set the Facebook description for Facebook shares.
 *
 * @param       description     The description of the shared video.
 *
 */
+ (void)setFacebookDescription:(NSString *)description;

/*
 *
 * Returns the previously set Facebook description for shared videos.
 *
 * @returns     The previously set Facebook description for shared videos.
 *
 */
+ (NSString *)facebookDescription;

/*
 *
 * Sets the default tweet, which is used if the user doesn't enter a message when
 * they share a video.
 *
 * @param       tweet           The default tweet if the video is shared to Twitter.
 *
 */
+ (void)setDefaultTweet:(NSString *)tweet;

/*
 *
 * Returns the previously set default tweet.
 *
 * @returns     The previously set default tweet.
 *
 */
+ (NSString *)defaultTweet;

/*
 *
 * Videos that are shared to Twitter are embedded via a Twitter card.
 * You can set the description in that Twitter card with this method.
 *
 * @param       description     The Twitter card description for the shared video.
 *
 */
+ (void)setTwitterDescription:(NSString *)description;

/*
 *
 * Returns the previously set Twitter description.
 *
 * @returns     The previously set Twitter description.
 *
 */
+ (NSString *)twitterDescription;

/*
 *
 * Set the default email subject if the user shares a video via email.
 *
 * @param       subject         The default email subject.
 *
 */
+ (void)setDefaultEmailSubject:(NSString *)subject;

/*
 *
 * Returns the previously default email subject.
 *
 * @returns     The previously set default email subject.
 *
 */
+ (NSString *)defaultEmailSubject;

/*
 *
 * Set the default email body if the user shares a video via email.
 *
 * @param       body            The default email body.
 *
 */
+ (void)setDefaultEmailBody:(NSString *)body;

/*
 *
 * Returns the previously set default email body.
 *
 * @returns     The previously set default email body.
 *
 */
+ (NSString *)defaultEmailBody;

/*
 * This method will allow you to upload a video to Facebook with the given parameters
 */
+ (void)uploadVideoToFacebookWithAccessToken:(NSString *)accessToken
                                       title:(NSString *)title
                                 description:(NSString *)description;

// -------------------------------------------------------------------------
// Advanced Settings
// -------------------------------------------------------------------------

/*
 *
 * Controls the target frames-per-second of the recorded video.
 * By default, most of our games run at 60 FPS while the recorded video is at 30 FPS.
 *
 * Valid values are 15, 20, 30.
 *
 * @param       videoFPS            Set the FPS of the recorded video.
 *
 */
+ (void)setVideoFPS:(NSUInteger)videoFPS;

/*
 *
 * Returns the target recording FPS.
 *
 * @returns     The target recording FPS.
 *
 */
+ (NSUInteger)videoFPS;

/*
 *
 * If doing cross promo between your games, you can set the icon for
 * the extra cross promo watch tab.
 *
 * @param       imageName           The name of the image in the main bundle.
 *                                  If you have both the 1x and 2x image
 *                                  named "crossPromoIcon.png" and "crossPromoIcon2@x.png",
 *                                  pass in @"crossPromoIcon.png" and we will automatically
 *                                  use the 2x version on retina devices.
 *
 */
+ (void)setCrossPromoIcon:(NSString *)imageName;

// -------------------------------------------------------------------------
// OpenGL Commands
// -------------------------------------------------------------------------

/*
 *
 * Call this method to save the current state of the rendered frame out to video.
 * This is useful if you have HUD layer and would like to capture a video
 * without the HUD. You can call this method before your HUD draws and
 * Kamcord will write that pre-HUD frame to the video.
 *
 */
+ (void)captureFrame;

/*
 *
 * Returns a snapshot of the currently rendered frame. If the frame is only partially
 * rendered, this will return a snapshot of that. If you'd like to get a snapshot
 * of the next fully rendered frame, please call snapshotNextFrameWithCompletionHandler:
 *
 */
+ (UIImage *)snapshot;

/*
 *
 * Takes a snapshot of the next frame and calls back when the frame is captured.
 *
 * Returns YES if a snashot will be taken. Returns NO if you've previously called this
 * but haven't gotten a callback yet.
 *
 * @param   handler         The completion handler once the next frame's snapshot is ready.
 *                          If you passed in a non-nil destinationURL (below), the second
 *                          argument will be the local URL of the image on disk.
 * @param   destinationURL  If non-nil, the snapshot will be saved to the given local URL.
 *
 */
+ (BOOL)snapshotNextFrameWithCompletionHandler:(void(^)(UIImage * image, NSURL * imageURL))handler
                                     saveToURL:(NSURL *)destinationURL;


// -------------------------------------------------------------------------
// Audio Overlay
// -------------------------------------------------------------------------

/*
 *
 * These methods allow you to add one background audio track to the recorded video.
 *
 */
+ (void)overlayBackgroundTrack:(NSString *)filename;
+ (void)overlayBackgroundTrackAtURL:(NSURL *)fileURL;

// -------------------------------------------------------------------------
// Private APIs: Do not use.
// -------------------------------------------------------------------------
+ (void)setMode:(unsigned long long)mode;
+ (unsigned long long)mode;

@end