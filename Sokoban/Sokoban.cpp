// Hide console on release build
#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif 

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <Engine.hpp>

#include <iostream>
#include <fstream>
#include <chrono>

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
    try
    {
        AppConfig cfg;
    
        Application* app = new Sokoban(cfg);
        app->Run();
        delete app;
    }
    catch(const std::exception& ex)
    {
        std::ofstream stream("Error.log", std::ios::app);

		if (stream.is_open())
		{
			time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::string currentTimeStr = std::string(ctime(&currentTime));
			stream << "[" << currentTimeStr.substr(0, currentTimeStr.size() - 1) << "]" << std::endl << ex.what() << std::endl;
		}

		stream.close();
    }

    return 0;
}
