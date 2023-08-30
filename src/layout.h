/*******************************************************************************************
 *
 *   LayoutName v1.0.0 - Tool Description
 *
 *   MODULE USAGE:
 *       #define LAYOUT
 *       #include "gui_layout_name.h"
 *
 *       INIT: GuiLayoutNameState state = InitGuiLayoutName();
 *       DRAW: GuiLayoutName(&state);
 *
 *   LICENSE: Propietary License
 *
 *   Copyright (c) 2022 raylib technologies. All Rights Reserved.
 *
 *   Unauthorized copying of this file, via any medium is strictly prohibited
 *   This project is proprietary and confidential unless the owner allows
 *   usage in any other form by expresely written permission.
 *
 **********************************************************************************************/

#include "pulog.h"
#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including
// this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h> // Required for: strcpy()

#ifndef GUI_LAYOUT_NAME_H
#define GUI_LAYOUT_NAME_H

typedef struct {
  Vector2 anchor01;

  bool StackContentsEditMode;
  char StackContentsText[128];
  bool CodeViewEditMode;
  char CodeViewText[128];

  Rectangle layoutRecs[6];

  bool StepButtonPressed;

} GuiLayoutNameState;

#ifdef __cplusplus
extern "C" { // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiLayoutNameState InitGuiLayoutName(void);
static void StepButton(GuiLayoutNameState *state);
void GuiLayoutName(GuiLayoutNameState *state);
void set_boxes(GuiLayoutNameState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_LAYOUT_NAME_H

/***********************************************************************************
 *
 *   GUI_LAYOUT_NAME IMPLEMENTATION
 *
 ************************************************************************************/
// #define LAYOUT
#if defined(LAYOUT)

#include "raygui.h"

void set_boxes(GuiLayoutNameState *state) {
  int pad = 8;
  float fourth = 0.25 * GetScreenWidth();
  float height = GetScreenHeight();
  float innerrect_height = height - (4 * pad);
  float outerrect_height = height - (2 * pad);
  state->layoutRecs[0] =
      (Rectangle){state->anchor01.x + 0, state->anchor01.y + 0, fourth - pad,
                  outerrect_height};
  state->layoutRecs[1] =
      (Rectangle){state->anchor01.x + pad, state->anchor01.y + pad,
                  fourth - (3 * pad), innerrect_height};
  state->layoutRecs[2] =
      (Rectangle){state->anchor01.x + fourth, state->anchor01.y + 0,
                  fourth - pad, outerrect_height};
  state->layoutRecs[3] =
      (Rectangle){state->anchor01.x + fourth + pad, state->anchor01.y + pad,
                  fourth - (3 * pad), innerrect_height};
  state->layoutRecs[4] =
      (Rectangle){state->anchor01.x + 2 * fourth, state->anchor01.y + 0,
                  2 * fourth - (2 * pad), outerrect_height};
  state->layoutRecs[5] =
      (Rectangle){state->anchor01.x + 2 * fourth + pad, state->anchor01.y + pad,
                  2 * fourth - (4 * pad), innerrect_height};
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiLayoutNameState InitGuiLayoutName(void) {
  GuiLayoutNameState state = {0};

  state.anchor01 = (Vector2){10, 10};

  state.StackContentsEditMode = false;
  strcpy(state.StackContentsText, "69\n34\n35");
  state.CodeViewEditMode = false;
  strcpy(state.CodeViewText, "0\n{\n  1 + dupe print dupe 10 breakifeq\n}");

  set_boxes(&state);

  // Custom variables initialization

  return state;
}

static void StepButton(GuiLayoutNameState *state) {
  state->StepButtonPressed = true;
}

void GuiLayoutName(GuiLayoutNameState *state) {
  const char *ControlsBoxText = "Debugger Controls";
  const char *StepButtonText = "STEP";
  const char *StackContentsBoxText = "Stack Contents";
  const char *CodeViewBoxText = "Code";

  GuiGroupBox(state->layoutRecs[0], ControlsBoxText);
  if (GuiButton(state->layoutRecs[1], StepButtonText))
    StepButton(state);
  GuiGroupBox(state->layoutRecs[2], StackContentsBoxText);
  if (GuiTextBox(state->layoutRecs[3], state->StackContentsText, 128,
                 state->StackContentsEditMode))
    state->StackContentsEditMode = !state->StackContentsEditMode;
  GuiGroupBox(state->layoutRecs[4], CodeViewBoxText);
  if (GuiTextBox(state->layoutRecs[5], state->CodeViewText, 128,
                 state->CodeViewEditMode))
    state->CodeViewEditMode = !state->CodeViewEditMode;
}

#endif // LAYOUT
