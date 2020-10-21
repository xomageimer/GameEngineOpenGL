#include "IGameActor.h"

GameObjects::IGameActor::IGameActor(glm::vec2 position,
                                    glm::vec2 size,
                                    float rotation,
                                    float layer)
        : m_position(position),
          m_size(size),
          m_rotation(rotation),
          m_layer(layer)
{

}

std::shared_ptr<Graphic::SpriteAnimator> GameObjects::IGameActor::GetAnimator(ACTION action) {
    return this->m_representative.at(action);
}
