#ifndef GAMEENGINE_IGAMEACTOR_H
#define GAMEENGINE_IGAMEACTOR_H

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphic/SpriteAnimator.h"

// TODO класс для представления интерфейсов всех акторов движка


namespace GameObjects {

    /*!
* \addtogroup Game_Objects logic of game objects
* @{ \details Класс для представления интерфейса всех игровых объектов
*/
                    /*!
                     * Возможные действия игрока
                     */
    enum class ACTION {
        IDLE,       ///< Анимация в режиме "Стоять"
        WALK,       ///< Анимация в режиме "Идти"
        SHOOTING,   ///< Анимация в режиме "Стрельба"
        RELOAD,    ///< Анимация в режиме "Перезарядка"
        DIE         ///< Анимация в режиме "Смерть"
    };

    struct IGameActor {
    public:
        IGameActor(glm::vec2 position, glm::vec2 size, float rotation, float layer);

        virtual ~IGameActor() = default;
               /*!
               * Задать анимацию врага
               * @param name_of_action имя акта
               * @param anim название анимации
               */
        virtual void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator> anim) = 0;
                /*!
                 * Гетер для получения вектора спрайтов (которые представляют из себя покадрываю анимацию)
                 * @param action действие
                 * @return указатель на набор спрайтов этого действия (анимацию)
                 */
        virtual std::shared_ptr<Graphic::SpriteAnimator> GetAnimator(ACTION action);
                    /*!
                     * Рендер объекта
                     */
        virtual void Render() = 0;
                    /*!
                     * Проверка на смерть
                     * @return true/false (умер ли?)
                     */
        virtual bool die() = 0;

        virtual inline void setVelocity(float vel) {
            m_velocity = vel;
        }

        [[nodiscard]] virtual inline glm::vec2 &GetCurrentPosition() {
            return m_position;
        };

        [[nodiscard]] virtual inline glm::vec2 &GetCurrentDirection() {
            return m_direction;
        }

        [[nodiscard]] virtual inline glm::vec2 &GetSize() {
            return m_size;
        }

        [[nodiscard]] virtual inline float &velocity() {
            return m_velocity;
        }

    protected:
        std::map<ACTION, std::shared_ptr<Graphic::SpriteAnimator>> m_representative;

        glm::vec2 m_position;
        glm::vec2 m_size;
        float m_rotation;
        float m_layer;

        glm::vec2 m_direction{};
        glm::vec3 m_up{0.f, 0.f, 1.f};
        float m_velocity{};
    };
    /*! @} */
}

#endif //GAMEENGINE_IGAMEACTOR_H
