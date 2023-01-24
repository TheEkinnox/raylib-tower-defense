#include "pch.h"

#include "App.h"

int main(const int argc, const char* argv[])
{
	TD::App app;

    app.Init(argc, argv);

    app.Run();

    app.Quit();

    return 0;
}
