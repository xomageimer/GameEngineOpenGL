#include "Bullet.h"


GameObjects::Bullet::Bullet(glm::vec2 & position, glm::vec2 size, float & rotation, glm::vec2 & direct, float layer) : IGameActor(position, size, rotation, layer), current_target(position), rotation(rotation), direct(direct) {
    m_direction = direct;
}


void GameObjects::Bullet::Update(std::shared_ptr<Graphic::Sprite> sprite) {
    float currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
    m_position += (m_direction * m_velocity *_deltaTime);
    sprite->GetCenter() = m_position;
    sprite->GetSize() = m_size;
    sprite->GetRotation() = m_rotation;
    sprite->GetLayer() = m_layer;
}


void GameObjects::Bullet::SetAnimator(GameObjects::ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator> anim) {
    auto it = this->m_representative.emplace(name_of_action, anim);
    float vertices[] = {
            1.f, 1.f, 0.f,
            1.f, -1.f, 0.f,
            -1.f, -1.f, 0.f,
            -1.f, 1.f, 0.f
    };
    const int indices[] {
            0, 1, 3,
            1, 2, 3
    };
    it.first->second->GetSprite()->Init(vertices, sizeof(vertices), GL_DYNAMIC_DRAW, indices, sizeof(indices), GL_DYNAMIC_DRAW);
}

void GameObjects::Bullet::SetSprite(std::shared_ptr<Graphic::SpriteAnimator> sprite_animator) {
    this->SetAnimator(m_action, sprite_animator);
}

void GameObjects::Bullet::Render() {
    auto it = m_representative[m_action];
    Update(it->GetSprite());
    it->AnimationUpdate();
}

bool GameObjects::Bullet::die() {
    float m_curlifetime = glfwGetTime();
    return m_curlifetime - m_lasttime >= 3.f || !active;
}

void GameObjects::Bullet::diactivate() {
    active = false;
}
