#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "ray.h"
#include "objects.h"
#include "scene.h"
#include "light.h"

#include <iostream>

#include <windows.h>
#pragma comment( lib,"winmm.lib" )


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void setupCamera();
void setupScene();
void PhongRendering();
void RTRendering();
GLFWwindow* init();
void modeChoose();
void sceneChoose();

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
const float SCR_RATIO = float(SCR_WIDTH)/SCR_HEIGHT;
const int MAX_SAMPLE_RATIO = 32;
int SAMPLE_RATIO = 1;

glm::vec3 colorBuffer[SCR_HEIGHT][SCR_WIDTH];

// camera
Camera *camera = nullptr;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// use configuration
int modeChoosed;
int sceneChoosed;
bool RTaccelerate;

// scene
Scene *scene;

int main(int argc, char *argv[]) {
    if(argc > 1) {
        for(int i=1; i<argc; i++) {
            if(!strcmp(argv[i], "-s")) {
                i++;
                int sample_ratio = std::stoi(argv[i]);
                if(sample_ratio > MAX_SAMPLE_RATIO || sample_ratio < 1) {
                    printf("Invalid sample option! Try 1~%d.\n", MAX_SAMPLE_RATIO);
                    exit(-1);
                }
                SAMPLE_RATIO = sample_ratio;
            }
            else {
                printf("Invalid option!\n");
                exit(-1);
            }
        }
    }

    printf("Welcome!\n");
    modeChoose();
    sceneChoose();

    setupCamera();
    setupScene();

    //scene->printVerticesInfo();

    if(modeChoosed == 1) {
        PhongRendering();
    }
    else {
        RTRendering();
    }

    scene->destroyScene();
    
    return 0;
}


void modeChoose() {
    char c;
    while(true) {
        printf("Choose rendering mode:\n\t[1] Phong\n\t[2] Ray tracing\n\t[3] Ray tracing with acceleration\n\t[0] Quit\nYou choice: ");
        c = getchar();
        getchar();
        system("cls");
        if(c == '1') {
            modeChoosed = 1;
        }
        else if(c == '2') {
            modeChoosed = 2;
            RTaccelerate = false;
        }
        else if(c == '3') {
            modeChoosed = 2;
            RTaccelerate = true;
        }
        else if(c == '0') {
            exit(0);
        }
        else {
            printf("Wrong choise! Please choise again.\n");
            continue;
        }
        break;
    }
}

void sceneChoose() {
    char c;
    while(true) {
        if(modeChoosed == 2 || modeChoosed == 3) {
            printf("Choose scene:\n\t[1] Simple\n\t[2] Complicated\n\t[3] Sphere\n\t[0] Quit\nYou choice: ");
        }
        else {
            printf("Choose scene:\n\t[1] Simple\n\t[2] Complicated\n\t[0] Quit\nYou choice: ");
        }
        c = getchar();
        getchar();
        system("cls");
        if(c == '1') {
            sceneChoosed = 1;
        }
        else if(c == '2') {
            sceneChoosed = 2;
        }
        else if(c == '3' && (modeChoosed == 2 || modeChoosed == 3)) {
            sceneChoosed = 3;
        }
        else if(c == '0') {
            exit(0);
        }
        else {
            printf("Wrong choise! Please choise again.\n");
            continue;
        }
        break;
    }
}

GLFWwindow* init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Scene", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(modeChoosed == 1) {
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    return window;
}

void setupCamera() {
    if(modeChoosed == 1) {
        camera = new Camera(glm::vec3(-4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, -30.0f);
        camera->Zoom = 90.0f;
    }
    else {
        camera = new Camera(glm::vec3(-4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, -30.0f);
    }

    if(sceneChoosed == 3) {
        camera->Position = glm::vec3(-4.0f, 2.0f, 5.0f);
        camera->Pitch = -10.0f;
    }
}

void setupScene() {
    scene = new Scene(5, RTaccelerate);
    /*--------------------------- Objects in scene ---------------------------*/
    if(sceneChoosed == 1) {
        Cube *object0 = new Cube(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(2.0f, 2.0f, 2.0f));
        object0->setMaterial(Material::getSilverMaterial());
        scene->addObject(object0);
        Cube *object1 = new Cube(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(2.0f, 2.0f, 2.0f));
        object1->setMaterial(Material::getByzantiumMaterial());
        scene->addObject(object1);
        Plane *object2 = new Plane(BOTTOM_FACE, glm::vec3(0.0f, -1.5, 0.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(20.0f, 20.0f, 20.0f));
        object2->setMaterial(Material::getPlaneGridMaterial());
        scene->addObject(object2);
    }
    else if(sceneChoosed == 2) {
        Bunny *object0 = new Bunny(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        object0->setMaterial(Material::getSilverMaterial());
        scene->addObject(object0);
        Dragon *object1 = new Dragon(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        object1->setMaterial(Material::getBronzeMaterial());
        scene->addObject(object1);
        Happy *object2 = new Happy(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        object2->setMaterial(Material::getGoldMaterial());
        scene->addObject(object2);
        Plane *object3 = new Plane(BOTTOM_FACE, glm::vec3(0.0f, -1.5, 0.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(20.0f, 20.0f, 20.0f));
        object3->setMaterial(Material::getPlaneGridMaterial());
        scene->addObject(object3);
    }
    else {
        Sphere *object0 = new Sphere(1.5f, glm::vec3(-3.0f, 0.0f, 0.0f));
        object0->setMaterial(Material::getGlassMaterial());
        scene->addObject(object0);
        Sphere *object1 = new Sphere(1.5f, glm::vec3(2.0f, 0.0f, 0.0f));
        object1->setMaterial(Material::getMirrorMaterial());
        scene->addObject(object1);
        Sphere *object2 = new Sphere(0.5f, glm::vec3(-0.5f, -1.0f, 3.5f));
        object2->setMaterial(Material::getByzantiumMaterial());
        scene->addObject(object2);
        Sphere *object3 = new Sphere(0.5f, glm::vec3(3.5f, -1.0f, 2.0f));
        object3->setMaterial(Material::getSilverMaterial());
        scene->addObject(object3);
        Sphere *object4 = new Sphere(0.5f, glm::vec3(-4.0f, -1.0f, 2.5f));
        object4->setMaterial(Material::getGoldMaterial());
        scene->addObject(object4);
        Sphere *object5 = new Sphere(0.5f, glm::vec3(1.5f, -1.0f, -5.0f));
        object5->setMaterial(Material::getBronzeMaterial());
        scene->addObject(object5);
        Sphere *object6 = new Sphere(0.5f, glm::vec3(-6.0f, -1.0f, -3.0f));
        object6->setMaterial(Material::getCeruleanMaterial());
        scene->addObject(object6);
        Plane *object7 = new Plane(BOTTOM_FACE, glm::vec3(0.0f, -1.5, 0.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(20.0f, 20.0f, 20.0f));
        object7->setMaterial(Material::getPlaneGridMaterial());
        scene->addObject(object7);
    }

    /*--------------------------- Lights in scene ----------------------------*/
    DirectLight *light0 = new DirectLight(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.06f, 0.06f, 0.06f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, -1.0f, 0.0f));
    scene->addLight(light0);
    PointLight *light1 = new PointLight(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-5.0f, 5.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    scene->addLight(light1);
    /*------------------------------------------------------------------------*/
}

void PhongRendering() {
    GLFWwindow *window = init();
    if(!window) {
        glfwTerminate();
        exit(-1);
    }

    scene->loadVertices();

    Shader lightingShader("vshader.vs", "fshader.fs");
    lightingShader.use();

    for(Light *light: scene->lights) {
        // override light attributes in shader
        DirectLight *directLight = dynamic_cast<DirectLight*>(light);
        if(directLight) {
            lightingShader.setVec3("dirLight.ambient", directLight->ambient);
            lightingShader.setVec3("dirLight.diffuse", directLight->diffuse);
            lightingShader.setVec3("dirLight.specular", directLight->specular);
            continue;
        }
        PointLight *pointLight = dynamic_cast<PointLight*>(light);
        if(pointLight) {
            lightingShader.setVec3("pointLight.position", pointLight->position);
            lightingShader.setVec3("pointLight.ambient", pointLight->ambient);
            lightingShader.setVec3("pointLight.diffuse", pointLight->diffuse);
            lightingShader.setVec3("pointLight.specular", pointLight->specular);
            lightingShader.setFloat("pointLight.constant", pointLight->constant);
            lightingShader.setFloat("pointLight.linear", pointLight->linear);
            lightingShader.setFloat("pointLight.quadratic", pointLight->quadratic);
            continue;
        }
    }

    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
        lightingShader.setVec3("viewPos", camera->Position);
        
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        for(Object *object: scene->objects) {
            glm::mat4 model = object->getModelMatrix(float(glfwGetTime()));
            lightingShader.setMat4("model", model);

            const Material *mat = object->getMaterial();
            glm::vec3 dummyPos(0.0f, 0.0f, 0.0f);
            lightingShader.setVec3("material.ambient", mat->ambient(dummyPos));
            lightingShader.setVec3("material.diffuse", mat->diffuse(dummyPos));
            lightingShader.setVec3("material.specular", mat->specular(dummyPos)); // specular lighting doesn't have full effect on this object's material
            lightingShader.setFloat("material.shininess", mat->shininess(dummyPos));
            
            lightingShader.setBool("gridMaterial", false);

            // draw ground
            Plane *plane = dynamic_cast<Plane*>(object);
            if(plane) {
                lightingShader.setBool("gridMaterial", true);
                plane->vertices->Draw(lightingShader);
                lightingShader.setBool("gridMaterial", false);
                continue;
            }

            ModelObject *modelObject = dynamic_cast<ModelObject*>(object);
            if(modelObject) {
                modelObject->model->Draw(lightingShader);
                continue;
            }
            VerticesObject *verticesObject = dynamic_cast<VerticesObject*>(object);
            if(verticesObject) {
                verticesObject->vertices->Draw(lightingShader);
                continue;
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void RTRendering() {
    int height = SAMPLE_RATIO*SCR_HEIGHT;
    int width = SAMPLE_RATIO*SCR_WIDTH;

    printf("Start rendering with resolution %dx%d\n", width, height);

    float start = timeGetTime();

    // calculate pixels' color
#pragma omp parallel for schedule(dynamic)
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            glm::vec3 scrPos = glm::vec3(float(j)*2/width-1.0f, float(i)*2/height-1.0f, 0.0f);
            glm::vec3 globalPos = camera->Position + camera->Front + scrPos.x*camera->Right*SCR_RATIO + scrPos.y*camera->Up;
            Ray ray(camera->Position, globalPos-camera->Position);
            glm::vec3 color = scene->rayTrace(ray);
            colorBuffer[i/SAMPLE_RATIO][j/SAMPLE_RATIO] += color;
        }
    }

    float end = timeGetTime();
    printf("Time consumption: %.3fs\n", (end-start)*1.0/1000);

    GLFWwindow *window = init();
    if(!window) {
        glfwTerminate();
        exit(-1);
    }

    // draw with data in buffer
    float vertices[] ={0.0f, 0.0f, 0.0f};
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader shaderRT("vshaderRT.vs", "fshaderRT.fs");
    shaderRT.use();
    glBindVertexArray(VAO);

    // draw pixel with shader
    for(int i=0; i<SCR_HEIGHT; i++) {
        for(int j=0; j<SCR_WIDTH; j++) {
            colorBuffer[i][j] /= (SAMPLE_RATIO*SAMPLE_RATIO);
            glm::vec3 scrPos = glm::vec3(float(j)*2/SCR_WIDTH-1.0f, float(i)*2/SCR_HEIGHT-1.0f, 0.0f);
            shaderRT.setVec2("screenPos", scrPos.x, scrPos.y);
            shaderRT.setVec3("vertexColor", colorBuffer[i][j]);
            glDrawArrays(GL_POINTS, 0, 1);
        }
    }

    glfwSwapBuffers(window);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(modeChoosed != 1) return;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->ProcessKeyboard(FORWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->ProcessKeyboard(LEFT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->ProcessKeyboard(RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera->ProcessKeyboard(UP, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera->ProcessKeyboard(DOWN, deltaTime);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera->ProcessMouseScroll(yoffset);
}