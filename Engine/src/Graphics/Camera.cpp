#include "Engine/Graphics/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
    OrthographicCamera::OrthographicCamera(Viewport* viewport, float size)
        :
        mViewport(viewport),
        mSize(size),
        mRotation(0.0f),
        mPosition({ 0.0f, 0.0f })
    {
        Update();
    }

    void OrthographicCamera::Update() noexcept
    {
        float w = mSize * mViewport->Aspect();

        mView = 
            glm::rotate(glm::mat4(1.0f), -mRotation, { 0.0f, 0.0f, 1.0f }) *
            glm::translate(glm::mat4(1.0f), { -mPosition.x, -mPosition.y, 0.0f });
        mProj = glm::ortho(-w / 2.0f, w / 2.0f, -mSize / 2.0f, mSize / 2.0f);
        mCombined = mProj * mView;
    }


    void OrthographicCamera::SetPosition(float x, float y) noexcept
    {
        mPosition.x = x;
        mPosition.y = y;
    }
    void OrthographicCamera::Translate(float x, float y) noexcept
    {
        mPosition.x += x;
        mPosition.y += y;
    }
    void OrthographicCamera::SetPosition(const glm::vec2& pos) noexcept { mPosition = pos; }
    void OrthographicCamera::SetRotation(float rotation) noexcept { mRotation = rotation; }
    void OrthographicCamera::Translate(const glm::vec2& amount) noexcept { mPosition += amount; }
    void OrthographicCamera::Rotate(float amount) noexcept { mRotation += amount; }
    float OrthographicCamera::Rotation() const noexcept { return mRotation; }
    const glm::vec2& OrthographicCamera::Position() const noexcept { return mPosition; }
    const glm::mat4& OrthographicCamera::Combined() const noexcept { return mCombined; }
    const glm::mat4& OrthographicCamera::View() const noexcept { return mView; }
    const glm::mat4& OrthographicCamera::Proj() const noexcept { return mProj; }
}
