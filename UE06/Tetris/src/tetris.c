//       $Id: tetris.c 47848 2023-11-22 18:32:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/C/Tetris-Shader/intermediate/src/tetris/src/tetris.c $
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

#include "./board.h"
#include "./timer.h"
#include "./window.h"

// -------------------------------------------------------------------------------------------------

static block_type g_current_block = {color_red, {N_COLS / 2, N_ROWS}};
static bool       g_game_over     = false;

// -------------------------------------------------------------------------------------------------

static void handle_key_event (key_type key, action_type action);

// -------------------------------------------------------------------------------------------------

void on_key (key_type const key, action_type const action) {
   if (g_game_over)
      return;

   printf ("key event: %s\n", string_from_key (key, action));

   handle_key_event (key, action);
}

void on_paint (void) {
   if (g_game_over)
      return;

   printf ("paint event: repaint\n");

   render_block (g_current_block.position, g_current_block.color);
}

void on_timer (double const elapsed) {
   if (g_game_over)
      return;

   printf ("timer event: %s elapsed\n", string_from_duration (elapsed));

   handle_key_event (key_down, action_press);
}

// -------------------------------------------------------------------------------------------------

static void handle_key_event (key_type const key, action_type const action) {
   if (key == key_esc)
      g_game_over = true;

   if (!g_game_over && (key != key_unknown) && ((action == action_press) || (action == action_repeat))) {
      int dx = 0;
      int dy = 0;

      switch (key) {
         case key_down:  dy = -1; break;
         case key_left:  dx = -1; break;
         case key_right: dx =  1; break;
         case key_up:    dy =  1; break;
      }

      position_type const position = move_position (g_current_block.position, dx, dy);

      if (is_valid_position (position)) {
         g_current_block.position = position; render_block (g_current_block.position, g_current_block.color);
      }
   }
}

// -------------------------------------------------------------------------------------------------

int main (void) {
   initialize_renderer (N_ROWS, N_COLS, on_key);
   initialize_timer (on_timer);

   do {   // the message pump
      drive_timer ();

      begin_frame ();
      on_paint ();
      end_frame ();

      if (!renderer_is_open ())
         g_game_over = true;
   } while (!g_game_over);

   printf ("game over\n"); shut_down_renderer();
}
