#ifndef GAMEENGINE_PLAYER_H
#define GAMEENGINE_PLAYER_H

#include <set>

#include "IGameActor.h"
#include "Bullet.h"

// TODO прикрепить также камеру и изменять ее матрицу перемещения в зависимости от перемещения плеера

// TODO присобачить сюда sprite и инициализировать им анимации

// TODO хранить значение текущей позиции мышки, получать новую позицию мышку => находить вектор между ними и находить угол между этим вектором и вектором направления персонажа, делать поворот!


namespace GameObjects {

                     /*!
                     * \addtogroup Game_Objects
                     * @{ \details Класс для представления логики игрока
                     */

    struct Player : public IGameActor {
    public:
        Player(glm::vec2 position, glm::vec2 size, float rotation, float layer);

        ~Player() override = default;
                    /*!
                     * @ref GameObjects::IGameActor::SetAnimator
                     */
        void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>) override;
                    /*!
                     * Задать пули плееру
                     */
        void SetBullet(std::vector<std::shared_ptr<Graphic::Sprite>>);

        void SetAmmo(size_t num);

        void SetReloadTime(double time);

        void SetAnimation(ACTION act);
                    /*!
                   * @ref GameObjects::IGameActor::Render
                   */
        void Render() override;
                    /*!
                     * @ref GameObjects::IGameActor::die
                     */
        bool die() override;
                    /*!
                     * @ref GameObjects::Enemy::UpdateSprite
                     */
        void UpdateSprite(std::shared_ptr<Graphic::Sprite>);

                    /*!
                     * Геттер текущего HP игрока
                     * @return указатель на HP плеера
                     */
        std::shared_ptr<float> getHealth();
                    /*!
                     * Геттер для пуль плеера
                     * @return вектор из пар свойств: выпущена ли пуля и ссылка на пулю
                     */
        std::vector<std::pair<bool, std::shared_ptr<GameObjects::Bullet>>> & getBullets();
                    /*!
                     * Метод контролля курсора мышки
                     * @param window текущее окно состояния OpenGl
                     * @param xpos позиция мышки по x
                     * @param ypos позиция мышки по y
                     */
        void mouse_controller(GLFWwindow* window, double xpos, double ypos);
                    /*!
                     * Метод контролля нажатия клавиши и мыши
                     * @param window текущее окно состояния OpenGl
                     */
        void keyboard_controller(GLFWwindow *window, float & deltaTime, float & lastFrame);

    private:
        std::shared_ptr<float> health;
        std::vector<std::pair<bool, std::shared_ptr<Bullet>>> bullets;
        size_t bullet_num = 0;

        size_t ammo = 30;

        bool is_reload = false;

        float lastBullet = 0.f;
        float reload_start = 0.f;

        float reload_timer = 0.8f;

        void SetAction(ACTION act);
        ACTION m_action = ACTION::WALK;
    };
    /*! @} */
}

#endif //GAMEENGINE_PLAYER_H
