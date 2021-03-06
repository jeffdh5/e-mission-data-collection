//
//  TripDiaryStateMachine.h
//  CFC_Tracker
//
//  Created by Kalyanaraman Shankari on 1/31/15.
//  Copyright (c) 2015 Kalyanaraman Shankari. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

/*
 * public static String constants for the transition notifications.
 * I was originally going to use an extern here to avoid multiple copies of the string, but it turns out
 * that NSString constants are actually not re-created every time due to a compile time optimization.
 * See comments by stevebert here:
 * http://iosdevelopertips.com/objective-c/java-developers-guide-to-string-constants-in-objective-c.html
 * 
 * So switching to #defines to make it easier to add/edit the list.
 */

#define CFCTransitionInitialize @"T_INITIALIZE"
#define CFCTransitionInitComplete @"T_INIT_COMPLETE"
#define CFCTransitionExitedGeofence @"T_EXITED_GEOFENCE"
#define CFCTransitionTripStarted @"T_TRIP_STARTED"
#define CFCTransitionRecievedSilentPush @"T_RECEIVED_SILENT_PUSH"
#define CFCTransitionTripEndDetected @"T_TRIP_END_DETECTED"
#define CFCTransitionTripRestarted @"T_TRIP_RESTARTED"
#define CFCTransitionEndTripTracking @"T_END_TRIP_TRACKING"
#define CFCTransitionTripEnded @"T_TRIP_ENDED"
#define CFCTransitionForceStopTracking @"T_FORCE_STOP_TRACKING"
#define CFCTransitionTrackingStopped @"T_TRACKING_STOPPED"
#define CFCTransitionNOP @"T_NOP"

/*
 * We need to decide the format of the notifications. From what I can see, there are two main options:
 * - we have a standard name for the notifications from this machine, and use the "object" field to indicate with transition it is, or
 * - we have different names for each notification.
 *
 * At this point, I am unsure of the pros and cons, so we will go with the single name with multiple object solution, since it makes registering for the notifications significantly easier.
 */

#define CFCTransitionNotificationName @"TRANSITION_NAME"

typedef enum : NSUInteger {
    kStartState,
    kWaitingForTripStartState,
    kOngoingTripState
} TripDiaryStates;

typedef void(^GeofenceStatusCallback)(NSString* geofenceStatus);

@interface TripDiaryStateMachine : NSObject
-(id)initRelaunchLocationManager:(BOOL)restart;

@property CLLocationManager *locMgr;
@property CMMotionActivityManager *activityMgr;

@property TripDiaryStates currState;

+ (NSString*)getStateName:(TripDiaryStates) state;

- (void)checkGeofenceState:(GeofenceStatusCallback) resultField;

@end
