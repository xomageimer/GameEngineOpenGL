#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Actors/Quad.h>
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Bullet.h"
#include "Camera.h"

struct Engine {
public:
    static Engine& Editor();
    void Render();
    Engine(Engine&) = delete;
    Engine& operator=(Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void ConfigPlayerAnim(GameObjects::ACTION act, const std::string & sprite_name, const std::vector<std::vector<float>> & sprite_frames);
    void ConfigPlayerParticles(const std::string & sprite_name);
    inline void SetPlayer(glm::vec2 position, glm::vec2 size, float rotation, float layer){
        player_controller.reset();
        player_controller = std::make_shared<GameObjects::Player>(position, size, rotation, layer);
    };
    [[nodiscard]] inline std::shared_ptr<GameObjects::Player> & GetPlayerController() {
        return player_controller;
    }

    void SetMap(glm::vec2 position, glm::vec2 size);
    void ConfigSpriteMap(const std::string & sprite_name);

    void SetProp(glm::vec2 position, glm::vec2 size);
    void ConfigSpriteProp(const std::string & sprite_name);

    void SetEnemiesSpawn();
    void SetEnemies();

    void SetSprite(const std::string & name,
                   const std::string & texture_name);

    void SetSpritePack(const std::string & name,
                   const std::string & texture_name, size_t max_count);

    void SetTexture(const std::string& name,
                    const std::filesystem::path &,

                    unsigned int type = GL_RGBA,
                    unsigned int format = GL_RGBA,
                    bool flip_vertically = true);

    void SetShader(const std::filesystem::path & vertex_shader, const std::filesystem::path & fragment_shader);

    void SetCameraUpdatePosition();

private:
    Engine() = default;

    std::shared_ptr<Shader> m_shader;

    std::shared_ptr<GameObjects::Player> player_controller = nullptr;
    std::shared_ptr<GameObjects::Quad> map;
    std::vector<std::shared_ptr<GameObjects::Quad>> props ;
    std::set<std::shared_ptr<GameObjects::Enemy>> enemies;

    std::map<std::string, std::shared_ptr<Graphic::Sprite>> pool_sprites;
    std::map<std::string, std::vector<std::shared_ptr<Graphic::Sprite>>> pool_pack_sprites;
    std::map<std::string, std::shared_ptr<Graphic::Texture2D>> pool_textures;

    std::shared_ptr<Camera> m_cam;
};


#endif //GAMEENGINE_ENGINE_H
