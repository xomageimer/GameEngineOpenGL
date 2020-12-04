#include "Enemy.h"

std::random_device rd;
std::mt19937 mersenne (rd());

GameObjects::Enemy::Enemy(glm::vec2 position, glm::vec2 size, float rotation, float layer) : IGameActor(position, size,
                                                                                                        rotation,
                                                                                                        layer) {

}

void GameObjects::Enemy::Update() {
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    m_direction = glm::normalize(*current_target - m_position);
    if (!this->die()){
        for (auto & i : *bulls){
            if (!i.second->die()) {
                if (std::abs(i.second->GetCurrentPosition().x - m_position.x) <= 0.12f &&
                        std::abs(i.second->GetCurrentPosition().y - m_position.y) <= 0.12f) {
                    health -= damage;
                    i.second->diactivate();
                }
            }
        }
    }
    if (this->die())
    {
        if (reload_spawn >= 0.6f) {
            this->Respawn();
            reload_spawn = 0.f;
        }
        reload_spawn += m_deltaTime * m_velocity;
        m_layer = -0.5f;
        m_action = ACTION::DIE;
    }
    else {
        m_rotation = atan2f(m_direction.y, m_direction.x) ;
        m_action = ACTION::WALK;
        reload_start += m_deltaTime * m_velocity;
        if (std::abs(current_target->x - m_position.x) <= 0.12f && std::abs(current_target->y - m_position.y) <= 0.12f) {
            m_action = ACTION::SHOOTING;
            if (reload_start >= 0.4f) {
                *current_health -= get_damage;
                reload_start = 0.f;
            }
        } else {
            m_position += (m_direction * m_velocity * m_deltaTime);
        }
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
    return health < 0;
}

void GameObjects::Enemy::Render() {
    this->Update();
    auto it = m_representative[m_action];
    UpdateSprite(it->GetSprite());
    it->AnimationUpdate();
}

void GameObjects::Enemy::Respawn() {
    m_direction = glm::vec2(0.f, 0.f);
    m_action = ACTION::WALK;
    health = 100.f;
    m_position = my_spawn[ mersenne() % my_spawn.size()];
}

void GameObjects::Enemy::SetSpawn(std::vector<glm::vec2> spawn) {
    my_spawn = spawn;
}

void GameObjects::Enemy::Stop() {
    m_lastFrame = glfwGetTime();
}

void GameObjects::Enemy::SetDamage(float dmg) {
    damage = dmg;
}

void GameObjects::Enemy::SetHp(float hp) {
    health = hp;
}

void GameObjects::Enemy::SetDamageReceived(float dmg) {
    get_damage = dmg;
}
