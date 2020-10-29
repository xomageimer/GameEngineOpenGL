#ifndef GAMEENGINE_QUAD_H
#define GAMEENGINE_QUAD_H

#include "IGameActor.h"


namespace GameObjects {
    struct Quad : public IGameActor {
    public:
        Quad(glm::vec2 position, glm::vec2 size, float rotation = 0.f, float layer = -1.f);

        ~Quad() = default;

        void SetSprite(std::shared_ptr<Graphic::SpriteAnimator>);

        void UpdateSprite(std::shared_ptr<Graphic::Sprite> sprite);

        void SetPosition(glm::vec2 new_pose);

        void Render() override;

    private:
      void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>) override;
      bool die() override;
      static inline const ACTION m_action = ACTION::IDLE;
        // коллизия
    };
}


#endif //GAMEENGINE_QUAD_H
