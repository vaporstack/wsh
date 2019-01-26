//
//  wsh_player.h
//  wsh
//
//  Created by vs on 8/24/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_player_h
#define wsh_player_h

#include <wsh/wsh.h>

/**
 *
 *	convenience utility to handle playback of wsh files
 *
 */

//	already partially implemented this in GRenderWsh oops
//

typedef enum
{
	WSH_PLAYER_PLAYBACK_NONE,
	WSH_PLAYER_PLAYBACK_FRAMES,
	WSH_PLAYER_PLAYBACK_REPLAY

} WSH_PLAYER_PLAYBACKTYPES;

typedef struct WshPlaybackInfo
{
	double start_time;
	double last;
	bool   trim;
	// bool   remove_gaps;
	bool multiple_frames;
} WshPlaybackInfo;

typedef struct WshPlayer
{
	int		 playing;
	int		 paused;
	int		 playbacktype;
	WshPlaybackInfo* info;
	WDocumentHnd*     hnd;
	WObject*	 current_frame;

} WshPlayer;

WshPlayer* wsh_player_create_static(WDocumentHnd* hnd);
WshPlayer* wsh_player_create_frames(WDocumentHnd* hnd);
WshPlayer* wsh_player_create_replay(WDocumentHnd* hnd);


//	wsh is a core library and this is an extension / nicety
//	the user needs to supply time values in seconds since that is beyond
//	the scope of the library
//	(ONLY IF they want to use the animation playback)

void wsh_player_destroy(WshPlayer* player);
void wsh_player_update(WshPlayer* player, double time);
void wsh_player_start(WshPlayer* player, double time);
void wsh_player_stop(WshPlayer* player, double time);
void wsh_player_pause(WshPlayer* player, double time);

#endif /* wsh_player_h */
