#ifndef GAMEENGINE_SPRITEANIMATOR_H
#define GAMEENGINE_SPRITEANIMATOR_H

// TODO класс обработчик анимации (по факту должен как-то итерироваться по одному изображению с кучей шитов (между этими шитами))

#include <memory>
#include "Sprite.h"



namespace Graphic {
    /*!
     * \addtogroup ENGINE_SMART_GRAPHIC_OBJECT
     * @{ \details Класс для определения анимации игровых объектов
     */
    struct SpriteAnimator {
    public:
                /*!
                 * Конструктор аниматора
                 * @param sprite текстурный атлас
                 */
        explicit SpriteAnimator(std::shared_ptr<Sprite> sprite, const std::vector<std::vector<float>> &);
        ~SpriteAnimator() = default;

        SpriteAnimator(const SpriteAnimator &) = default;
        SpriteAnimator& operator=(const SpriteAnimator &) = default;
                /*!
                 * Задать спрайт - часть анимации (кадр)
                 * @param left_bottom левая нижняя граница
                 * @param right_top правая верхняя
                 */
        void SetSheet(const glm::vec2 &left_bottom, const glm::vec2 &right_top);
                    /*!
                     * Сгенерировать из всего текстурного атласа кадры
                     * @param left_bottom левая нижняя граница
                     * @param right_top правая верхняя
                     * @param x смещение по x
                     * @param y смещение по y
                     * @param vertical кол-во кадров по вертикале
                     * @param horizontal кол-во кадров по горизонтале
                     */
        void SetSheetAtlas(glm::vec2 left_bottom, glm::vec2 right_top, float x,
                           float y, size_t vertical, size_t horizontal);
                     /*!
                      * Обновить кадр
                      */
        void AnimationUpdate();
                    /*!
                     * Очистить текщий аниматор от кадров
                     */
        void ClearAnimPack();

        [[nodiscard]] inline const std::vector<std::vector<float>> & GetAnim() const {
            return animation;
        }
        [[nodiscard]] inline std::shared_ptr<Sprite> GetSprite() {
            return m_sprite;
        }
        inline void SetSpeed(float new_speed) {
            speed = new_speed;
        }

    private:
        float prev_anim = 0.f;
        float speed = 0.05f;
        size_t current_sheet = 0;

        std::shared_ptr<Sprite> m_sprite;

        std::vector<std::vector<float>> animation;
    };
    /*! @} */
}

#endif //GAMEENGINE_SPRITEANIMATOR_H
