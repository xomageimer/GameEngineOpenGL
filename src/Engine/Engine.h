#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include "Actors/Player.h"

struct Engine {
public:
    static Engine& Editor();
    void Render();
    Engine(Engine&) = delete;
    Engine& operator=(Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void ConfigPlayerAnim(GameObjects::ACTION act, const std::string & sprite_name, const std::vector<std::vector<float>> & sprite_frames);

    inline void SetPlayer(glm::vec2 position, glm::vec2 size, float rotation, float layer){
        player_controller.reset();
        player_controller = std::make_shared<GameObjects::Player>(position, size, rotation, layer);
    };
    [[nodiscard]] inline std::shared_ptr<GameObjects::Player> & GetPlayerController() {
        return player_controller;
    }

    void SetSprite(const std::string & name,
                   const std::string & texture_name);

    void SetTexture(const std::string& name,
                    const std::filesystem::path &,

                    unsigned int type = GL_RGBA,
                    unsigned int format = GL_RGBA,
                    bool flip_vertically = true);

    void SetShader(const std::filesystem::path & vertex_shader, const std::filesystem::path & fragment_shader);

private:
    Engine() = default;

    std::shared_ptr<Shader> m_shader;

    std::shared_ptr<GameObjects::Player> player_controller = nullptr;
    std::vector<std::shared_ptr<GameObjects::IGameActor>> props;

    std::map<std::string, std::shared_ptr<Graphic::Sprite>> pool_sprites;
    std::map<std::string, std::shared_ptr<Graphic::Texture2D>> pool_textures;
};


#endif //GAMEENGINE_ENGINE_H
