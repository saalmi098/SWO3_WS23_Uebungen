//       $Id: primitives.h 47848 2023-11-22 18:32:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/C/Tetris-Shader/intermediate/src/tetris/src/primitives.h $
// $Revision: 47848 $
//     $Date: 2023-11-22 19:32:07 +0100 (Mi., 22 Nov 2023) $
//   $Author: p20068 $
//   Creator: Michael Hava
//  Creation: October 24, 2023
// Copyright: (c) 2023 Michael Hava (michael.hava<AT>risc-software.at)
//            (c) 2023 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------------------------------------------------------------

#undef  UNUSED
#define UNUSED(v) ((void) (v))

// -------------------------------------------------------------------------------------------------

typedef struct {
   int x;
   int y;
} position_type;

typedef enum {
   action_unknown,
   action_press,
   action_release,
   action_repeat,
} action_type;

typedef enum {
   key_unknown,
   key_down,
   key_left,
   key_right,
   key_up,
   key_esc,
} key_type;

typedef void on_key_type   (key_type, action_type);   // the user's event handler for events from the keyboard
typedef void on_timer_type (double elapsed);          // the user's event handler for events from the timer

// -------------------------------------------------------------------------------------------------

position_type make_position (int x, int y);
position_type move_position (position_type position, int dx, int dy);

action_type action_type_from_glfw_action (int glfw_action);
key_type    key_type_from_glfw_key       (int glfw_key);

char const * string_from_duration (double duration);
char const * string_from_key      (key_type key, action_type action);

void signal_last_gl_error   (bool force_abort);
void signal_last_glad_error (bool force_abort);
void signal_last_glfw_error (bool force_abort);
void signal_last_ogl_error  (GLuint shader, bool force_abort);
