#ifndef GAMEENGINE_INDEXBUFFER_H
#define GAMEENGINE_INDEXBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

                /*!
                 * \defgroup ENGINE_GRAPHIC primitives of graphic logic
                 * @{ \details Класс необходимой для инкапсулированной работы индексного буфера
                 */

namespace Graphic {
    struct IndexBuffer {
    public:
        IndexBuffer(const void * data, size_t size, unsigned int usage);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer &) = delete;
        IndexBuffer& operator=(const IndexBuffer &) = delete;
        IndexBuffer(IndexBuffer&&) noexcept;
        IndexBuffer& operator=(IndexBuffer&&) noexcept;
                /*!
                 * Изменить данные индексного буфера, которые уже переданны на память видеокарты
                 * @param data новые данные
                 * @param size размер от 0 до size, кт будет заменен
                 */
        void Reset(const void * data, size_t size);
                /*!
               * Привязать текущий индексный буффер к текщуему состоянию OpenGL
               */
        void bind();
                /*!
               * Отвязать текущий индексный буффер от текщуего состояния OpenGL
               */
        void unbind();

        [[nodiscard]] inline unsigned int GetId() const {
            return ID;
        }
        [[nodiscard]] inline unsigned int GetSize() const {
            return m_numbers;
        }
    private:
        unsigned int ID;
        size_t m_numbers;
    };
}
            /*! @} */

#endif //GAMEENGINE_INDEXBUFFER_H
