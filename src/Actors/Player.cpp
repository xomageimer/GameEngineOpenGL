#include "Player.h"

void GameObjects::Player::SetAction(GameObjects::ACTION act) {
    m_action = act;
}

void GameObjects::Player::Render() {
    auto it = m_representative[m_action];
    UpdateSprite(it->GetSprite());
    it->AnimationUpdate();
    for (auto & i : bullets){
        i.first = !i.second->die();
        if (i.first)
            i.second->Render();
    }
}

GameObjects::Player::Player(glm::vec2 position, glm::vec2 size, float rotation, float layer) : IGameActor(position,
                                                                                                          size,
                                                                                                          rotation,
                                                                                                          layer) {
    health = std::make_shared<float>(100.f);
}

bool GameObjects::Player::die() {
    return *health < 0.f;
}

void GameObjects::Player::UpdateSprite(std::shared_ptr<Graphic::Sprite> sprite) {
    sprite->GetCenter() = m_position;
    sprite->GetSize() = m_size;
    sprite->GetRotation() = m_rotation;
    sprite->GetLayer() = m_layer;
}

void GameObjects::Player::SetAnimator(ACTION name_of_action, std::shared_ptr<Graphic::SpriteAnimator> anim) {
    auto it = this->m_representative.emplace(name_of_action, anim);
    float vertices[] = {
            1.f, 1.f, 0.f,
            1.f, -1.f, 0.f,
            -1.f, -1.f, 0.f,
            -1.f, 1.f, 0.f
    };
    const int indices[] {
            0, 1, 3,
            1, 2, 3
    };
    it.first->second->GetSprite()->Init(vertices, sizeof(vertices), GL_DYNAMIC_DRAW, indices, sizeof(indices), GL_DYNAMIC_DRAW);
}

void GameObjects::Player::SetAnimation(GameObjects::ACTION act) {
    m_action = act;
}

void GameObjects::Player::mouse_controller(GLFWwindow *window, double xpos, double ypos) {
    if (die())
        return;

    glm::vec3 pos_2D{ xpos, ypos, 0.0f };

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 projection = glm::frustum(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 100.f);

    glm::vec3 proje_vect = glm::unProject(pos_2D, model, projection, glm::vec4(0.0f, 0.0f, 800.0f, 600.0f));

    proje_vect = glm::normalize(proje_vect);

    m_rotation = atan2f(proje_vect.y, proje_vect.x);

    m_direction = proje_vect;
}

void GameObjects::Player::keyboard_controller(GLFWwindow *window, float & deltaTime, float & lastFrame) {
    if (die())
        return;

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    const float CameraSpeed = m_velocity * deltaTime;

    auto prev_pos = m_position;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_action = ACTION::WALK;
        m_position += (m_direction * CameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_action = ACTION::WALK;
        m_position -= (m_direction * CameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_action = ACTION::WALK;
        glm::vec2 right = glm::cross(glm::vec3(m_direction, 0.f), m_up);
        m_position -= (right * CameraSpeed * 0.7f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_action = ACTION::WALK;
        glm::vec2 right = glm::cross(glm::vec3(m_direction, 0.f), m_up);
        m_position += (right * CameraSpeed * 0.7f);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (bullet_num != ammo) {
            if (currentFrame - lastBullet >= 0.3f) {
                bullets[bullet_num].first = true;
                bullets[bullet_num++].second->Activate();
                lastBullet = glfwGetTime();
            }
            m_action = ACTION::SHOOTING;
        } else {
            is_reload = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS
        && glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_R) != GLFW_PRESS) {
        m_action = ACTION::IDLE;
    }
    if (is_reload || glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (reload_start >= reload_timer) {
            bullet_num = 0;
            reload_start = 0.f;
            is_reload = false;
        }
        reload_start += CameraSpeed;
        m_action = ACTION::RELOAD;
    }

    if (m_position.x >= 3.9f || m_position.y >= 3.9f || m_position.x <= -3.9f || m_position.y <= -3.9f)
        m_position = prev_pos;

  //  std::cerr << "my position: " << m_position.x << ' ' << m_position.y << std::endl;
}

void GameObjects::Player::SetBullet(std::vector<std::shared_ptr<Graphic::Sprite>> vec) {
    bullets.reserve(vec.size());
    for (auto i : vec) {
        bullets.emplace_back(false, std::make_shared<Bullet>(m_position, glm::vec2{0.02f, 0.02f}, m_rotation, m_direction));
        bullets.back().second->SetSprite(std::make_shared<Graphic::SpriteAnimator>(i, std::vector<std::vector<float>>{{1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}}));
    }
}

std::shared_ptr<float> GameObjects::Player::getHealth() {
    return std::shared_ptr<float>(this->health);
}

std::vector<std::pair<bool, std::shared_ptr<GameObjects::Bullet>>> & GameObjects::Player::getBullets() {
    return bullets;
}

void GameObjects::Player::SetAmmo(size_t num) {
    assert(num > 0);
    ammo = num;
}

void GameObjects::Player::SetReloadTime(double time) {
    assert(time > 0);
    reload_timer = time;
}

