/*!
 *
 * Kamcord-C-Interface.h
 * Copyright (c) 2013 Kamcord. All rights reserved.
 *
 */

#ifndef Kamcord_Kamcord_C_Interface_h
#define Kamcord_Kamcord_C_Interface_h

namespace KamcordC
{
    /*******************************************************************
     *
     * VKamcord config
     *
     */
    
    /*
     *
     * Automatically disable Kamcord on certain devices.
     * Call this method before you call any other Kamcord methods.
     *
     */
    void SetDeviceBlacklist(bool disableiPod4G,
                            bool disableiPod5G,
                            bool disableiPhone3GS,
                            bool disableiPhone4,
                            bool disableiPad1,
                            bool disableiPad2,
                            bool disableiPadMini);
    
    /*
     *
     * Returns true if and only if Kamcord is enabled. Kamcord is by default
     * enabled, but is disabled if any of the following conditions are met:
     *
     *  - The version of iOS is < 5.0
     *  - The device has been blacklisted by SetDeviceBlacklist(...);
     *
     */
    bool IsEnabled();
    
    /*
     *
     * Returns the current device orientation.
     *
     */
    const char * DeviceOrientation();
    
    /*
     *
     * Set the device orientation.
     *
     */
    void SetDeviceOrientation(const char * deviceOrientation);
    
    
    /*******************************************************************
     *
     * Video recording
     *
     */
    
    /*
     *
     * Start video recording.
     *
     */
	void StartRecording();
    
    /*
     *
     * Stop video recording.
     *
     */
    void StopRecording();
    
    /*
     *
     * Pause video recording.
     *
     */
    void Pause();
    
    /*
     *
     * Resume video recording.
     *
     */
    void Resume();
    
    /*
     *
     * Returns true if the video is recording.
     *
     */
    bool IsRecording();
    
    /*
     *
     * After every video is recorded (i.e. after you call StopRecording()), you should
     * call this method to set the title for the video in case it is shared.
     *
     * We suggest you set the title to contain some game-specific information such as
     * the level, score, and other relevant game metrics.
     *
     */
    void SetVideoTitle(const char * title);
    
    /*
     *
     * Set the level and score for the recorded video.
     * This metadata is used to rank videos in the watch view.
     *
     */
    void SetLevelAndScore(const char * level,
                          double score);
    
    /*
     *
     * Use this to record the OpenGL frame to video in its currently rendered state.
     * You can use this, for instance, after you draw your game scene but before
     * you draw your HUD. This will result in the recorded video only having
     * the scene without the HUD.
     *
     */
    void CaptureFrame();
    
    /*******************************************************************
     *
     * Kamcord UI
     *
     */
    
    /*
     *
     * Show the Kamcord view, which will let the user share the most
     * recently recorded video.
     *
     */
    void ShowView();
    
    /*
     *
     * Show the watch view, which has a feed of videos shared by other users.
     *
     */
    void ShowWatchView();
    
    
    /*******************************************************************
     *
     * Share settings
     *
     */
    
    /*
     *
     * For native iOS 6 Facebook integration, set your Facebook App ID
     * so all Facebook actions will happen through your game's Facebook app..
     *
     */
    void SetFacebookAppID(const char * facebookAppID);
    
    /*
     *
     * Set the description for when the user shares to Facebook.
     *
     */
    void SetFacebookDescription(const char * description);
    
    /*
     *
     * Set the video description and tags for YouTube.
     *
     */
    void SetYouTubeSettings(const char * description,
                            const char * tags);

    /*
     *
     * Set the default tweet.
     *
     */
    void SetDefaultTweet(const char * tweet);
    
    /*
     *
     * The Twitter desscription for the embedded video.
     *
     */
    void SetTwitterDescription(const char * twitterDescription);

    /*
     *
     * Set the default email subject.
     *
     */
    void SetDefaultEmailSubject(const char * subject);

    /*
     *
     * Set the default email body.
     *
     */
    void SetDefaultEmailBody(const char * body);
    
    
    /*******************************************************************
     * 
     * Sundry Methods
     *
     */
    
    /*
     *
     * Set the FPS of the recorded video. Valid values are 30 and 60 FPS.
     * The default setting is 30 FPS.
     *
     */
    void SetVideoFPS(int videoFPS);
    
    /*
     *
     * Returns the FPS of the recorded video.
     *
     */
    int VideoFPS();
    
    /*
     *
     * To prevent videos from becoming too long, you can use this method
     * and Kamcord will only record the last given seconds of the video.
     *
     * For instance, if you set seconds to 300, then only the last 5 minutes
     * of video will be recorded and shared. The default setting is 300 seconds
     * with a maximum of up to 1 hour = 60 * 60 = 3600 seconds.
     *
     */
    void SetMaximumVideoLength(unsigned int seconds);
    
    /*
     *
     * Returns the maximum video length.
     *
     */
    unsigned int MaximumVideoLength();
    
    /*******************************************************************
     *
     * Gameplay of the week
     *
     */
    
    /*
     *
     * Enable automatic gameplay of the week push notifications.
     *
     */
    void SetNotificationsEnabled(bool notificationsEnabled);
    
    /*
     *
     * Fire a test gameplay of the week push notfication.
     *
     */
    void FireTestNotification();
}

#endif
