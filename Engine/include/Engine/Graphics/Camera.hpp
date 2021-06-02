#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Engine/API.hpp"
#include "Viewport.hpp"
#include <glm/glm.hpp>

namespace engine
{
    class ENGINE_API OrthographicCamera
    {
    public:
        OrthographicCamera(Viewport* viewport, float size);

        void Update() noexcept;

        void SetPosition(const glm::vec2& pos) noexcept;
        void SetPosition(float x, float y) noexcept;
        void SetRotation(float rotation) noexcept;
        void Translate(const glm::vec2& amount) noexcept;
        void Translate(float x, float y) noexcept;
        void Rotate(float amount) noexcept;

        float Rotation() const noexcept;
        const glm::vec2& Position() const noexcept;
        const glm::mat4& Combined() const noexcept;
        const glm::mat4& View() const noexcept;
        const glm::mat4& Proj() const noexcept;
    private:
        float mRotation;
        glm::vec2 mPosition;

        // Transformation and projection matrices
        glm::mat4 mCombined;
        glm::mat4 mView;
        glm::mat4 mProj;

        float mSize;
        Viewport* mViewport;
    };
}

#endif
