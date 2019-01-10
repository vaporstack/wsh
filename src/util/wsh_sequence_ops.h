//
//  wsh_sequence_ops.h
//  wsh
//
//  Created by vs on 5/14/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_sequence_ops_h
#define wsh_sequence_ops_h

#include "../geo/wsh_sequence.h"

/**
 *
 *
 *
 */

WObject* wsh_sequence_ops_collapse(WSequence* seq);
void     wsh_sequence_center_frames_independent(WSequence* seq);

#endif /* wsh_sequence_ops_h */
