#ifndef MAINWINDOW_CLASS_H
#define MAINWINDOW_CLASS_H

#include"core/window.h"
#include"player.h"
#include"level_def.h"
#include"core/vao.h"
#include"assets/sprite.h"

class MainWindow : public Window{
public:
    MainWindow(int w, int h, int x, int y, const char* title);
    void update();
    void openWindow();
    void load();
    void draw();
    void newLevel();
private:
    void resize(GLFWwindow*, int, int);
    Camera cam;
    LevelManager levelManager;
    glm::vec2 fadeMesh[4] = {
        glm::vec2(-1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(-1.0f, -1.0f)
    };
    unsigned short fadeInds[6] = {
        0,3,2,
        2,1,0
    };
    long long lastPressed = 0;
    bool paused = false;
    bool levelComplete = false;
    float fade = 0.0f;
    VAO fadeVAO;
    Shader_* fadeShader_ = new Shader(shaders::fadeShader,uniforms(&fade),staticUniforms());

    float resumeHover;
    glm::mat4 resumeTransform = glm::mat4(1.0f);
    Sprite resumeButton;

    float restartHover;
    glm::mat4 restartTransform = glm::mat4(1.0f);
    Sprite restartButton;

    float exitHover;
    glm::mat4 exitTransform = glm::mat4(1.0f);
    Sprite exitButton;

    float failedColor = 1.0f;
    glm::mat4 failedTransform = glm::mat4(1.0f);
    Sprite failedText;
    
    float continueColor;
    glm::mat4 continueTransform = glm::mat4(1.0f);
    Sprite continueButton;

    float playColor;
    glm::mat4 playTransform = glm::mat4(1.0f);
    Sprite3D playButton;

    glm::mat4 exit3DTransform = glm::mat4(1.0f);
    Sprite3D exitButton3D;

    float mainscreenColor = 1.0f;
    glm::mat4 mainTransform = glm::mat4(1.0f);
    Sprite mainSprite;
    glm::mat4 pencilTransform = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(-16.0f,0.05f,-20.0f)), glm::vec3(8.0f, 8.0f, 8.0f)), glm::radians(30.0f), UP_VECTOR);
    glm::mat4 staplerTransform = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(6.0f,4.0f,-22.0f)), glm::vec3(4.0f, 4.0f, 4.0f)), glm::radians(-60.0f), UP_VECTOR);
    glm::mat4 tableTransform = glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(-7.5f,0.0f,-11.0f)), glm::vec3(2.0f, 2.0f, 2.0f)), glm::radians(90.0f), UP_VECTOR);
    Shader_* tableShader = new Shader(shaders::textured, uniforms(&cam.matrix, &tableTransform, assets.getTexture("table.png")),staticUniforms());
    Model table = Model(&models::table);
    Object pencil = Object(new Shader(shaders::textured, uniforms(&cam.matrix, &pencilTransform, assets.getTexture("pencil.png")),staticUniforms()), Model(&models::pencil));
    Object stapler = Object(new Shader(shaders::textured, uniforms(&cam.matrix, &staplerTransform, assets.getTexture("stapler.png")),staticUniforms()), Model(&models::stapler));

    Model mainModel = Model(&models::l1);
	Shader_* mainShader = new Shader(shaders::textured, uniforms(&cam.matrix,&tableTransform,assets.getTexture("main.png")), staticUniforms());


    int levelNum = 0;

    bool loading = false;
    bool mainscreen = true;
};

#endif