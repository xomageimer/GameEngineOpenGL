#ifndef GAMEENGINE_BULLET_H
#define GAMEENGINE_BULLET_H

#include "IGameActor.h"

namespace GameObjects {

    struct Bullet : public IGameActor {
    public:
        Bullet(glm::vec2 & position, glm::vec2 size, float & rotation, glm::vec2 & direct, float layer = 0.2f);

        void SetSprite(std::shared_ptr<Graphic::SpriteAnimator> sprite_animator);

        void Render() override;

        bool die() override;

        void Update(std::shared_ptr<Graphic::Sprite> sprite);

        inline void Activate(){
            m_lasttime = glfwGetTime();
            _lastFrame = glfwGetTime();
            m_position = current_target;
            m_direction = glm::normalize(direct);
            m_rotation = rotation;
            m_velocity = 0.8f;
        }

    private:
        virtual void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>);
        float _deltaTime;
        float _lastFrame = 0.f;

        float m_curlifetime = 0.f;
        float m_lasttime = 0.f;

        const glm::vec2 & current_target;
        const float & rotation;
        const glm::vec2 & direct;

        const ACTION m_action = ACTION::IDLE;
    };

}
#endif //GAMEENGINE_BULLET_H
