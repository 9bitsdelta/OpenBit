#include "Bit.h"

#include <iostream>

class Sandbox : public Bit::Application
{
public:
    Sandbox() {}
    ~Sandbox() {}

    void OnUpdate(Bit::Timestep& ts)
    {
        BIT_TRACE(m_Watch);
        BIT_ERROR("HELLO");
        Close();
    }

private:
    int m_Watch = 5;
};

Bit::Application* Bit::CreateApp()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    return BitMain(argc, argv);
}