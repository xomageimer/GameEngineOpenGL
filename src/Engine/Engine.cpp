#include "Engine.h"

Engine &Engine::Editor()  {
    static Engine engine = Engine();
    return engine;
}

void Engine::ConfigPlayerAnim(GameObjects::ACTION act, const std::string & sprite_name,
                          const std::vector<std::vector<float>> & sprite_frames) {
    auto it = pool_sprites.find(sprite_name);
    if (it != pool_sprites.end()) {
        player_controller->SetAnimator(act, std::make_shared<Graphic::SpriteAnimator>(it->second, sprite_frames));
    }
    else {
        std::cerr << "NO IMPL" << std::endl;
    }
}

void Engine::Render() {
    m_shader->use();
    SetCameraUpdatePosition();
    map->Render();
    m_cam->Render();
    player_controller->Render();
    for (auto i : props)
        i->Render();
}

void Engine::SetSprite(const std::string & name,
                       const std::string & texture_name) {
    auto it_texture = pool_textures.find(texture_name);
    if (it_texture != pool_textures.end()) {
        pool_sprites.emplace(name, std::make_shared<Graphic::Sprite>(it_texture->second, m_shader));
    }
}

void Engine::SetTexture(const std::string& name,
                        const std::filesystem::path & path_to_texture,
                        unsigned int type,
                        unsigned int format,
                        bool flip_vertically) {
    pool_textures.emplace(name, std::make_shared<Graphic::Texture2D>(path_to_texture, type, format, flip_vertically));
}

void Engine::SetShader(const std::filesystem::path &vertex_shader, const std::filesystem::path &fragment_shader) {
    m_shader = std::make_shared<Shader>(vertex_shader, fragment_shader);
    m_cam = std::make_shared<Camera>(m_shader);
}

void Engine::SetCameraUpdatePosition() {
    this->m_cam->SetPos(this->player_controller->GetCurrentPosition());
}

void Engine::SetMap(glm::vec2 position, glm::vec2 size) {
    map = std::make_shared<GameObjects::Quad>(position, size);
}

void Engine::ConfigSpriteMap(const std::string &sprite_name) {
    map->SetSprite(std::make_shared<Graphic::SpriteAnimator>(pool_sprites.find(sprite_name)->second, std::vector<std::vector<float>>{{1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}}));
}

void Engine::SetProp(glm::vec2 position, glm::vec2 size) {
    props.emplace_back(std::make_shared<GameObjects::Quad>(position, size, 0.f, 0.3f));
}

void Engine::ConfigSpriteProp(const std::string &sprite_name) {
    size_t j = 0;
    for (auto i : props) {
        i->SetSprite(std::make_shared<Graphic::SpriteAnimator>(pool_pack_sprites.find(sprite_name)->second[j++],
                                                            std::vector<std::vector<float>>{{1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}}));
    }
}

void Engine::SetSpritePack(const std::string &name, const std::string &texture_name, size_t max_count) {
    pool_pack_sprites[name].reserve(max_count);
    auto it_texture = pool_textures.find(texture_name);

    if (it_texture != pool_textures.end())
        for (size_t i = 0; i < max_count; i++)
            pool_pack_sprites[name].emplace_back(std::make_shared<Graphic::Sprite>(it_texture->second, m_shader));
}

void Engine::ConfigPlayerParticles(const std::string & name) {
    player_controller->SetBullet(pool_pack_sprites[name]);
}
