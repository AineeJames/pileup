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

  // Custom state variables (depend on development software)
  // NOTE: This variables should be added manually if required

} GuiLayoutNameState;

#ifdef __cplusplus
extern "C" { // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiLayoutNameState InitGuiLayoutName(void);
void GuiLayoutName(GuiLayoutNameState *state);
static void StepButton();

#ifdef __cplusplus
}
#endif

#endif // GUI_LAYOUT_NAME_H

/***********************************************************************************
 *
 *   GUI_LAYOUT_NAME IMPLEMENTATION
 *
 ************************************************************************************/
#if defined(LAYOUT)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

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

  state.layoutRecs[0] =
      (Rectangle){state.anchor01.x + 0, state.anchor01.y + 0, 144, 264};
  state.layoutRecs[1] =
      (Rectangle){state.anchor01.x + 8, state.anchor01.y + 8, 128, 24};
  state.layoutRecs[2] =
      (Rectangle){state.anchor01.x + 152, state.anchor01.y + 0, 144, 264};
  state.layoutRecs[3] =
      (Rectangle){state.anchor01.x + 160, state.anchor01.y + 8, 128, 248};
  state.layoutRecs[4] =
      (Rectangle){state.anchor01.x + 304, state.anchor01.y + 0, 240, 264};
  state.layoutRecs[5] =
      (Rectangle){state.anchor01.x + 312, state.anchor01.y + 8, 224, 248};

  // Custom variables initialization

  return state;
}
static void StepButton() {
  // TODO: Implement control logic
}

void GuiLayoutName(GuiLayoutNameState *state) {
  const char *ControlsBoxText = "Debugger Controls";
  const char *StepButtonText = "STEP";
  const char *StackContentsBoxText = "Stack Contents";
  const char *CodeViewBoxText = "Code";

  GuiGroupBox(state->layoutRecs[0], ControlsBoxText);
  if (GuiButton(state->layoutRecs[1], StepButtonText))
    StepButton();
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
