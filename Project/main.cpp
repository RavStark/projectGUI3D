#define GLEW_STATIC
#include "GL\glew.h"

#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Shader.hpp"
#include "Engine/Renderer/TextureManager.hpp"
#include "Engine/Camera/CameraFps.hpp"
#include "Engine/Renderer/Objects/PlaneRenderer.hpp"
#include "Engine/Renderer/Objects/CubeRenderer.hpp"
#include "Engine/Renderer/LightsManager.hpp"
#include "Engine/Renderer/Lights/PointLight.hpp"
#include <iostream>
#include <memory>
#include <Windows.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1020
GLFWwindow *window;
bool _wireFrame = false;


GLfloat deltaTime =0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX = SCREEN_WIDTH / 2.f;
GLfloat lastY = SCREEN_HEIGHT / 2.f;
float xOffset = 0.0f;
float yOffset = 0.0f;

//Keys event presseds/released
bool keys[1024];
std::shared_ptr<CameraFps> camera = nullptr;

float specular = 0.0f;
float ambient = 0.0f;
float diffuse = 0.0f;
bool firstMouse = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{




	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		_wireFrame = !_wireFrame;
		if (_wireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		camera->processKeyboard(Camera::FORWARD, deltaTime);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		camera->processKeyboard(Camera::BACKWARD, deltaTime);
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		camera->processKeyboard(Camera::LEFT, deltaTime);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		camera->processKeyboard(Camera::RIGHT, deltaTime);
	}
	
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
		return;
	}
	xOffset = xpos - lastX;
	yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera->updateDirection(xOffset, yOffset, 0);
}

int initializeOpenGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Creating window
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	return 0;
}

void do_mouvement(std::shared_ptr<CameraFps> &cam)
{
	if (cam == nullptr)
		return;
	GLfloat cameraSpeed = 5.f * deltaTime;
	if (keys[GLFW_KEY_W])
		cam->setPos(camera->getPos() + cameraSpeed * cam->getFront());
	if (keys[GLFW_KEY_S])
	{
		cam->setPos(camera->getPos() - cameraSpeed * cam->getFront());
	}
	if (keys[GLFW_KEY_A])
		cam->setPos(camera->getPos() - cameraSpeed * glm::normalize(glm::cross(cam->getFront(), cam->getUp())));
	if (keys[GLFW_KEY_D])
		cam->setPos(camera->getPos() + cameraSpeed * glm::normalize(glm::cross(cam->getFront(), cam->getUp())));
	if (keys[GLFW_KEY_8])
	{
		specular += 0.1f;
		std::cout << "specular: " << specular << std::endl;
	}
	if (keys[GLFW_KEY_7])
	{
		if (specular > 0)
			specular -= 0.1f;
	}
	if (keys[GLFW_KEY_0])
	{
		ambient += 0.1f;
		std::cout << "ambient: " <<ambient << std::endl;
	}
	if (keys[GLFW_KEY_9])
	{
		if (ambient > 0)
			ambient -= 0.1f;
	}
	if (keys[GLFW_KEY_6])
	{
		diffuse += 0.1f;
		std::cout << "diffuse: " << specular << std::endl;
	}
	if (keys[GLFW_KEY_5])
	{
		if (diffuse > 0)
			diffuse -= 0.1f;
	}
	float ambient = 0.0f;
	float diffuse = 0.0f;
}

int main(int ac, char *av[])
{
	
	if (initializeOpenGL() == -1)
		return -1;


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	
/*	GLuint indexes[] = {
		0,1,2, //first triangle
		3,4,5 //second triangle
	};*/

	GLfloat texCoords[] = {
		0.0f, 0.0f,  // Lower-left corner  
		1.0f, 0.0f,  // Lower-right corner
		0.5f, 1.0f   // Top-center corner
	};
	
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	
	//Camera
	camera = std::make_shared<CameraFps>(glm::vec3(0.0f, 0.0f, 3.0f), screenWidth, screenHeight);

	/* Texture */
	std::shared_ptr<TextureManager> textureManager = std::make_shared<TextureManager>();


	textureManager->loadNewTexture2D("container", "./Project/Ressources/Textures/container2.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_NEAREST);
	textureManager->loadNewTexture2D("container2_specular", "./Project/Ressources/Textures/container2_specular.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	//textureManager->loadNewTexture2D("matrix", "./Ressources/Textures/matrix.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

	Renderer renderer(camera, textureManager);

	/* LIGHT */
	for (auto lightPos : pointLightPositions)
	{
		auto pointLight = std::make_shared<PointLight>(lightPos);
		renderer.addLight(pointLight);
	}


	
	renderer.addObject(glm::vec3(0.0f, 0.0f, 0.0f));
	
	glEnable(GL_DEPTH_TEST);
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightDir(-0.2f, -1.0f, -0.2);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	glm::vec3 planePos = glm::vec3(0.f, -2.f, -3.f);
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		
		double start = glfwGetTime();
		glfwPollEvents();
		do_mouvement(camera);
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer.draw();
		//cubeRenderer->draw(textureManager, camera);
		/*** PLANE SHADER **/
		/*planeShader.use();
		//glm::mat4 modelPlane;
		glm::mat4 inverseModelView;
		planeShader.setVec3("viewPos", camera->getPos());

		planeShader.setInt("material.diffuse", 0);
		planeShader.setInt("material.specular", 1);
		planeShader.setFloat("material.shininess", 32.f);

		planeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		//lightingShader.setVec3("lightPos", lightPos);

		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*//*
		// directional light
		planeShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		planeShader.setVec3("dirLight.ambient", ambient);
		planeShader.setVec3("dirLight.diffuse", diffuse);
		planeShader.setVec3("dirLight.specular", specular);
		// point light 1
		planeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		planeShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		planeShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		planeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		planeShader.setFloat("pointLights[0].constant", 1.0f);
		planeShader.setFloat("pointLights[0].linear", 0.09f);
		planeShader.setFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		planeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		planeShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		planeShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		planeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		planeShader.setFloat("pointLights[1].constant", 1.0f);
		planeShader.setFloat("pointLights[1].linear", 0.09f);
		planeShader.setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		planeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		planeShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		planeShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		planeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		planeShader.setFloat("pointLights[2].constant", 1.0f);
		planeShader.setFloat("pointLights[2].linear", 0.09);
		planeShader.setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		planeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		planeShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		planeShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		planeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		planeShader.setFloat("pointLights[3].constant", 1.0f);
		planeShader.setFloat("pointLights[3].linear", 0.09f);
		planeShader.setFloat("pointLights[3].quadratic", 0.032f);
		// spotLight
		planeShader.setVec3("spotLight.position", camera->getPos());
		planeShader.setVec3("spotLight.direction", camera->getFront());
		planeShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		planeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		planeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		planeShader.setFloat("spotLight.constant", 1.0f);
		planeShader.setFloat("spotLight.linear", 0.09f);
		planeShader.setFloat("spotLight.quadratic", 0.032f);
		planeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		planeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		
		*/
		//planeRenderer.draw(view, projection, planePos, glm::vec3(1.f, 1.f, 1.f), 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		/*
		lightShader.use();
		
		//glm::mat4 model;
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f));
		//glUniform3f(glGetUniformLocation(lightShader.getProgram(), "our_color"), lightColor.x, lightColor.y, lightColor.z);
		
		//glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		//glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			//model = glm::mat4();
			//model = glm::translate(model, pointLightPositions[i]);
			//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			//glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//cuLightRenderer[i]->draw(view, projection, pointLightPositions[i], glm::vec3(0.2f),0.0f , lightColor);
		}*/
		//glBindVertexArray(0);
		glfwSwapBuffers(window);
		double stop = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Sleep(1000 / 60 - (stop - start));
	}
	glfwTerminate();

	return 0;
}