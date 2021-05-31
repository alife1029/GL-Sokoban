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
        
    }

    void Update() override
    {
        Renderer2D::Begin(glm::mat4(1.0f));

        int offset = 0;
        float size = 0.01f;
        for (float i = -1.0f; i <= 1.0f; i += size)
        {
            for (float j = -1.0f; j <= 1.0f; j += size)
            {
                glm::vec4 color = offset % 2 ? glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f } 
                    : glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f };
                ++offset;

                Renderer2D::DrawQuad({ i, j }, { size, size }, color);
            }
        }

        Renderer2D::End();
        Renderer2D::Flush();
    }

    void Dispose() override
    {
        
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
