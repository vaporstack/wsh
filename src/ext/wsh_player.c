//
//  wsh_player.c
//  wsh
//
//  Created by vs on 8/24/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_player.h"

WshPlayer* wsh_player_create_static(WDocumentHnd hnd)
{
	WshPlayer* player     = calloc(1, sizeof(WshPlayer));
	player->playbacktype  = WSH_PLAYER_PLAYBACK_NONE;
	player->hnd	   = hnd;
	player->info	  = NULL;
	player->current_frame = hnd.src->sequence.src->current_frame;

	return player;
}

WshPlayer* wsh_player_create_frames(WDocumentHnd hnd)
{
	WshPlayer* player = wsh_player_create_static(hnd);

	player->playbacktype = WSH_PLAYER_PLAYBACK_FRAMES;

	return player;
}

WshPlayer* wsh_player_create_replay(WDocumentHnd hnd)
{
	WshPlayer* player = wsh_player_create_static(hnd);

	player->playbacktype = WSH_PLAYER_PLAYBACK_REPLAY;
	player->info	 = calloc(1, sizeof(WshPlaybackInfo));

	return player;
}

void wsh_player_destroy(WshPlayer* player)
{
	if (!player)
	{
		wsh_log("Not destroying a NULL player\n");
		
		return;
	}
	if (player->info)
		free(player->info);

	if (player->hnd.src)
		free(player->hnd.src);
}

static void update_replay(WshPlayer* player, double t)
{
	//double last = player->info->last;

	double fakenow = t - player->info->start_time;

	bool playback_done = true;
	if (player->current_frame)
	{
	}
	WObject*   dst = wsh_object_create(NULL);
	WSequence* seq = player->hnd.src->sequence.src;

	WObject* src = seq->current_frame;

	for (int i = 0; i < src->num; i++)
	{

		//wsh_object_add_line(dst, wsh_line_create());
		WLine* sl = src->lines[i];
		if (!sl)
			continue;
		WLine* dl = wsh_line_create();

		//bool done = false;
		for (int j = 0; j < sl->num; j++)
		{
			WPoint p = sl->data[j];
			if (p.time < fakenow)
			{
				wsh_line_add_point(dl, p);
				//playback_done = false;
			}
		}
		if (dl->num != sl->num)
			playback_done = false;

		wsh_object_add_line(dst, dl);
		//while ( !done )
		//	{
		//		WPoint p = sl->data[
		//	}
	}

	player->current_frame = dst;
	if (player->info->multiple_frames)
	{

		if (playback_done)
		{
			free(dst);
			player->current_frame = NULL;
			
			wsh_sequence_frame_next(player->hnd.src->sequence.src);
			wsh_player_stop(player, t);
			wsh_player_start(player, t);
			//player->hnd.src->current_frame
		}
	}
}

void wsh_player_update(WshPlayer* player, double t)
{
	if (!player->playing)
	{
		wsh_log("Not updating, not playin");
		return;
	}

	if (player->playbacktype == WSH_PLAYER_PLAYBACK_REPLAY)
	{
		// is this the cause of all our leaks/
		//update_replay(player, t);
		return;
	}
}

void wsh_player_start(WshPlayer* player, double time)
{
	if (player->playbacktype == WSH_PLAYER_PLAYBACK_REPLAY)
	{
		player->info->start_time = time;
		player->playing		 = true;
	}
}

void wsh_player_stop(WshPlayer* player, double time)
{
}

void wsh_player_pause(WshPlayer* player, double time)
{
}
