
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp> 
#include<glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<string>
#include<vector>
#include"class/Shader.h"
#include"class/Model.h"
#include"class/Camera.h"
#include"class/VertexBuffer.h"
#include"class/Texture2.h"
#include"class/CubeTexture.h"
using namespace std;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


float fov = 45.0f;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float lastX = 320.0f;
float lastY = 240.0f;

int esc_counts = 0;
bool esc_status = false;
bool firstmouse = true;

Camera camera1(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);



    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwWindowHint(GLFW_REFRESH_RATE, 30);
    glfwSetScrollCallback(window, scroll_callback);
    glewInit();
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    float grassattribute[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
    };
    float attribute[] = {
        // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    float screen[]{
         -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    unsigned int lightvao;
    glGenVertexArrays(1, &lightvao);
    glBindVertexArray(lightvao);
    VertexBuffer vbo(attribute, 288 * sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int grassvao;
    glGenVertexArrays(1, &grassvao);
    glBindVertexArray(grassvao);
    VertexBuffer grassvbo(grassattribute, 48 * sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int screenvao;
    glGenVertexArrays(1, &screenvao);
    glBindVertexArray(screenvao);
    VertexBuffer screenvbo(screen, 24 * sizeof(float));
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    unsigned int cubevao;
    glGenVertexArrays(1, &cubevao);
    glBindVertexArray(cubevao);
    VertexBuffer cubevbo(skyboxVertices, 108 * sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    Model rmodel("model/robot/nanosuit.obj");
    Texture2 grasstexture(GL_TEXTURE4, "texture/grass.png", PNG);
    Texture2 windowtexture(GL_TEXTURE5, "texture/blending_transparent_window.png", PNG);
    //load cube Texture
    vector<string> faces{
    "cube/right.jpg",
    "cube/left.jpg",
    "cube/bottom.jpg",
    "cube/top.jpg",
    "cube/front.jpg",
    "cube/back.jpg"     
    };
    CubeTexture sky(GL_TEXTURE6, faces, JPG);
    Shader shader("shader/vertex.shader", "shader/fragment.shader");
    Shader lightshader("shader/vertex.shader", "shader/lightfragment.shader");
    Shader outlingshader("shader/vertex.shader", "shader/outliningfragment.shader");
    Shader grassshader("shader/vertex.shader", "shader/grass_f.shader");
    Shader screenshader("shader/screen_v.shader", "shader/screen.shader");
    Shader cubeshader("shader/skycube_v.shader", "shader/skycube_f.shader");
    //framebuffer
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    //create texture
 
    unsigned int texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //bind texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
    glActiveTexture(GL_TEXTURE0);
    //bind rbo
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    //bind depth and stencil to rbo
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // -----------------------------
    
    
    /* Loop until the user closes the window */
    

    while (!glfwWindowShouldClose(window))
    {
       
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        /* Render here */
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
      
       

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.3f, 0.1f, 100.0f);
        glm::mat4 view = camera1.GetView();
        //sky cube shader
        glDisable(GL_DEPTH_TEST);
        cubeshader.Use();
        glBindVertexArray(cubevao);
        cubeshader.setInt("skybox",6);
        cubeshader.setMat4("view", view);
        cubeshader.setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glEnable(GL_DEPTH_TEST);

        //light model transformation
        glm::vec3 light_position(0.0f, 1.5f, 0.0f);
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f * sin((float)glfwGetTime()), 0.0f, 0.5f * cos((float)glfwGetTime())));
        light_position = glm::vec3(trans * glm::vec4(light_position, 1.0f));
        glm::mat4 light_model(1.0f);
        light_model = glm::translate(light_model, light_position);
        light_model = glm::scale(light_model, glm::vec3(0.02f));
        

        //obejcet model transformations
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.1f));	// it's a bit too big for our scene, so scale it down
      
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        //object shader
        shader.Use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);
        // render the loaded model
        shader.setInt("skybox", 6);
        shader.setVec3("u_camerapos", camera1.GetPos());
        //u_point
        shader.setVec3("u_pointlight.color", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setVec3("u_pointlight.position", light_position);
        shader.setFloat("u_pointlight.p", 64);
        shader.setFloat("u_pointlight.constant", 1.0f);
        shader.setFloat("u_pointlight.linear", 0.22f);
        shader.setFloat("u_pointlight.quadratic", 0.20f);
        //u_spot
        shader.setVec3("u_spotlight.color", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setVec3("u_spotlight.position", camera1.GetPos());
        shader.setVec3("u_spotlight.direction", camera1.GetDir());
        shader.setFloat("u_spotlight.cutoff", glm::cos(glm::radians(12.5f)));
        shader.setFloat("u_spotlight.outer_cutoff", glm::cos(glm::radians(17.5f)));
        shader.setFloat("u_spotlight.p", 64);
        shader.setFloat("u_spotlight.constant", 1.0f);
        shader.setFloat("u_spotlight.linear", 0.0f);
        shader.setFloat("u_spotlight.quadratic", 0.0f);
        rmodel.Draw(shader);
        glStencilMask(0x00);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        
        //outlining shader
        outlingshader.Use();
        outlingshader.setMat4("projection", projection);
        outlingshader.setMat4("view", view);
        model = glm::scale(model, glm::vec3(1.02f,1.005f,1.03f));
        shader.setMat4("model", model);
        rmodel.Draw(outlingshader);

        glStencilMask(0xFF);
    
        glDisable(GL_STENCIL_TEST);


        //light shader
        glBindVertexArray(lightvao);
        lightshader.Use();
        lightshader.setMat4("model", light_model);
        lightshader.setMat4("view", view);
        lightshader.setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glm::mat4 grass_model = glm::mat4(1.0f);
        //window draw
        glBindVertexArray(grassvao);
        grassshader.Use();
        grass_model = glm::mat4(1.0f);
        grass_model = glm::scale(grass_model, glm::vec3(0.5f));
        grass_model = glm::translate(grass_model, glm::vec3(0.0f, 3.0f, 2.0f));
        grassshader.setMat4("model", grass_model);
        grassshader.setMat4("projection", projection);
        grassshader.setMat4("view", view);
        grassshader.setInt("grass_texture", 5);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //grass draw
        glBindVertexArray(grassvao);
        grassshader.Use();
        grass_model = glm::mat4(1.0f);
        grass_model = glm::translate(grass_model, glm::vec3(0.0f, 0.0f, 1.0f));
        grassshader.setMat4("model", grass_model);
        grassshader.setMat4("projection", projection);
        grassshader.setMat4("view", view);
        grassshader.setInt("grass_texture",4 );
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisable(GL_DEPTH_TEST);


        //framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(screenvao);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        screenshader.Use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}





// camera controll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 60.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 60.0f)
        fov = 60.0f;
}


void processInput(GLFWwindow* window)
{

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_W);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_S);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_A);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_D);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_SPACE);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera1.Set_Keyborad_MOVE(deltaTime, GLFW_KEY_LEFT_CONTROL);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        if (!esc_counts) {
            if (esc_status) {
                esc_status = false;

                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else {
                esc_status = true;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            esc_counts = 1;
        }


    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
        esc_counts = 0;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    //intialize

    float sensitivity = 0.05f;
    float xoffset = sensitivity * (xpos - lastX);
    float yoffset = sensitivity * (lastY - ypos);
    lastX = xpos;
    lastY = ypos;
    camera1.Set_Mouse_MOVE(xoffset, yoffset);


}