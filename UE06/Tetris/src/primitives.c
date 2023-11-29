//       $Id: primitives.c 47848 2023-11-22 18:32:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/C/Tetris-Shader/intermediate/src/tetris/src/primitives.c $
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

#include "./primitives.h"

// -------------------------------------------------------------------------------------------------

position_type make_position (int const x, int const y) {
   position_type const position = {x, y}; return position;
}

position_type move_position (position_type position, int const dx, int const dy) {
   position.x += dx;
   position.y += dy;

   return position;
}

// -------------------------------------------------------------------------------------------------

action_type action_type_from_glfw_action (int const glfw_action) {
   action_type action = action_unknown;

   switch (glfw_action) {
      case GLFW_PRESS:   action = action_press;   break;
      case GLFW_RELEASE: action = action_release; break;
      case GLFW_REPEAT:  action = action_repeat;  break;
   }

   return action;
}

key_type key_type_from_glfw_key (int const glfw_key) {
   key_type key = key_unknown;

   switch (glfw_key) {
      case GLFW_KEY_DOWN:   key = key_down;  break;
      case GLFW_KEY_LEFT:   key = key_left;  break;
      case GLFW_KEY_RIGHT:  key = key_right; break;
      case GLFW_KEY_UP:     key = key_up;    break;
      case GLFW_KEY_ESCAPE: key = key_esc;   break;
   }

   return key;
}

// -------------------------------------------------------------------------------------------------

char const * string_from_duration (double const duration) {
   static char buffer [32] = {0};

   sprintf_s (buffer, sizeof (buffer), "%1.2f s", duration);

   return buffer;
}

char const * string_from_key (key_type const key, action_type const action) {
   static char buffer [32] = {0};

   switch (key) {
      case key_unknown: strcpy_s (buffer, sizeof (buffer), "<unknown>"); break;
      case key_down:    strcpy_s (buffer, sizeof (buffer), "down");      break;
      case key_left:    strcpy_s (buffer, sizeof (buffer), "left");      break;
      case key_right:   strcpy_s (buffer, sizeof (buffer), "right");     break;
      case key_up:      strcpy_s (buffer, sizeof (buffer), "up");        break;
      case key_esc:     strcpy_s (buffer, sizeof (buffer), "escape");    break;
   }

   switch (action) {
      case action_unknown: strcat_s (buffer, sizeof (buffer), " <unknown>"); break;
      case action_press:   strcat_s (buffer, sizeof (buffer), " pressed");   break;
      case action_release: strcat_s (buffer, sizeof (buffer), " released");  break;
      case action_repeat:  strcat_s (buffer, sizeof (buffer), " repeated");  break;
   }

   return buffer;
}

// -------------------------------------------------------------------------------------------------

void signal_last_gl_error (bool const force_abort) {   // see https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml
   GLenum const error = glGetError ();

   if (error != GL_NO_ERROR) {
      char const * p_message = "<unknown>";

      switch (GL_NO_ERROR) {
         case GL_INVALID_ENUM:
            p_message = "An unacceptable value is specified for an enumerated argument"; break;

         case GL_INVALID_FRAMEBUFFER_OPERATION:
            p_message = "The frame buffer object is not complete"; break;

         case GL_INVALID_OPERATION:
            p_message = "The specified operation is not allowed in the current state"; break;

         case GL_INVALID_VALUE:
            p_message = "A numeric argument is out of range"; break;

         case GL_OUT_OF_MEMORY:
            p_message = "There is not enough memory left to execute the command"; break;

         case GL_STACK_OVERFLOW:
            p_message = "An attempt has been made to perform an operation that would cause an internal stack to overflow"; break;

         case GL_STACK_UNDERFLOW:
            p_message = "An attempt has been made to perform an operation that would cause an internal stack to underflow"; break;
      }

      fprintf (stderr, "GL-ERROR #%d: '%s'\n", error, p_message); abort ();
   }

   if (force_abort)
      abort ();
}

void signal_last_glad_error (bool const force_abort) {
   UNUSED (force_abort); fprintf (stderr, "GLAD-ERROR #%d: '%s'\n", -1, "<unknown>"); abort ();
}

void signal_last_glfw_error (bool const force_abort) {
   char const * p_message = NULL;
   int const    error     = glfwGetError (&p_message);

   if ((error != GLFW_NO_ERROR) && p_message) {
      fprintf (stderr, "GLFW-ERROR #%d: '%s'\n", error, p_message); abort ();
   }

   if (force_abort)
      abort ();
}

void signal_last_ogl_error (GLuint const shader, bool const force_abort) {
   UNUSED (force_abort);

   static char buffer [512] = {0};

   glGetShaderInfoLog (shader, sizeof (buffer), NULL, buffer);

   fprintf (stderr, "OGL-ERROR: '%s'\n", buffer); abort ();
}
