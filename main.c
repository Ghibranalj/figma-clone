#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "raylib.h"

#define MAX_REC 255

Color col;
bool shouldTakeScreenshot = false;
char *screenshotLocation;
bool isEraseMode = false;

typedef struct {
  Rectangle rec;
  Color col;
} myRectangle;

int main(void) {

  myRectangle rect[MAX_REC];
  int count = 0;
  col = BLACK;

  const int screenWidth = 800;
  const int screenHeight = 450;
  SetTraceLogLevel(LOG_NONE);
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);
  Vector2 from;
  while (!WindowShouldClose()) {

    BeginDrawing();

    ClearBackground(RAYWHITE);
    for (int i = 0; i < count; i++) {
      Rectangle rec = rect[i].rec;
      Color col = rect[i].col;
      DrawRectangle(rec.x, rec.y, rec.width, rec.height, col);
    }

    if (isEraseMode && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

      Vector2 mousePos = GetMousePosition();
      int index = -1;
      for (int i = count - 1; i > -1; i--) {
        Rectangle rec = rect[i].rec;
        if (CheckCollisionPointRec(mousePos, rec)) {
          index = i;
          break;
        }
      }

      if (index == -1) {
        EndDrawing();
        continue;
      }

      printf("%d\n", count);

      for (int i = index; i < count - 1; i++) {
        rect[i] = rect[i + 1];
      }
      count--;


      EndDrawing();
      continue;
    }

    if (!isEraseMode && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      from = GetMousePosition();
    }

    if (!isEraseMode && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

      Vector2 to = GetMousePosition();
      Rectangle rec = (Rectangle){from.x, from.y, to.x - from.x, to.y - from.y};

      DrawRectangle(rec.x, rec.y, rec.width, rec.height, col);
    }

    if (!isEraseMode && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      Vector2 to = GetMousePosition();
      rect[count].rec =
          (Rectangle){from.x, from.y, to.x - from.x, to.y - from.y};
      rect[count].col = col;
      count++;
    }

    EndDrawing();

    if (shouldTakeScreenshot) {
      shouldTakeScreenshot = false;
      TakeScreenshot(strcat(screenshotLocation, ".png"));
    }
  }
  CloseWindow();

  return 0;
}

void makeScreenshot(char *filename) {
  if(shouldTakeScreenshot){
    return;
  }

  int size = strlen(filename);
  screenshotLocation = malloc(sizeof(char *) * size);
  strcpy(screenshotLocation, filename);

  shouldTakeScreenshot = true;
}

void setColor(unsigned int hex) {
  printf("%x\n", hex);

  unsigned int r = (hex & 0xFF0000) >> 16;
  unsigned int g = (hex & 0xFF00) >> 8;
  unsigned int b = (hex & 0xFF);

  col = (Color){r, g, b, 255};
}

void toggleEraser() { isEraseMode = !isEraseMode; }