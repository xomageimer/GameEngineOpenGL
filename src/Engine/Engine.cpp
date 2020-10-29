#include "Engine.h"

#include <utility>

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
    for (auto i : enemies)
        i->Render();
    for (auto i : props)
        i->Render();
    PlayerDeadChecker();
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
    map->SetSprite(std::make_shared<Graphic::SpriteAnimator>(pool_sprites.find(sprite_name)->second, std::vector<std::vector<float>>{{0.999f, 0.999f, 0.999f, 0.011f, 0.011f, 0.011f, 0.011f, 0.999f}}));
}

void Engine::SetProp(glm::vec2 position, glm::vec2 size) {
    props.emplace_back(std::make_shared<GameObjects::Quad>(position, size, 0.f, 0.3f));
}

void Engine::ConfigSpriteProp(const std::string &sprite_name) {
    size_t j = 0;
    for (auto i : props) {
        i->SetSprite(std::make_shared<Graphic::SpriteAnimator>(pool_pack_sprites.find(sprite_name)->second[j++],
                                                            std::vector<std::vector<float>>{{0.98f, 0.98f, 0.98f, 0.02f, 0.02f, 0.02f, 0.02f, 0.98f}}));
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

void Engine::SetEnemies(glm::vec2 size, float layer, size_t numbers) {
    enemies.reserve(numbers);
    for(size_t i = 0; i < numbers; i++){
        enemies.emplace_back(std::make_shared<GameObjects::Enemy>(glm::vec2{0.f, 0.f}, size, 0.f, layer));
        enemies.back()->SetPlayerTarget(player_controller->GetCurrentPosition(), player_controller->getHealth(), player_controller->getBullets());
        enemies.back()->setVelocity(0.15f);
    }
}

void Engine::ConfigEnemies(GameObjects::ACTION act, const std::string & sprite_name,
                           glm::vec2 left_bottom,
                           glm::vec2 right_top,
                           float x,
                           float y,
                           size_t vertical,
                           size_t horizontal) {
    auto it = pool_pack_sprites.find(sprite_name);
    size_t j = 0;
    if (it == pool_pack_sprites.end()) return;
    for (auto & i : enemies){
        i->SetAnimator(act, std::make_shared<Graphic::SpriteAnimator>(it->second[j++], std::vector<std::vector<float>>{}));
        i->GetAnimator(act)->SetSheetAtlas(left_bottom, right_top, x, y, vertical, horizontal);
        i->GetAnimator(act)->SetSpeed(0.07f);
    }
}

void Engine::SetEnemiesSpawns(std::vector<glm::vec2> spawn_pos) {
    glm::vec2 spawns {2.3f, 2.3f};
    float fract = 0.3f;
    for (size_t i = 0; i < 4; i++){
        spawn_pos.emplace_back(spawns.x + fract, spawns.y);
        spawn_pos.emplace_back(spawns.x, spawns.y + fract);
        spawn_pos.emplace_back(spawns.x - fract, spawns.y);
        spawn_pos.emplace_back(spawns.x, spawns.y - fract);
        spawn_pos.emplace_back(-spawns.x + fract, -spawns.y);
        spawn_pos.emplace_back(-spawns.x, -spawns.y + fract);
        spawn_pos.emplace_back(-spawns.x - fract, -spawns.y);
        spawn_pos.emplace_back(-spawns.x, -spawns.y - fract);
        fract += 0.3f;
    }
    glm::vec2 spawns2 {-2.3f, 2.3f};
    for (size_t i = 0; i < 4; i++){
        fract -= 0.5f;
        spawn_pos.emplace_back(spawns2.x + fract, spawns2.y);
        spawn_pos.emplace_back(spawns2.x, spawns2.y + fract);
        spawn_pos.emplace_back(spawns2.x - fract, spawns2.y);
        spawn_pos.emplace_back(spawns2.x, spawns2.y - fract);
        spawn_pos.emplace_back(-spawns2.x + fract, -spawns2.y);
        spawn_pos.emplace_back(-spawns2.x, -spawns2.y + fract);
        spawn_pos.emplace_back(-spawns2.x - fract, -spawns2.y);
        spawn_pos.emplace_back(-spawns2.x, -spawns2.y - fract);
    }
    for (auto & i : enemies){
        i->SetSpawn(spawn_pos);
        i->Respawn();
    }
}

void Engine::PlayerDeadChecker() {
    if (Engine::Editor().GetPlayerController()->die()) {
        if (!is_Dead) {
            StartDeathTime = glfwGetTime();
            DeadSign->SetPosition(player_controller->GetCurrentPosition());
            is_Dead = true;
        }
        if (glfwGetTime() - StartDeathTime <= deltaTime) {
            DeadSign->Render();
            std::cerr << DeadSign->GetCurrentPosition().x << ' ' << DeadSign->GetCurrentPosition().y << std::endl;
        } else {
            for (auto i : enemies)
                i->Respawn();
            this->player_controller->GetCurrentPosition() = player_start_pos;
            *this->player_controller->getHealth() = 100.f;
            is_Dead = false;
        }
    }
}

void Engine::SetDeadSign(glm::vec2 size, float timer) {
    DeadSign = std::make_shared<GameObjects::Quad>(glm::vec2{0.f, 0.f}, size);
    deltaTime = timer;
}

void Engine::ConfigSpriteDeadSign(const std::string &sprite_name) {
    DeadSign->SetSprite(std::make_shared<Graphic::SpriteAnimator>(pool_sprites.find(sprite_name)->second, std::vector<std::vector<float>>{{0.999f, 0.999f, 0.999f, 0.011f, 0.011f, 0.011f, 0.011f, 0.999f}}));
}

