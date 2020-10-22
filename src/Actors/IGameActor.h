#ifndef GAMEENGINE_IGAMEACTOR_H
#define GAMEENGINE_IGAMEACTOR_H

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphic/SpriteAnimator.h"

// TODO класс для представления интерфейсов всех акторов движка

namespace GameObjects {
    enum class ACTION {
        IDLE, WALK, SHOOTING
    };

    struct IGameActor {
    public:
        IGameActor(glm::vec2 position, glm::vec2 size, float rotation, float layer);

        virtual ~IGameActor() = default;

        virtual void SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator>) = 0;
        virtual std::shared_ptr<Graphic::SpriteAnimator> GetAnimator(ACTION action);

        virtual void Render() = 0;

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
}

#endif //GAMEENGINE_IGAMEACTOR_H
