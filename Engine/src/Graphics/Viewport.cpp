#include "Engine/Graphics/Viewport.hpp"

#include <cmath>
#include <iostream>

#include <glad/glad.h>

namespace engine
{
    // Base class
    Viewport::Viewport(int virtualW, int virtualH)
        :
        mX(0.0f),
        mY(0.0f),
        mW((float)virtualW),
        mH((float)virtualH)
    {
        mAspect = mW / mH;
    }

    void Viewport::Update(int w, int h) { glViewport((int)mX, (int)mY, (int)mW, (int)mH); }
    float Viewport::Aspect() const noexcept { return mAspect; }
    float Viewport::X() const noexcept { return mX; }
    float Viewport::Y() const noexcept { return mY; }
    float Viewport::Width() const noexcept { return mW; }
    float Viewport::Height() const noexcept { return mH; }



    // Stretch Viewport
    StretchViewport::StretchViewport(int virtualW, int virtualH)
        :
        Viewport(virtualW, virtualH) 
    { 
        Update(virtualW, virtualH);
    }

    void StretchViewport::Update(int width, int height)
    {
        glViewport(0, 0, (int)width, (int)height);
    }



    // Fill Viewport
    FillViewport::FillViewport(int virtualW, int virtualH)
        :
        Viewport(virtualW, virtualH) 
    {
        Update(virtualW, virtualH);
    }

    void FillViewport::Update(int width, int height)
    {
        mX = 0.0f;
        mY = 0.0f;
        mW = (float)width;
        mH = (float)height;
        mAspect = mW / mH;

        Viewport::Update(width, height);
    }



    // Fit Viewport
    FitViewport::FitViewport(int virtualW, int virtualH)
        :
        Viewport(virtualW, virtualH)
    {
        Update(virtualW, virtualH);
    }

    void FitViewport::Update(int width, int height)
    {
		float newAspect = static_cast<float>(width) / static_cast<float>(height);

		if (newAspect >= mAspect) 
		{
			mW = (float)height * mAspect;
			mH = (float)height;
			mX = ((float)width - mW) / 2.0f;
			mY = 0;
		} 
		else
		{
			mW = (float)width;
			mH = (float)width * pow(mAspect, -1.0);
			mX = 0.0f;
			mY = ((float)height - mH) / 2.0f;
		}

		Viewport::Update(width, height);
    }
}
