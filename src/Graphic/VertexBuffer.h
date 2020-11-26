#ifndef GAMEENGINE_VERTEXBUFFER_H
#define GAMEENGINE_VERTEXBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

                    /*!
                    * \addtogroup ENGINE_GRAPHIC
                    * @{ \details Класс для инкапсулирования логики вершинного буффера данных glfw
                    */

namespace Graphic {

    struct VertexBuffer {
    public:
                    /*!
                     * Конструктор
                     * @param data массив данных (координаты вершин например)
                     * @param size размер массива
                     * @param usage предполагаемый паттерн использования буфера
                     */
        VertexBuffer(const void * data, size_t size, unsigned int usage);

        VertexBuffer(const VertexBuffer &) = delete;
        VertexBuffer& operator=(const VertexBuffer &) = delete;

        VertexBuffer(VertexBuffer&&) noexcept;
        VertexBuffer& operator=(VertexBuffer &&) noexcept;
                    /*!
                     * Заменить значения вершинного буфера
                     * @param data данные
                     * @param size размер
                     */
        void Reset(const void * data, size_t size);
                    /*!
                     * связать текущий буффер с состоянием OpenGL
                     */
        void bind();
                    /*!
                     * отвязать текущий буффер от состояния OpenGL
                     */
        void unbind();

        ~VertexBuffer();

        [[nodiscard]] inline unsigned int GetId() const {
            return ID;
        }

    private:
        unsigned int ID{};
    };

}
                                /*! @} */

#endif //GAMEENGINE_VERTEXBUFFER_H
