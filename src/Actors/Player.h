#ifndef GAMEENGINE_PLAYER_H
#define GAMEENGINE_PLAYER_H

#include <set>

#include "IGameActor.h"
#include "Bullet.h"

// TODO прикрепить также камеру и изменять ее матрицу перемещения в зависимости от перемещения плеера

// TODO присобачить сюда sprite и инициализировать им анимации

// TODO хранить значение текущей позиции мышки, получать новую позицию мышку => находить вектор между ними и находить угол между этим вектором и вектором направления персонажа, делать поворот!

namespace GameObjects {

    struct Player : public IGameActor {
    public:
        Player(glm::vec2 position, glm::vec2 size, float rotation, float layer);

        ~Player() override = default;

        void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>) override;

        void SetBullet(std::vector<std::shared_ptr<Graphic::Sprite>>);

        void SetAnimation(ACTION);

        void Render() override;
        bool die() override;

        void UpdateSprite(std::shared_ptr<Graphic::Sprite>);

        void mouse_controller(GLFWwindow* window, double xpos, double ypos);
        void keyboard_controller(GLFWwindow *window, float & deltaTime, float & lastFrame);

    private:
        std::shared_ptr<float> health;
        std::vector<std::pair<bool, std::shared_ptr<Bullet>>> bullets;
        size_t bullet_num = 0;

        float lastBullet = 0.f;
        float reload_start = 0.f;

        void SetAction(ACTION act);
        ACTION m_action = ACTION::WALK;
    };
}

#endif //GAMEENGINE_PLAYER_H
