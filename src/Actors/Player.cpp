#include "Player.h"

void GameObjects::Player::SetAction(GameObjects::ACTION act) {
    m_action = act;
}

void GameObjects::Player::Render() {
    auto it = m_representative[m_action];
    UpdateSprite(it->GetSprite());
    it->AnimationUpdate();
}

GameObjects::Player::Player(glm::vec2 position, glm::vec2 size, float rotation, float layer) : IGameActor(position,
                                                                                                          size,
                                                                                                          rotation,
                                                                                                          layer) {
}

void GameObjects::Player::die() {
    std::cerr << "NO IMPL" << std::endl;
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
    glm::vec3 pos_2D{ xpos, ypos, 0.0f };

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 projection = glm::frustum(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 100.f);

    glm::vec3 proje_vect = glm::unProject(pos_2D, model, projection, glm::vec4(0.0f, 0.0f, 800.0f, 600.0f));

    m_rotation = atan2f(proje_vect.y, proje_vect.x); // -3.14, что бы соответствовать направлению {0, 1}

    m_direction = glm::normalize(proje_vect);
}

void GameObjects::Player::keyboard_controller(GLFWwindow *window, float & deltaTime, float & lastFrame) {

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    const float CameraSpeed = m_velocity * deltaTime;

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
    if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS
        && glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) {
        m_action = ACTION::IDLE;
    }

}
