//
// Created by xomag on 16.10.2020.
//

#include "Enemy.h"

GameObjects::Enemy::Enemy(glm::vec2 position, glm::vec2 size, float rotation, float layer) : IGameActor(position, size,
                                                                                                        rotation,
                                                                                                        layer) {

}

void GameObjects::Enemy::Update() {
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    m_rotation = atan2f(current_target->y, current_target->x);
    m_direction = glm::normalize(*current_target);
    for (auto & i : *bulls){
        if (i.second->GetCurrentPosition().x <= m_position.x + m_size.x && i.second->GetCurrentPosition().x <= m_position.y + m_size.y){
            this->die();
        }
    }
    if (m_position.x <= 0.2f || m_position.y <= 0.2f) {
        m_action = ACTION::SHOOTING;
        if (reload_start >= 0.07f) {
            *current_health -= 33.f;
            reload_start = 0.f;
        }
        reload_start += m_deltaTime  * m_velocity;
    } else {
        m_action = ACTION::WALK;
        m_position += (m_direction * m_velocity * m_deltaTime);
    }
}

void GameObjects::Enemy::SetAction(GameObjects::ACTION act) {
    m_action = act;
}


void GameObjects::Enemy::SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator> anim) {
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

void GameObjects::Enemy::UpdateSprite(std::shared_ptr<Graphic::Sprite> sprite) {
    sprite->GetCenter() = m_position;
    sprite->GetSize() = m_size;
    sprite->GetRotation() = m_rotation;
    sprite->GetLayer() = m_layer;
}

bool GameObjects::Enemy::die() {
    Respawn();
    return true;
}

void GameObjects::Enemy::Render() {
    this->Update();
    auto it = m_representative[m_action];
    UpdateSprite(it->GetSprite());
    it->AnimationUpdate();
}

void GameObjects::Enemy::Respawn() {
    m_position = my_spawn;
}

void GameObjects::Enemy::SetSpawn(glm::vec2 spawn) {
    my_spawn = spawn;
}
