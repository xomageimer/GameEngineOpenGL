#ifndef GAMEENGINE_VERTEXARRAY_H
#define GAMEENGINE_VERTEXARRAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

                     /*!
                     * \addtogroup ENGINE_GRAPHIC
                     * @{ \details Класс для инкапсулирования логики вершинного массива glfw
                     */

namespace Graphic {
    struct VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray &) = delete;
        VertexArray& operator=(const VertexArray &) = delete;
        VertexArray(VertexArray&&) noexcept;
        VertexArray& operator=(VertexArray&&) noexcept;

                        /*!
                         * Задать вершинный атрибут для массива (можно не задать явно ничего)
                         * @param index индентификатор атрибута внутри буффера
                         * @param size задает размер компонента
                         * @param stride шаг
                         * @param type задает тип компонента
                         * @param normalized в нормализированных ли координатах?
                         * @param offset смещение в массиве
                         * @return последний номер атрибута текущего вершинного массива
                         */
        size_t SetVertexAttrib(size_t index = 0,
                               size_t size = 3,
                               size_t stride = 0 * sizeof(float),
                               unsigned int type = GL_FLOAT,
                               bool normalized = GL_FALSE,
                               const void * offset = nullptr);
                        /*!
                         * связать текущий массив вершин с состоянием OpenGL
                         */
        void bind();

                        /*!
                         * Отвязать текущий массив вершин от состояния OpenGL
                         */
        void unbind();

                        /*!
                         * активировать все атрибуты
                         */
        void EnableAllAttrib();
                         /*!
                         * деактивировать все атрибуты
                         */
        void DisableAllAttrib();
                        /*!
                         * активировать конкретный атрибут
                         */
        bool EnableAttrib(size_t i);
                    /*!
                     * деактивировать конкретный атрибут
                     */
        bool DisableAttrib(size_t i);

        [[nodiscard]] inline unsigned int GetId() const {
            return ID;
        }
                    /*!
                     * получить последний добавленный атрибут
                     * @return последний атрибут
                     */
        [[nodiscard]] inline size_t GetLastAttrib() const {
            return m_last_attrib;
        }

    private:
        unsigned int ID;
        size_t m_last_attrib;
    };

}
                                /*! @} */

#endif //GAMEENGINE_VERTEXARRAY_H
