#ifndef GAMEENGINE_ENEMY_H
#define GAMEENGINE_ENEMY_H

#include "IGameActor.h"

namespace GameObjects {

    struct Enemy : IGameActor {
    public:
        Enemy(glm::vec2 position, glm::vec2 size, float rotation = 0.f, float layer = 1.f);
        Enemy(const Enemy&) = default;
        Enemy& operator=(const Enemy&) = default;
        Enemy(Enemy&&) = default;
        Enemy& operator=(Enemy&&) = default;

        inline void SetPlayerTarget(std::shared_ptr<glm::vec2> targ, std::shared_ptr<float> targ_health){
            current_health = targ_health;
            current_target = targ;
        };

        void SetSpawn(glm::vec2 spawn);

        void Render() override;

        void UpdateSprite(std::shared_ptr<Graphic::Sprite>);

        void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator> anim) override;

        void Update();

        void Respawn();

        bool die() override;

    private:
        glm::vec2 my_spawn;

        std::shared_ptr<const glm::vec2> current_target;
        std::shared_ptr<float> current_health;

        float m_deltaTime;
        float m_lastFrame = 0.f;

        void SetAction(ACTION act);
        ACTION m_action = ACTION::WALK;
    };

}


#endif //GAMEENGINE_ENEMY_H
