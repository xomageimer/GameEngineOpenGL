cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set (PROJECT_NAME_ GameEngine)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(${PROJECT_NAME_} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${PROJECT_NAME_} VERSION 0.0.1)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME_}

        src/main.cpp
        src/stb_image.cpp

        src/Actors/IGameActor.cpp
        src/Actors/Player.cpp
        src/Actors/Quad.cpp
        src/Actors/Enemy.cpp

        src/Graphic/Texture2D.cpp
        src/Graphic/Sprite.cpp
        src/Graphic/SpriteAnimator.cpp
        src/Graphic/VertexBuffer.cpp
        src/Graphic/VertexArray.cpp
        src/Graphic/IndexBuffer.cpp
        src/Graphic/Shader.cpp

        src/Physics/CollisionBox.cpp

        src/Engine/Engine.cpp
        src/Engine/Camera.cpp

        dependencies/glad/src/glad.c

)

add_subdirectory(contrib/glfw)
target_link_libraries(${PROJECT_NAME_} PRIVATE glfw)

add_subdirectory(contrib/glm)
target_link_libraries(${PROJECT_NAME_} PRIVATE glm)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shaders)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/res)
include_directories("glfw_repo/include")
include_directories("dependencies/glad/include")
include_directories("dependencies/image_reader")

target_link_libraries(${PROJECT_NAME_} PRIVATE ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME_} PUBLIC dependencies/image_reader)

find_package(OpenGL REQUIRED)

if (WIN32)
    target_link_libraries(${PROJECT_NAME_} PRIVATE OpenGL::GL -lopengl32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME_} PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME_} PRIVATE glfw)
else()
    message( FATAL_ERROR "could not determine the OS" )
endif()

set_target_properties(${PROJECT_NAME_} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wall;"
        )

install(TARGETS ${PROJECT_NAME_} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT xomageimer@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)