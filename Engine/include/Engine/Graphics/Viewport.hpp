#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "Engine/API.hpp"

namespace engine
{
    class ENGINE_API Viewport
    {
    public:
        Viewport(int virtualW, int virtualH);
        virtual void Update(int width, int height);

        // Getters
        float Aspect() const noexcept;
        float X() const noexcept;
        float Y() const noexcept;
        float Width() const noexcept;
        float Height() const noexcept;
    
    protected:
        float mAspect;
        float mX;
        float mY;
        float mW;
        float mH;
    };


    class ENGINE_API StretchViewport : public Viewport
    {
    public:
        StretchViewport(int virtualW, int virtualH);
        virtual void Update(int width, int height) override;
    };


    class ENGINE_API FillViewport : public Viewport
    {
    public:
        FillViewport(int virtualW, int virtualH);
        virtual void Update(int width, int height) override;
    };


    class ENGINE_API FitViewport : public Viewport
    {
    public:
        FitViewport(int viertualW, int virtualH);
        virtual void Update(int width, int height) override;
    };
    
}

#endif
