#include "test_engine.h"
#include <sstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    Engine::Editor().GetPlayerController()->mouse_controller(window, xpos, ypos);
}

void processInput(GLFWwindow *window)
{
    if (!Engine::Editor().CheckPauseMode(window))
        Engine::Editor().GetPlayerController()->keyboard_controller(window, deltaTime, lastFrame);
}

void ZombieShooter(GLFWwindow* window){
    std::fstream config_file = (std::filesystem::current_path())/"res"/"config.json";

    std::stringstream ss;
    ss << config_file.rdbuf();

    json j = json::parse(ss.str());
    assert(j["command"] == "configure");

    auto p_set = j["data"]["player"];
    auto e_set = j["data"]["enemy"];

    Engine::Editor().SetPlayer({p_set["Player_Position"]["x"], p_set["Player_Position"]["y"]}, {p_set["Player_Size"]["x"], p_set["Player_Size"]["y"]}, 0.f, 0.f);

    auto Resource_Path = (std::filesystem::current_path())/"res";
    auto Shaders_Path = (std::filesystem::current_path())/"shaders";

    Engine::Editor().SetShader(Shaders_Path/"vertex_shader.glsl", Shaders_Path/"fragment_shader.glsl");
    Engine::Editor().SetTexture("Survivor_Texture", (Resource_Path/"chars/survivor_sec.png"));
    Engine::Editor().SetTexture("Survivor_Texture_Reloading", (Resource_Path/"chars/survivor-reload_rifle.png"));
    Engine::Editor().SetTexture("Zombie_Texture", (Resource_Path/"chars/zombie_sec.png"));
    Engine::Editor().SetTexture("Zombie_Die_Texture", (Resource_Path/"textures/blood.png"));
    Engine::Editor().SetTexture("Bullet_Texture", (Resource_Path/"textures/bullet.png"));
    Engine::Editor().SetTexture("Tree_Texture", (Resource_Path/"textures/tree.png"));
    Engine::Editor().SetTexture("You_Dead_Texture", (Resource_Path/"textures/died.png"));
    Engine::Editor().SetTexture("Pause_Texture", (Resource_Path/"textures/pause.png"));
    Engine::Editor().SetTexture("Map_Texture", (Resource_Path/"textures/map.jpg"), GL_RGB);

    Engine::Editor().SetSprite("Survivor_Walk", "Survivor_Texture");
    Engine::Editor().SetSprite("Survivor_Idle", "Survivor_Texture");
    Engine::Editor().SetSprite("Survivor_Shooting", "Survivor_Texture");
    Engine::Editor().SetSprite("Survivor_Reload", "Survivor_Texture_Reloading");
    Engine::Editor().SetSpritePack("Zombie_Walk","Zombie_Texture", 100);
    Engine::Editor().SetSpritePack("Zombie_Attack", "Zombie_Texture", 100);
    Engine::Editor().SetSpritePack("Zombie_Die", "Zombie_Die_Texture", 100);
    Engine::Editor().SetSpritePack("Bullet", "Bullet_Texture", 50);
    Engine::Editor().SetSpritePack("Tree", "Tree_Texture", 10);
    Engine::Editor().SetSprite("You_Dead", "You_Dead_Texture");
    Engine::Editor().SetSprite("Pause", "Pause_Texture");
    Engine::Editor().SetSprite("Map", "Map_Texture");

    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::WALK, "Survivor_Walk", {});
    Engine::Editor().GetPlayerController()->GetAnimator(GameObjects::ACTION::WALK)->SetSheetAtlas({0.027, 0.82}, {0.24, 0.99}, 0.25f, 0.1665f, 5, 4);
    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::RELOAD, "Survivor_Reload", {});
    Engine::Editor().GetPlayerController()->GetAnimator(GameObjects::ACTION::RELOAD)->SetSheetAtlas({0.027, 0.82}, {0.24, 0.99}, 0.25f, 0.1665f, 5, 4);
    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::IDLE, "Survivor_Idle", {std::vector<std::vector<float>>{{
                                                                                                                           0.24f, 0.99f,
                                                                                                                           0.24f, 0.82f,
                                                                                                                           0.027f, 0.82f,
                                                                                                                           0.027f, 0.99f
                                                                                                                   }}});
    Engine::Editor().ConfigPlayerParticles("Bullet");

    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::SHOOTING, "Survivor_Shooting", {});
    Engine::Editor().GetPlayerController()->GetAnimator(GameObjects::ACTION::SHOOTING)->SetSheetAtlas({0.027, 0.f}, {0.24, 0.163}, 0.25f, 0.1665f, 1, 3);
    Engine::Editor().GetPlayerController()->GetAnimator(GameObjects::ACTION::SHOOTING)->SetSpeed(0.1);



    Engine::Editor().SetPlayerConf(p_set["health"], p_set["velocity"], p_set["ammo"], p_set["reload_time"]);
    glfwSetCursorPosCallback(window, mouse_callback);


    Engine::Editor().SetEnemies({0.16f, 0.3f}, 0.2f, e_set["enemy_numbers"]);
    Engine::Editor().ConfigEnemies(GameObjects::ACTION::WALK, "Zombie_Walk", {0.001, 0.8}, {0.20, 0.99}, 0.1999f, 0.2f, 3, 5);
    Engine::Editor().ConfigEnemies(GameObjects::ACTION::SHOOTING, "Zombie_Attack", {0.001, 0.2f}, {0.20, 0.4}, 0.1999f, 0.2f, 2, 5);
    Engine::Editor().ConfigEnemies(GameObjects::ACTION::DIE, "Zombie_Die", {0., 0.f}, {1.f, 1.f}, 0.f, 0.f, 1, 1);
    Engine::Editor().SetEnemiesSpawns({{2.0f, 2.0f}});
    Engine::Editor().SetEnemiesConf(e_set["velocity"], e_set["health"], e_set["damage"], p_set["damage"]);

    Engine::Editor().SetPauseSign({0.9f, 0.9f});
    Engine::Editor().ConfigSpritePauseSign("Pause");

    Engine::Editor().SetDeadSign({0.5f, 0.5f}, p_set["respawn_time"]);
    Engine::Editor().ConfigSpriteDeadSign("You_Dead");

    Engine::Editor().SetMap({0.f, 0.f}, {4.f, 4.f});
    Engine::Editor().ConfigSpriteMap("Map");


    Engine::Editor().SetProp({1.06049f, -0.0821197f}, {0.2, 0.25});
    Engine::Editor().SetProp({3.02035, 1.24345}, {0.2, 0.25});
    Engine::Editor().SetProp({3.5999, 1.01457}, {0.2, 0.25});
    Engine::Editor().SetProp({-1.87852, 2.21532}, {0.2, 0.25});
    Engine::Editor().SetProp({-0.0136374, 2.57205}, {0.2, 0.25});
    Engine::Editor().SetProp({-2.09623, -1.47281}, {0.2, 0.25});
    Engine::Editor().SetProp({-2.03615, -3.21101}, {0.2, 0.25});
    Engine::Editor().SetProp({0.777356, -1.24756}, {0.2, 0.25});
    Engine::Editor().SetProp({1.90111, -3.2913}, {0.2, 0.25});
    Engine::Editor().ConfigSpriteProp("Tree");

}

