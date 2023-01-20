#include "pch.h"

#include "App.h"

int main(int argc, char* argv[])
{
	TD::App app;

    app.Init();

    app.Run();

    app.Quit();

    return 0;
}
