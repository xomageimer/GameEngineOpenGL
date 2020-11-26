#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphic/Shader.h"

                    /*!
                     * \addtogroup ENGINE_INTERFACE camera logic
                     * @{ \details Класс для представления логики игровой камеры
                     */

struct Camera {
public:
    Camera(const Camera &) = delete;
    Camera& operator=(const Camera &) = delete;
    Camera(Camera &&) = delete;
    Camera& operator=(Camera &) = delete;

    Camera(std::shared_ptr<Shader> shrd);
                /*!
                 * Задать новую позицию камеры
                 * @param NewCameraPos новая позиция камеры
                 */
    void SetPos (const glm::vec2 & NewCameraPos);

                /*!
                 * Отрендерить новое положение сцены относительно точки камеры
                 */
    void Render();

private:
    glm::vec3 CameraPos = {0.f, 0.f, 3.f};
    glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);;

    std::shared_ptr<Shader> m_shader;
};
                /*! @} */

#endif //GAMEENGINE_CAMERA_H
