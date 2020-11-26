#ifndef GAMEENGINE_QUAD_H
#define GAMEENGINE_QUAD_H

#include "IGameActor.h"


namespace GameObjects {

    /*!
 * \addtogroup Game_Objects
 * @{ \details Класс для представления статических объектов
 */
    struct Quad : public IGameActor {
    public:
        Quad(glm::vec2 position, glm::vec2 size, float rotation = 0.f, float layer = -1.f);

        ~Quad() = default;
            /*!
             * @ref GameObjects::IGameActor::SetAnimator
             */
        void SetSprite(std::shared_ptr<Graphic::SpriteAnimator>);
            /*!
             * @ref GameObjects::Enemy::UpdateSprite
             */
        void UpdateSprite(std::shared_ptr<Graphic::Sprite> sprite);
                /*!
                * Задать новую позицию
                * @param new_pose новая позиция
                */
        void SetPosition(glm::vec2 new_pose);
            /*!
             * @ref GameObjects::IGameActor::Render
             */
        void Render() override;

    private:
      void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>) override;
      bool die() override;
      static inline const ACTION m_action = ACTION::IDLE;
        // коллизия
    };
    /*! @} */
}




#endif //GAMEENGINE_QUAD_H
