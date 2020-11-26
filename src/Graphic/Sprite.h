#ifndef GAMEENGINE_SPRITE_H
#define GAMEENGINE_SPRITE_H

#include <memory>
#include <optional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "Buffers.h"


// TODO все данные должны быть тут, в акторах можно реализовать логику/управление/рендер всего прочего

// TODO может быть получиться вытащить маттрицу модели наружу а тут лишь отдавать ее в шейдер
// TODO придумать как задавать размер

namespace Graphic {

    /*!
* \defgroup ENGINE_SMART_GRAPHIC_OBJECT smart objects of graphic logic
* @{ \details Класс необходимой для создания спрайтов
*/

    class Sprite {
    public:
                                        /*!
                                         * Задать текстуру и шейдер для текущего спрайта
                                         */
        Sprite(std::shared_ptr<Texture2D>, std::shared_ptr<Shader>);
        ~Sprite() = default;

        Sprite(const Sprite &) = delete;
        Sprite& operator=(const Sprite &) = delete;

        Sprite(Sprite &&) noexcept;
        Sprite& operator=(Sprite&&) noexcept;
                                        /*!
                                         * Сгенерировать спрайт
                                         * принимает в себя данные голого вершинного буфера и голого индексного буфера
                                         */
        void Init(const void *data_vert,
                          size_t size_vert,
                          unsigned int usage_vert,
                          const void *data_indic,
                          size_t size_indic,
                          unsigned int usage_indic);
                                        /*!
                                         * Задать текстурный атлас, что по сути заменяет спрайт на представление текстурного атласа
                                         * принимает в себя координаты на атласе представляющие отдельный спрайт
                                         */
        void SetSpriteSheet(const std::vector<float> & vec);
                                        /*!
                                         * отрисовать текущий спрайт
                                         * инкапсулированность позволяет вызвать только этот метод чтобы выполнить задачу
                                         */
        void draw();

        [[nodiscard]] inline std::shared_ptr<Texture2D> GetTexture(){
            return m_texture;
        }
        [[nodiscard]] inline std::shared_ptr<Shader> GetShader(){
            return m_shader;
        }
        [[nodiscard]] inline const std::vector<float> & GetCoords() const{
            return *textureCoords;
        }
        [[nodiscard]] inline glm::vec2 & GetCenter(){
            return m_center;
        }
        [[nodiscard]] inline glm::vec2 & GetSize(){
            return m_size;
        }
        [[nodiscard]] inline float & GetRotation(){
            return m_rotation;
        }
        [[nodiscard]] inline float & GetLayer(){
            return m_layer;
        }

    private:
        glm::vec2 m_center {0.f, 0.f};
        glm::vec2 m_size {1.0f, 1.0f};
        float m_rotation = 90.f;
        float m_layer = 0.0f;

        std::shared_ptr<Texture2D> m_texture;
        std::shared_ptr<Shader> m_shader;

        std::optional<VertexArray> m_vao;
        std::optional<VertexBuffer> m_vertices_bo;
        std::optional<VertexBuffer> m_textures_bo;
        std::optional<IndexBuffer> m_ebo;

        const std::vector<float> * textureCoords = nullptr;
    };
    /*! @} */
}

#endif //GAMEENGINE_SPRITE_H
