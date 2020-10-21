#include "Engine/Engine.h"

#include "Graphic/Buffers.h"
// TODO попробовать собрать плеера и санимировать его!

extern float deltaTime;
extern float lastFrame;


void PlayerTest (){
    using namespace Graphic;
    using namespace GameObjects;
    using namespace std;


    auto Shaders_Path = (std::filesystem::current_path()).parent_path()/"shaders";
    auto Resource_Path = (std::filesystem::current_path()).parent_path()/"res";

    float vertices[] = {
            0.13f, 0.2f, 0.0f,
            0.13f, -0.2f, 0.0f,
            -0.13f,  -0.2f, 0.0f,
            -0.13f, 0.2f, 0.0f
    };
    float text[] = {
            0.2f, 1.f,
            0.2f, 0.80f,
            0.f, 0.80f,
            0.f, 1.f
    };
    int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    static auto shader = Shader(Shaders_Path/"vertex_shader.glsl", Shaders_Path/"fragment_shader.glsl");
    static auto texture = Texture2D((Resource_Path/"chars/survivor_sec.png"));

    auto player = Player(glm::vec2(0.f, 0.f),{0.13f, 0.2f}, 90.f, 0.f);

    static auto sprite = Sprite(std::shared_ptr<Texture2D>(&texture), std::shared_ptr<Shader>(&shader));

    vector<vector<float>> vec { {text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7]}};

    sprite.Init(vertices, sizeof(vertices), GL_DYNAMIC_DRAW, indices, sizeof(indices), GL_DYNAMIC_DRAW);

    player.SetAnimator(ACTION::WALK, std::make_shared<SpriteAnimator>(SpriteAnimator(std::shared_ptr<Sprite>(&sprite), vec)));

}

void SpriteAnimatorTest(){
    using namespace Graphic;
    using namespace std;


    auto Shaders_Path = (std::filesystem::current_path()).parent_path()/"shaders";
    auto Resource_Path = (std::filesystem::current_path()).parent_path()/"res";

    float vertices[] = {
            0.13f, 0.2f, 0.0f,
            0.13f, -0.2f, 0.0f,
            -0.13f,  -0.2f, 0.0f,
            -0.13f, 0.2f, 0.0f
    };
    float text[] = {
            0.2f, 1.f,
            0.2f, 0.80f,
            0.f, 0.80f,
            0.f, 1.f
    };
    int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    static auto shader = Shader(Shaders_Path/"vertex_shader.glsl", Shaders_Path/"fragment_shader.glsl");
    static auto texture = Texture2D((Resource_Path/"chars/survivor_sec.png"));

    static auto sprite = Sprite(std::shared_ptr<Texture2D>(&texture), std::shared_ptr<Shader>(&shader));

    vector<vector<float>> vec { {text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7]}};

    auto sa = SpriteAnimator(std::shared_ptr<Sprite>(&sprite), vec);

    sa.GetSprite()->Init(vertices, sizeof(vertices), GL_DYNAMIC_DRAW, indices, sizeof(indices), GL_DYNAMIC_DRAW);


}

void SpriteTest(){
    using namespace Graphic;
    using namespace std;


    auto Shaders_Path = (std::filesystem::current_path()).parent_path()/"shaders";
    auto Resource_Path = (std::filesystem::current_path()).parent_path()/"res";

    float vertices[] = {
            0.13f, 0.2f, 0.0f,
            0.13f, -0.2f, 0.0f,
            -0.13f,  -0.2f, 0.0f,
            -0.13f, 0.2f, 0.0f
    };

    int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    static auto shader = Shader(Shaders_Path/"vertex_shader.glsl", Shaders_Path/"fragment_shader.glsl");
    static auto texture = Texture2D((Resource_Path/"chars/survivor_sec.png"));

    static auto sprite = Sprite(std::shared_ptr<Texture2D>(&texture), std::shared_ptr<Shader>(&shader));

    sprite.Init(vertices, sizeof(vertices), GL_DYNAMIC_DRAW, indices, sizeof(indices), GL_DYNAMIC_DRAW);

    shader.use();
    shader.glUniform("texture_", 0);
    texture.bind();
    shader.glUniform("transform", glm::mat4(1.f));
}


void BuffersTest(){
    using namespace Graphic;
    using namespace std;


    auto Shaders_Path = (std::filesystem::current_path()).parent_path()/"shaders";
    auto Resource_Path = (std::filesystem::current_path()).parent_path()/"res";

    float vertices[] = {
            0.13f, 0.2f, 0.0f,
            0.13f, -0.2f, 0.0f,
            -0.13f,  -0.2f, 0.0f,
            -0.13f, 0.2f, 0.0f
    };
    float text[] = {
            0.2f, 1.f,
            0.2f, 0.80f,
            0.f, 0.80f,
            0.f, 1.f
    };
    int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    static auto shader = Shader(Shaders_Path/"vertex_shader.glsl", Shaders_Path/"fragment_shader.glsl");
    static auto texture = Texture2D((Resource_Path/"chars/survivor_sec.png"));
    static auto vao = VertexArray(); // < вроде норм
    vao.bind();
    static auto vbo = VertexBuffer(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
    static auto ibo = IndexBuffer(indices, sizeof(indices), GL_DYNAMIC_DRAW);
    vao.SetVertexAttrib();
    static auto tbo = VertexBuffer(text, sizeof(text), GL_DYNAMIC_DRAW);
    vao.SetVertexAttrib(1, 2);
    shader.use();
    shader.glUniform("texture_", 0);
    texture.bind();
    vao.EnableAllAttrib();
    shader.glUniform("transform", glm::mat4(1.f));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    Engine::Editor().GetPlayerController()->mouse_controller(window, xpos, ypos);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    Engine::Editor().GetPlayerController()->keyboard_controller(window, deltaTime, lastFrame);
}

void AnimeTest(GLFWwindow* window){
    Engine::Editor().SetPlayer({0.f, 0.f}, {0.13f, 0.2f}, 0.f, 0.f);
    auto Resource_Path = (std::filesystem::current_path()).parent_path()/"res";
    auto Shaders_Path = (std::filesystem::current_path()).parent_path()/"shaders";

    Engine::Editor().SetShader(Shaders_Path/"vertex_shader.glsl", Shaders_Path/"fragment_shader.glsl");
    Engine::Editor().SetTexture("Survivor_Texture", (Resource_Path/"chars/survivor_sec.png"));

    Engine::Editor().SetSprite("Survivor_Walk", "Survivor_Texture");
    Engine::Editor().SetSprite("Survivor_Idle", "Survivor_Texture");
    Engine::Editor().SetSprite("Survivor_Shooting", "Survivor_Texture");

    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::WALK, "Survivor_Walk", {});
    Engine::Editor().GetPlayerController()->GetAnimator(GameObjects::ACTION::WALK)->SetSheetAtlas({0.027, 0.82}, {0.24, 0.99}, 0.25f, 0.1665f, 5, 4);
    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::IDLE, "Survivor_Idle", {std::vector<std::vector<float>>{{
                                                                                                                           0.24f, 0.99f,
                                                                                                                           0.24f, 0.82f,
                                                                                                                           0.027f, 0.82f,
                                                                                                                           0.027f, 0.99f
                                                                                                                   }}});

    Engine::Editor().ConfigPlayerAnim(GameObjects::ACTION::SHOOTING, "Survivor_Shooting", {});
    Engine::Editor().GetPlayerController()->GetAnimator(GameObjects::ACTION::SHOOTING)->SetSheetAtlas({0.027, 0.0}, {0.24, 0.154}, 0.25f, 0.1665f, 1, 3);

    Engine::Editor().GetPlayerController()->setVelocity(0.2f);


    glfwSetCursorPosCallback(window, mouse_callback);
}

