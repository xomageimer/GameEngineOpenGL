#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

                                            /*! \defgroup _Metaprogramming_Macroprogramming creating static polymorphism for pure C functions
                                             *   @{ \details Использование макросов и метафункций для создания статического полиморфизма для чисто Сишных функций
                                             *   из библиотеки glfw
                                            */

#define UNIFORMTAG(ph_1, ph_2) glUniform ## ph_1 ## ph_2    ///< Макрос для вызова glUniform функции glfw на основе ее постфиксов

                                                            /*!
                                                             * Макрос для генерации всех возможных функций с данными постфиксами для простых C типов
                                                             */
#define CallFuncs(type, separate) CallIfCallable(UNIFORMTAG(1, type), glGetUniformLocation(ID, val_name.c_str()), std::forward<Params>(params)...) separate \
    CallIfCallable(UNIFORMTAG(2, type), glGetUniformLocation(ID, val_name.c_str()), std::forward<Params>(params)...) separate \
    CallIfCallable(UNIFORMTAG(3, type), glGetUniformLocation(ID, val_name.c_str()), std::forward<Params>(params)...) separate  \
    CallIfCallable(UNIFORMTAG(4, type), glGetUniformLocation(ID, val_name.c_str()), std::forward<Params>(params)...)
                                                            /*!
                                                             * Макрос для генерации всех возможных функций с данными постфиксами для матриц
                                                             */
#define CallFuncsForMatrix(type, separate) CallIfCallable(UNIFORMTAG(type, 2fv), glGetUniformLocation(ID, val_name.c_str()), 1, GL_FALSE, glm::value_ptr(std::forward<Params>(params)...)) separate \
    CallIfCallable(UNIFORMTAG(type, 3fv), glGetUniformLocation(ID, val_name.c_str()), 1, GL_FALSE, glm::value_ptr(std::forward<Params>(params)...)) separate  \
    CallIfCallable(UNIFORMTAG(type, 4fv), glGetUniformLocation(ID, val_name.c_str()), 1, GL_FALSE, glm::value_ptr(std::forward<Params>(params)...))

                                                             /*!
                                                              * Метафункция для перебора и попытки вызова с соотвествующими аргументами сишных функций
                                                              * @tparam F тип указателя функции
                                                              * @tparam S типы аргументов функции
                                                              * @param func функция
                                                              * @param args аргументы
                                                              * @return void
                                                              */
template <typename F, typename... S>
constexpr void CallIfCallable(F&& func, S&& ...args){
    if constexpr (std::is_invocable_v<F, decltype(std::forward<S>(args))...>){
        std::invoke(std::forward<F>(func), std::forward<S>(args)...);
    } else {
        return;
    }
};
                                        /*! @} */
struct Shader {
public:
                                        /*!
                                         * Конструктор Шейдера
                                         * @param vertex_shader - путь к вершинному шейдеру
                                         * @param fragment_shader - путь к фрагментому шейдеру
                                         * Код шейдера выглядет следующим образом:
                                         * Вершинный:
                                         * @code
                                                #version 330
                                                layout (location = 0) in vec3 aPos;
                                                layout (location = 1) in vec2 aTexture;

                                                out vec2 nextTexture;

                                                uniform mat4 view;
                                                uniform mat4 transform;
                                                uniform mat4 projection;

                                                uniform float layer = 0.f;

                                                void main() {
                                                    gl_Position = projection *  view * transform * vec4(aPos.x, aPos.y, layer, 1.0f);
                                                    nextTexture = aTexture;
                                                }
                                         * @endcode
                                         * Фрагментный шейдер:
                                         * @code
                                                #version 330

                                                in vec2 nextTexture;
                                                out vec4 FragColor;

                                                uniform sampler2D texture_;

                                                void main() {
                                                    FragColor = texture(texture_, vec2(nextTexture.x, nextTexture.y));
                                                }
                                         * @endcode
                                         */
    Shader(const std::filesystem::path & vertex_shader, const std::filesystem::path & fragment_shader);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&&) noexcept;
    Shader& operator=(Shader&&) noexcept;
                                    /*!
                                     * Использовать шейдерную программу инкапсулированную в этот класс для всего текущего состояния OpenGL
                                     */
    void use();
                                    /*!
                                     * Полиморфизм С функции и вызов подстановки Uniform - устанавливает значение для uniform-переменной только для активной в данный момент шейдерной программы
                                     */
    template <typename ... Params>
    void glUniform(const std::string &val_name, Params... params){
        if constexpr (std::is_same_v<Params..., float>) {
            CallFuncs(f, ;);
        }
        else if constexpr (std::is_same_v<Params..., int>) {
            CallFuncs(i, ;);
        }
        else if constexpr (std::is_same_v<Params..., glm::mat4>){
            CallFuncsForMatrix(Matrix, ;);
        }
    }
                                /*!
                                 * Проверка успешности компиляции шейдера
                                 * @return успешно ли?
                                 */
    bool Check(unsigned int &);

    [[nodiscard]] unsigned int GetId() const {
        return ID;
    }
private:
    unsigned int ID;
};


#endif //GAMEENGINE_SHADER_H
