//
//  r_input_tablet_cocoa.c
//  r4
//
//  Created by vs on 12/26/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#include "r_input_tablet_cocoa.h"

#include "WacomTabletDriver.h"


#include <AppKit/NSEvent.h>
#include <Foundation/Foundation.h>

//extern AppSettings   app_settings;
//extern AppExtensions app_extensions;
#include "../../input/input_tablet.h"

static CGLContextObj fsc = NULL;

UInt32 mLastUsedTablet;
UInt32 mContextID;
UInt32 mTabletOfContext;

//extern

enum {
	R_TABLET_DOWN,
	R_TABLET_UP,
	R_TABLET_MOTION,
	R_TABLET_DRAG,
	R_TABLET_PROXIMITY
};

void process_event(NSEvent* theEvent)
{
	NSEventType eventType	  = [theEvent type];
	BOOL	isMouseEvent       = NO;
	BOOL	isTabletPointEvent = NO;
	BOOL isTabletProximityEvent = NO;
	NSUInteger  modifierFlags      = ([theEvent modifierFlags] & NSDeviceIndependentModifierFlagsMask);
	NSString*   modifierString     = [NSString stringWithFormat:@"%X", (unsigned int)modifierFlags];
	//NSString    *penName             = nil;
	
	//printf(".");
	// Establish which events we may safely query for subtype
	//if(	eventType == NSMouseMoved
	if(
	   eventType == NSMouseMoved
	   || eventType == NSTabletPoint
	   ||  eventType == NSLeftMouseDragged
	   ||	eventType == NSRightMouseDragged
	   ||	eventType == NSOtherMouseDragged
	   
	   ||	eventType == NSLeftMouseDown
	   ||	eventType == NSRightMouseDown
	   ||	eventType == NSOtherMouseDown
	   
	   ||	eventType == NSLeftMouseUp
	   ||	eventType == NSRightMouseUp
	   ||	eventType == NSOtherMouseUp )
	{
		isMouseEvent = YES;
	}
	
	// NSEventMaskRightMouseUp -> NSEventMaskRightMouseUp
	/*
	 // Establish which events we may safely query for subtype
	 if (eventType == NSMouseMoved || eventType == NSLeftMouseDragged ||
	 eventType == NSLeftMouseDown  ||  eventType == NSEventTypeLeftMouseDragged || eventType == NSEventTypeRightMouseDragged || eventType == NSEventTypeOtherMouseDragged
	 || eventType == NSEventTypeLeftMouseDown || eventType == NSEventTypeRightMouseDown || eventType == NSEventTypeOtherMouseDown
	 || eventType == NSEventTypeLeftMouseUp || eventType == NSEventTypeRightMouseUp || eventType == NSEventTypeOtherMouseUp) {
	 isMouseEvent = YES;
	 printf("MOUSE?\n");
	 }
	 */
	
	
		if ( eventType == NSEventTypeTabletProximity )
		{
			//printf("TABLET!?\n");
			isTabletProximityEvent = true;
		}
	
	//NSEventSubtype st = [theEvent subtype];
	
	//printf("eventType: %lu st: %lu\n", (unsigned long)eventType, (unsigned long)st );
	
	//NSEventMask mask = [theEvent mask]
	
	// Find tablet point events (both pure and embedded)
	if (eventType == NSEventTypeTabletPoint || (isMouseEvent == YES && [theEvent subtype] == NSEventSubtypeTabletPoint)) 	{
		printf("yass\n");
		isTabletPointEvent = true;
	}
	
	/*
	 if ( st == NSEventSubtypeTabletPoint && isMouseEvent )
	 {
	 printf("yass\n");
	 isTabletPointEvent = true;
	 }
	 */
	if (eventType == NSEventTypeTabletPoint) {
		isTabletPointEvent = YES;
		printf("POINT\n");
		//cout << "p-";
	}
	/*
	 if (st == NSEventSubtypeTabletPoint) {
	 isTabletPointEvent = YES;
	 printf("POINT ST\n");
	 
	 //cout << "p-";
	 }
	 if (st == NSEventSubtypeTabletProximity) {
	 mLastUsedTablet = (int)[theEvent systemTabletID];
	 bool prox       = [theEvent isEnteringProximity];
	 eventType       = R_TABLET_PROXIMITY;
	 printf("Proximity? %d\n", prox);
	 //b_receive_tablet_proximity(prox);
	 
	 //	PUT THIS BACK IN ???
	 //	InputTablet::singleton->tablet_proximal = prox;
	 //	InputTablet::singleton->send_pen_proximity([theEvent pointingDeviceType], prox );
	 //return;
	 //penName           = [self nameOfPen:[theEvent pointingDeviceSerialNumber]];
	 //printf("pen is: %s\n", penName);
	 }
	 */
	
	
	if (!isTabletPointEvent) {
		//printf("ditch2\n");
			return;
	}
	//printf("TABLET\n");
	//if (!InputTablet::singleton->tablet_proximal ){
	//printf("Ditching, mouse is handled elsewhere!\n");
	//return;
	//}
	
	//	this is horrible but fuckit moving on
	int button     = -7;
	int event_type = -7;
	
	//RMessage m;
	
	if (eventType == NSEventTypeLeftMouseDragged || eventType == NSEventTypeLeftMouseDown || eventType == NSEventTypeLeftMouseUp) {
		button = 0;
		//printf("left!\n");
	}
	
	if (eventType == NSEventTypeRightMouseDragged || eventType == NSEventTypeRightMouseDown || eventType == NSEventTypeRightMouseUp) {
		button = 1;
		//printf("right!\n");
	}
	if (eventType == NSEventTypeOtherMouseDragged || eventType == NSEventTypeOtherMouseDown || eventType == NSEventTypeOtherMouseUp) {
		button = 7;
		//printf("OTHER!\n");
	}
	
	if (eventType == NSEventTypeMouseMoved) {
		//printf("m\n");
		event_type = R_TABLET_MOTION;
		//event_type = REDTA_motion;
	} else if (eventType == NSLeftMouseDragged ||eventType == NSEventTypeLeftMouseDragged || eventType == NSEventTypeRightMouseDragged || eventType == NSEventTypeOtherMouseDragged) {
		event_type = R_TABLET_DRAG;
		//printf("drag!\n");
		
		//event_type = REDTA_drag;
	} else if (eventType == NSEventTypeLeftMouseDown || eventType == NSEventTypeRightMouseDown || eventType == NSEventTypeOtherMouseDown) {
		//event_type = REDTA_down;
		//printf("down!\n");
		
		event_type = R_TABLET_DOWN;
	} else if (eventType == NSEventTypeLeftMouseUp || eventType == NSEventTypeRightMouseUp || eventType == NSEventTypeOtherMouseUp) {
		event_type = R_TABLET_UP;
		//printf("up!\n");
		
		//event_type = REDTA_up;
	} else if ( isTabletProximityEvent )
	{
		event_type = R_TABLET_PROXIMITY;
		
	}else{
		//printf("ugh!\n");
		// do we discard NSEventTypeTabletPoint since it seems to be teh suck?
		static bool event_discard_suppress = false;
		if (!event_discard_suppress) {
			printf("Unhandled event type.\n");
			event_discard_suppress = true;
		}
	}
	
	//	x y pressure rotation tilt_x tilt_y tangential button_mask
	double x, y, pressure, rotation, tilt_x, tilt_y, tangential;
	x = y = pressure = rotation = tilt_x = tilt_y = tangential = -1;
	if ( event_type == R_TABLET_DOWN || event_type == R_TABLET_DRAG || event_type == R_TABLET_UP )
	{
		
		pressure     = [theEvent pressure];
		rotation     = [theEvent rotation];
		NSPoint tilt = [theEvent tilt];
		tilt_x       = tilt.x;
		tilt_y       = tilt.y;
		tangential   = [theEvent tangentialPressure];
	}
	NSPoint loc = [theEvent locationInWindow];
	
	//NSPoint p = [theEvent convertPoint:loc fromView: nil];
	//NSView* currentView = [NSView focusView];
	
	x = loc.x;
	y = loc.y;
	
	///y = app_settings.current_window_y - y;
	//x *= app->r_window->retina_scale;
	//y *= app->r_window->retina_scale;
	//r_app_normalize_coords(&x, &y);
	//y *= -1;
	
	//	NSView
	//	fsc;
	//	OK DO WE FUCKING HAVE EVERYTHING?
	//	I think this is safe.  We'd NEVER be here if this was a mouse event, soooo
	//double w = app_settings.framebuffer_height;
	
	switch (event_type) {
		case R_TABLET_PROXIMITY:
			b_receive_tablet_proximity(true);
			break;
		case R_TABLET_DOWN:
			printf("d");

			//[NSEvent setMouseCoalescingEnabled:false];
			//app_extensions.coalescing_events = false;
			b_receive_tablet_down_rich(x, y, button, pressure, rotation, tilt_x, tilt_y, tangential);
			//b_receive_tablet_proximity(true);
			
			break;
		case R_TABLET_UP:
			printf("u");

			//app_extensions.coalescing_events = true;
			//[NSEvent setMouseCoalescingEnabled:true];
			b_receive_tablet_up_rich(x, y, button, pressure, rotation, tilt_x, tilt_y, tangential);
			
			break;
		case R_TABLET_MOTION:
			//printf("m");
			b_receive_tablet_motion_rich(x, y, button, pressure, rotation, tilt_x, tilt_y, tangential);
			
			break;
		case R_TABLET_DRAG:
			b_receive_tablet_proximity(true);
			b_receive_tablet_drag_rich(x, y, button, pressure, rotation, tilt_x, tilt_y, tangential);

			//b_receive_tablet_drag(x,y);
			break;
		default:
			printf("error!\n");
			break;
	}
	
	/*
	 //	TODO put this back in
	 
	 switch (event_type) {
	 case REDTA_motion:
	 //cout << "redta motion!" << endl;
	 InputTablet::singleton->send_pen_motion(mLastUsedTablet, button, x, y, pressure, rotation, tilt_x, tilt_y, tangential);
	 break;
	 case REDTA_down:
	 [NSEvent setMouseCoalescingEnabled: false];
	 //setMouseCoalescingEnabled(false, NULL);
	 InputTablet::singleton->send_pen_down(mLastUsedTablet, button, x, y, pressure, rotation, tilt_x, tilt_y, tangential);
	 break;
	 case REDTA_drag:
	 InputTablet::singleton->send_pen_drag(mLastUsedTablet, button, x, y, pressure, rotation, tilt_x, tilt_y, tangential);
	 break;
	 case REDTA_up:
	 //setMouseCoalescingEnabled(true, NULL);
	 
	 [NSEvent setMouseCoalescingEnabled: true];
	 InputTablet::singleton->send_pen_up(mLastUsedTablet, button, x, y, pressure, rotation, tilt_x, tilt_y, tangential);
	 break;
	 default:
	 printf("Nooope\n");
	 break;
	 }
	 
	 */
	
	/*
	 
	 OLD DEAD
	 else if (eventType	== NSEventTypeLeftMouseDragged){
	 double x, y;
	 NSPoint p =  [theEvent locationInWindow];
	 x = p.x;
	 y = p.y;
	 printf ("drag! %f %f\n", x, y);
	 RInput::handle_wacom_drag(NULL, x,y);
	 }
	 */
	
	//---------- Set UI ---------------------------------------------------------
	/*
	 
	 OLD DEAD
	 // Mouse move
	 if(eventType == NSEventTypeMouseMoved)
	 {
	 [mMouseMoveLocationXField		setFloatValue:[theEvent locationInWindow].x];
	 [mMouseMoveLocationYField		setFloatValue:[theEvent locationInWindow].y];
	 [mMouseMoveDeltaXField			setFloatValue:[theEvent deltaX]];
	 [mMouseMoveDeltaYField			setFloatValue:[theEvent deltaY]];
	 [mMouseMoveModifiersField		setStringValue:modifierString];
	 [mMouseMoveIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
	 
	 }
	 
	 // Mouse down
	 if(	eventType == NSEventMaskLeftMouseDown
	 ||	eventType == NSEventMaskRightMouseDown
	 ||	eventType == NSEventTypeOtherMouseDown )
	 {
	 [mMouseDownLocationXField		setFloatValue:[theEvent locationInWindow].x];
	 [mMouseDownLocationYField		setFloatValue:[theEvent locationInWindow].y];
	 [mMouseDownModifiersField		setStringValue:modifierString];
	 [mMouseDownIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
	 
	 }
	 
	 // Mouse Dragged
	 if(	eventType == NSEventTypeLeftMouseDragged
	 ||	eventType == NSEventTypeRightMouseDragged
	 ||	eventType == NSEventTypeOtherMouseDragged )
	 {
	 [mMouseDragLocationXField		setFloatValue:[theEvent locationInWindow].x];
	 [mMouseDragLocationYField		setFloatValue:[theEvent locationInWindow].y];
	 [mMouseDragDeltaXField			setFloatValue:[theEvent deltaX]];
	 [mMouseDragDeltaYField			setFloatValue:[theEvent deltaY]];
	 [mMouseDragModifiersField		setStringValue:modifierString];
	 [mMouseDragIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
	 
	 [mMouseDragIsTabletEventField setNeedsDisplay:YES];
	 
	 }
	 
	 // Mouse up
	 if(	eventType == NSEventTypeLeftMouseUp
	 ||	eventType == NSEventTypeRightMouseUp
	 ||	eventType == NSEventTypeOtherMouseUp )
	 {
	 [mMouseUpLocationXField			setFloatValue:[theEvent locationInWindow].x];
	 [mMouseUpLocationYField			setFloatValue:[theEvent locationInWindow].y];
	 [mMouseUpModifiersField			setStringValue:modifierString];
	 [mMouseUpIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
	 
	 }
	 
	 // Set field valid for Tablet Point events
	 if(isTabletPointEvent == YES)
	 {
	 [mAbsoluteXField					setIntValue:[theEvent absoluteX]];
	 [mAbsoluteYField					setIntValue:[theEvent absoluteY]];
	 [mAbsoluteZField					setIntValue:[theEvent absoluteZ]];
	 
	 [mPressureField					setFloatValue:[theEvent pressure]];
	 [mTangentialPressureField		setFloatValue:[theEvent tangentialPressure]];
	 
	 [mTiltXField						setFloatValue:[theEvent tilt].x];
	 [mTiltYField						setFloatValue:[theEvent tilt].y];
	 [mRotationField					setFloatValue:[theEvent rotation]];
	 
	 [mDeviceIDField					setIntValue:[theEvent deviceID]];
	 }
	 
	 // Set Fields valid for point or proximity events
	 if(	isTabletPointEvent == YES
	 ||	eventType == NSEventTypeTabletProximity)
	 {
	 [mDeviceIDField					setIntValue:[theEvent deviceID]];
	 }
	 
	 if(eventType == NSEventTypeTabletProximity)
	 {
	 [mTransducerNameField			setStringValue:penName];
	 [mTransducerSerialNumberField	setStringValue:[NSString stringWithFormat:@"0x%X", [theEvent pointingDeviceSerialNumber]]];
	 }
	 */
}

void r_input_tablet_cocoa_deinit()
{
}

void r_input_tablet_cocoa_init()
{
	printf("Initializing cocoa tablet handler.\n");
	if (mLastUsedTablet != mTabletOfContext) {
		[WacomTabletDriver destroyContext:mContextID];
		mContextID = 0;
		
		//[WacomTabletDriver destroyContext:mContext2ID];
		//mContext2ID = 0;
	}
	
	// If no context, create one
	if (mContextID == 0) {
		mContextID       = [WacomTabletDriver createContextForTablet:mLastUsedTablet type:pContextTypeDefault];
		mTabletOfContext = mLastUsedTablet;
	}
	
	/*
	 
	 NSEventMask observedTypes = NSEventTypeTabletPoint | NSEventTypeTabletProximity | NSMouseMoved | NSEventTypeMouseMoved
	 | NSEventTypeMouseMoved | NSEventTypeLeftMouseDragged | NSLeftMouseDragged | NSEventTypeRightMouseDragged | NSEventTypeOtherMouseDragged
	 | NSEventTypeLeftMouseDown | NSEventTypeRightMouseDown | NSEventTypeOtherMouseDown
	 | NSEventTypeLeftMouseUp | NSEventTypeRightMouseUp | NSEventTypeOtherMouseUp;
	 
	 
	 */
	
	
	
	NSEventMask observedTypes =
		NSTabletPointMask
	|	NSTabletProximityMask
	
	|	NSMouseMovedMask
	|	NSLeftMouseDraggedMask
	|	NSRightMouseDraggedMask
	|	NSOtherMouseDraggedMask
	
	|	NSLeftMouseDownMask
	|	NSRightMouseDownMask
	|	NSOtherMouseDownMask
	
	|	NSLeftMouseUpMask
	|	NSRightMouseUpMask
	|	NSOtherMouseUpMask
	//	the future?
	|       NSEventMaskTabletPoint
	|	NSEventMaskTabletProximity
	|	NSEventMaskLeftMouseDown
	|	NSEventMaskLeftMouseDragged
	|	NSEventMaskLeftMouseUp
	|	NSEventMaskRightMouseDown
	|	NSEventMaskRightMouseDragged
	|	NSEventMaskRightMouseDown
	|	NSEventMaskOtherMouseDown
	|	NSEventMaskOtherMouseDragged
	|	NSEventMaskOtherMouseUp;
	
	
	[NSEvent addLocalMonitorForEventsMatchingMask:observedTypes
					      handler:^(NSEvent* theEvent) {
						      process_event(theEvent);
						      return theEvent;
					      }];
	fsc = CGLGetCurrentContext();
}
