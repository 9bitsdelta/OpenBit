#include "bitpch.h"
#include "Core/EntryPoint.h"

#include "Core/Base.h"
#include "Core/Application.h"

extern Bit::Application* Bit::CreateApp();

int BitMain(int argc, char** argv)
{
    Bit::Log::Init();

    auto app = Bit::CreateApp();


    while (app->IsRunning())
    {
        app->OnRun();
    }

    delete app;

    return 0;
}