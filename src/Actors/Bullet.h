#ifndef GAMEENGINE_BULLET_H
#define GAMEENGINE_BULLET_H

#include "IGameActor.h"



namespace GameObjects {
    /*!
               * \addtogroup Game_Objects
               * @{ \details Класс для представления логики пули (сокет игрока)
               */

    struct Bullet : public IGameActor {
    public:
        Bullet(glm::vec2 & position, glm::vec2 size, float & rotation, glm::vec2 & direct, float layer = 0.2f);

                    /*!
                     * Задает спрайт пуле
                     * @param sprite_animator спрайт
                     */
        void SetSprite(std::shared_ptr<Graphic::SpriteAnimator> sprite_animator);
                /*!
              * @ref GameObjects::IGameActor::Render
              */
        void Render() override;
            /*!
            * @ref GameObjects::IGameActor::die
            */
        bool die() override;
                /*!
                * @ref GameObjects::Enemy::Update
                */
        void Update(std::shared_ptr<Graphic::Sprite> sprite);
                /*!
                 * диактивация текущей пули
                 */
        void diactivate();
                /*!
                 * активация текущей пули
                 */
        inline void Activate(){
            active = true;
            m_lasttime = glfwGetTime();
            _lastFrame = glfwGetTime();
            m_position = current_target;
            m_direction = glm::normalize(direct);
            m_rotation = rotation;
            m_velocity = 1.2f;
        }

    private:
            /*!
          * @ref GameObjects::IGameActor::SetAnimator
          */
        virtual void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>);
        float _deltaTime;
        float _lastFrame = 0.f;

        bool active = true;

        float m_curlifetime = 0.f;
        float m_lasttime = 0.f;

        const glm::vec2 & current_target;
        const float & rotation;
        const glm::vec2 & direct;

        const ACTION m_action = ACTION::IDLE;
    };
    /*! @} */
}


#endif //GAMEENGINE_BULLET_H
