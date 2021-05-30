#include <Engine.hpp>
#include <iostream>

using namespace engine;

class Sokoban : public Application
{
public:
    Sokoban(const AppConfig& cfg) : Application(cfg) { }

    void Start() override
    {
        std::cout << "Start called!" << std::endl;
    }

    void Update() override
    {
        std::cout << "Update called!" << std::endl;
    }

    void Dispose() override
    {
        std::cout << "Dispose called!" << std::endl;
    }
};

int main(int argc, char** argv)
{
    AppConfig cfg;
    
    Application* app = new Sokoban(cfg);
    app->Run();
    delete app;

    return 0;
}
