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
    player_controller->Render();
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
}

