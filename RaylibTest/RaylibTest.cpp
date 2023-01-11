#include "pch.h"

#include "raylib.h"


int main()
{
    InitWindow(300, 300, "Raylib works!");
    InitAudioDevice();

    Sound sound = LoadSound("Assets/sounds/doorClose_000.ogg");

	if (sound.stream.buffer == nullptr)
        return -1;

    Font font = LoadFont("Assets/fonts/GROBOLD.ttf");
    if (font.texture.id == 0)
    {
        // error...
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawCircle(100, 100, 100, GREEN);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}