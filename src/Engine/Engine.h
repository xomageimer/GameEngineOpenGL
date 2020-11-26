#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Actors/Quad.h>
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Bullet.h"
#include "Camera.h"

                    /*!
                     * \file
                     * \brief Основное представление интерфейса движка TOP DOWN шутера
                     *
                     * Данный файл содержит в себе определения интерфейсных методов для сборки
                     * и построения игры.
                     */

                    /*!
                     * \defgroup ENGINE_INTERFACE engine logic
                     * @{ \details Класс для представления логики игрового движка
                     */

struct Engine {
public:
                    /*!
                     * Статический метод для инициализации движка путем синглтона Маерса
                     * @return вернет синглтон объект движка
                     */
    static Engine& Editor();
    void Render();
    Engine(Engine&) = delete;
    Engine& operator=(Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;
                    /*!
                     * Функция для конфигурации анимации игрока, задать акт/действие и спрайт на него
                     * Так как поддерживает анимация с помощью текстурного атласа - задавать необходимо изображение
                     * хранящие в себе все анимации (желательно высокого качества).
                     * @param act действие игрока на которое добовляется анимация
                     * @param sprite_name имя изображения-текстурного атласа с покадровой анимацией
                     * @param sprite_frames вектор с координатами анимаций, можно задать пустой и проинициализировать в функции \ref Graphic::SpriteAnimator::SetSheetAtlas
                     */
    void ConfigPlayerAnim(GameObjects::ACTION act, const std::string & sprite_name, const std::vector<std::vector<float>> & sprite_frames);
                    /*!
                     * функция для того чтобы задать спрайты каким-нибудь сокетам плеера (например пули)
                     * @param sprite_name спрайт пули
                     */
    void ConfigPlayerParticles(const std::string & sprite_name);
                    /*!
                     * функция для того чтобы задать текущего плеера
                     * @param position позиция плеера в которой он будет спавниться
                     * @param size размер модели плеера
                     * @param rotation угол начального поворота
                     * @param layer слой \deprecated
                     */
    inline void SetPlayer(glm::vec2 position, glm::vec2 size, float rotation, float layer){
        player_controller.reset();
        player_controller = std::make_shared<GameObjects::Player>(position, size, rotation, layer);
        player_start_pos = position;
    };
                    /*!
                     * Гетер текущего плеера
                     * @return указатель на плеера
                     */
    [[nodiscard]] inline std::shared_ptr<GameObjects::Player> & GetPlayerController() {
        return player_controller;
    }
                    /*!
                     * Функция проверяющая смерть игрока и выводящая в этом случае "You Dead!"
                     * Также отвечает за перерес игрока
                     */
    void PlayerDeadChecker();

                    /*!
                     * Метод для того чтобы задать размер и время рестарта в случае смерти
                     * @param size размер
                     * @param timer_to_restart время до рестарта
                     */
    void SetDeadSign(glm::vec2 size = {1.f, 1.f}, float timer_to_restart = 3.f);
                    /*!
                     * Конфигурация таблички (спрайта) которая появится в случае смерти игрока
                     * @param sprite_name спрайт
                     */
    void ConfigSpriteDeadSign(const std::string & sprite_name);
                    /*!
                     * Метод для того чтобы задать размер окна паузы
                     * @param size размер
                     */
    void SetPauseSign(glm::vec2 size = {1.f, 1.f});
                    /*!
                     * Метод для того чтобы задать спрайт окна паузы
                     * @param sprite_name спрайт
                     */
    void ConfigSpritePauseSign(const std::string & sprite_name);
                    /*!
                     * Проверка на нажатие кнопки p (для активации паузы), а также ее вывода и отмены
                     * @param window указатель на текущий window OpenGL состояния
                     * @return флаг активаирована ли пауза или нет
                     */
    bool CheckPauseMode(GLFWwindow *window);
                    /*!
                     * Задать позицию и размер фона (карты)
                     * @param position позиция
                     * @param size размер
                     */
    void SetMap(glm::vec2 position, glm::vec2 size);
                    /*!
                     * Конфигурация фона спрайтом
                     * @param sprite_name спрайт
                     */
    void ConfigSpriteMap(const std::string & sprite_name);

                    /*!
                     * задать пропы (деревья в случае с примером)
                     * @param position позиия
                     * @param size размер
                     */
    void SetProp(glm::vec2 position, glm::vec2 size);
                    /*!
                     * Задать спрайт для пропа
                     * @param sprite_name спрайт
                     */
    void ConfigSpriteProp(const std::string & sprite_name);
                    /*!
                     * Задать точки спавана врагов
                     * @param spawn_pos массив координат спавнов
                     */
    void SetEnemiesSpawns(std::vector<glm::vec2> spawn_pos);
                    /*!
                     * Задать параметры для врагов
                     */
    void SetEnemies(glm::vec2 size, float layer, size_t numbers);
                    /*!
                     * Конфигуратор врага
                     * @param act действие врага
                     * @param sprite_name текстурный атлас с анимациями
                     * @param left_bottom левая нижняя граница
                     * @param right_top правая верхняя граница
                     * @param x смещение по x вдоль всей текстуры
                     * @param y смещение по y вдоль текстуры
                     * @param vertical количество спрайтов на текстуре по вериткале
                     * @param horizontal количество спрайтов на текстуре по горизонтале
                     */
    void ConfigEnemies(GameObjects::ACTION act, const std::string & sprite_name, glm::vec2 left_bottom,
                       glm::vec2 right_top,
                       float x,
                       float y,
                       size_t vertical,
                       size_t horizontal);
                    /*!
                     * Функция установки спрайта в массив игровых спрайтов
                     * @param name имя спрайта
                     * @param texture_name имя текстуры, которая должна находиться в буффере для текстур
                     */
    void SetSprite(const std::string & name,
                   const std::string & texture_name);

    void SetSpritePack(const std::string & name,
                   const std::string & texture_name, size_t max_count);

                    /*!
                     * добавление текустуры в буффер текстур (своеобразный паттерн объектный пул)
                     * @param name имя текстуры в буффере
                     * @param type тип для изображения (A - альфа канал)
                     * @param format формат передаваемого изображения
                     * @param flip_vertically необходимость в развороте, так как библиотека поворачивает изображение
                     */
    void SetTexture(const std::string& name,
                    const std::filesystem::path &,

                    unsigned int type = GL_RGBA,
                    unsigned int format = GL_RGBA,
                    bool flip_vertically = true);

                    /*!
                     * Функция для присоединения шейдеров
                     * @param vertex_shader вершинный шейдер
                     * @param fragment_shader фрагментный шейдер
                     */
    void SetShader(const std::filesystem::path & vertex_shader, const std::filesystem::path & fragment_shader);

                    /*!
                     * Задать новую позицию камеры
                     */
    void SetCameraUpdatePosition();

private:
    Engine() = default;

    std::shared_ptr<Shader> m_shader;

    std::shared_ptr<GameObjects::Player> player_controller = nullptr;
    glm::vec2 player_start_pos;
    std::shared_ptr<GameObjects::Quad> map;
    std::shared_ptr<GameObjects::Quad> DeadSign;
    std::shared_ptr<GameObjects::Quad> PauseSign;
    std::vector<std::shared_ptr<GameObjects::Quad>> props;

    float StartDeathTime = 0.f;
    bool is_Dead = false;
    float deltaTime;
    bool On_Pause = false;

    std::vector<std::shared_ptr<GameObjects::Enemy>> enemies;

    std::map<std::string, std::shared_ptr<Graphic::Sprite>> pool_sprites;
    std::map<std::string, std::vector<std::shared_ptr<Graphic::Sprite>>> pool_pack_sprites;
    std::map<std::string, std::shared_ptr<Graphic::Texture2D>> pool_textures;

    std::shared_ptr<Camera> m_cam;
};

                         /*! @} */

#endif //GAMEENGINE_ENGINE_H
