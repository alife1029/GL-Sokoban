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

class Sokoban : public Application, EventSystem
{
public:
    Sokoban(const AppConfig& cfg) : Application(cfg) 
    {
        mViewport = new FillViewport(cfg.Width, cfg.Height);
        mCamera = new OrthographicCamera(mViewport, 5.0f);
    }

    void Start() override
    {
        SetEventListener(this);

        StaticRenderer2D::BeginScene();

        int offset = 0;
        float size = 0.5f;
        for (float i = -6.0f; i <= 6.0f; i += size)
        {
            for (float j = -6.0f; j <= 6.0f; j += size)
            {
                glm::vec4 color = offset % 2 ? glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f } 
                    : glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f };
                ++offset;

                StaticRenderer2D::DrawQuad({ i, j }, { size, size }, color);
            }
        }

        StaticRenderer2D::EndScene();
    }

    void Update() override
    {
        if (Input::GetKey(ENGINE_KEY_Q))
            mCamera->Rotate(-0.01f);
        if (Input::GetKey(ENGINE_KEY_E))
            mCamera->Rotate(0.01f);

        if (Input::GetKey(ENGINE_KEY_W))
            mCamera->Translate(0.0f, 0.01f);
        if (Input::GetKey(ENGINE_KEY_S))
            mCamera->Translate(0.0f, -0.01f);
        if (Input::GetKey(ENGINE_KEY_A))
            mCamera->Translate(-0.01f, 0.0f);
        if (Input::GetKey(ENGINE_KEY_D))
            mCamera->Translate(0.01f, 0.0f);

        mCamera->Update();

        StaticRenderer2D::RenderScene(mCamera->Combined());

        Renderer2D::Begin(mCamera->Combined());
        Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, rot++, { 0.0f, 0.0f, 1.0f, 1.0f });
        Renderer2D::End();
        Renderer2D::Flush();

        RenderStat& stats = RenderStats();
        //std::cout << "Batches: " << stats.Batches() << " (Static: " << stats.StaticBatches << " Dynamic: " << stats.DynamicBatches << ")" << std::endl;
    }

    void Resize(int width, int height) override
    {
        mViewport->Update(width, height);
    }

    void Keydown(int keycode) override
    {
        std::cout << "Keydown! (" << keycode << ")" << std::endl;
    }

    void Keyup(int keycode) override
    {
        std::cout << "Keyup! (" << keycode << ")" << std::endl;
    }

    void Dispose() override
    {
        
    }
private:
    Viewport* mViewport;
    OrthographicCamera* mCamera;
    float rot = 0;
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
