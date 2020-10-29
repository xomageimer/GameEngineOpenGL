#include "Quad.h"

GameObjects::Quad::Quad(glm::vec2 position, glm::vec2 size, float rotation, float layer) : IGameActor(position, size,
                                                                                                      rotation, layer) {
}

void GameObjects::Quad::SetAnimator(GameObjects::ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator> anim) {
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
    it.first->second->GetSprite()->GetCenter() = m_position;
    it.first->second->GetSprite()->GetSize() = m_size;
    it.first->second->GetSprite()->GetRotation() = m_rotation;
    it.first->second->GetSprite()->GetLayer() = m_layer;
}

void GameObjects::Quad::SetSprite(std::shared_ptr<Graphic::SpriteAnimator> sprite_animator) {
    this->SetAnimator(m_action, sprite_animator);
}

void GameObjects::Quad::SetPosition(glm::vec2 new_pose) {
    this->m_position = new_pose;
}

void GameObjects::Quad::Render() {
    auto it = m_representative[m_action];
    UpdateSprite(it->GetSprite());
    it->AnimationUpdate();
}

bool GameObjects::Quad::die() {
    std::cerr << "NO IMPL" << std::endl;
    return false;
}

void GameObjects::Quad::UpdateSprite(std::shared_ptr<Graphic::Sprite> sprite) {
    sprite->GetCenter() = m_position;
    sprite->GetSize() = m_size;
    sprite->GetRotation() = m_rotation;
    sprite->GetLayer() = m_layer;
}