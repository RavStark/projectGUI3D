#define GLEW_STATIC
#include "GL\glew.h"

#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "TextureManager.hpp"
#include "Camera/CameraFps.hpp"
#include "Objects/ManageObjects.h"
#include "Objects/PrimitivePlane.hpp"
#include "Objects/PlaneGLProperties.hpp"
#include <iostream>
#include <Windows.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1020
GLFWwindow *window;
bool _wireFrame = false;
Shader *_lightingShader;

GLfloat deltaTime =0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX = SCREEN_WIDTH / 2.f;
GLfloat lastY = SCREEN_HEIGHT / 2.f;
float xOffset = 0.0f;
float yOffset = 0.0f;

//Keys event presseds/released
bool keys[1024];
CameraFps *camera;

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


void do_mouvement()
{
	GLfloat cameraSpeed = 5.f * deltaTime;
	if (keys[GLFW_KEY_W])
		camera->setPos(camera->getPos() + cameraSpeed * camera->getFront());
	if (keys[GLFW_KEY_S])
	{
		camera->setPos(camera->getPos() - cameraSpeed * camera->getFront());
	}
	if (keys[GLFW_KEY_A])
		camera->setPos(camera->getPos() - cameraSpeed * glm::normalize(glm::cross(camera->getFront(), camera->getUp())));
	if (keys[GLFW_KEY_D])
		camera->setPos(camera->getPos() + cameraSpeed * glm::normalize(glm::cross(camera->getFront(), camera->getUp())));
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
	//vertices for triangles
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords   //Normal
		//front
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // Top Left
		0.5f,-0.5f, -0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Bottom Right
		-0.5f,-0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Bottom Left

		-0.5f,  0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f, // Top Left
		0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  0.0f, 0.0f, -1.0f, // Top Right
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,  0.0f, 0.0f, -1.0f, // Bottom Right

		//back
		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		//left
		-0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		//right
		0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,-0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		//face down
		-0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		//face up
		-0.5f, 0.5f,-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f,-0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	};

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
//	glfwSetCursorPosCallback(window, mouse_callback);
	//shaders
	_lightingShader = new Shader("./Shaders/MultipleLighting.vs", "./Shaders/MultipleLighting.frag");
	Shader lightShader("./Shaders/Light.vs", "./Shaders/Color.frag");
	Shader planeShader("./Shaders/MultipleLighting.vs", "./Shaders/MultipleLightingWithoutText.frag");
	//Camera
	camera = new CameraFps(glm::vec3(0.0f, 0.0f, 3.0f), screenWidth, screenHeight);
	
	Texture::TextureManager *textureManager = new Texture::TextureManager();

	textureManager->loadNewTexture2D("container", "./Ressources/Textures/container2.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_NEAREST);
	textureManager->loadNewTexture2D("container2_specular", "./Ressources/Textures/container2_specular.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	//textureManager->loadNewTexture2D("matrix", "./Ressources/Textures/matrix.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	GLuint VBO, VAO;
	//GLuint EBO;
	GLuint texture;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Nomal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	/* LIGHT */
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
	

	/* PLANE */

	//ManageObjects<PrimitivePlane, PlaneGLProperties> _planesObjectManager;
	PlaneGLProperties pGLp;
	pGLp.initObjectGLProperties();
	PrimitivePlane plane;
	/*
	GLuint planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlane), verticesPlane, GL_STATIC_DRAW);

	glBindVertexArray(planeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Nomal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);*/


	glEnable(GL_DEPTH_TEST);
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightDir(-0.2f, -1.0f, -0.2);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	plane.setTranslate(glm::vec3(0.f, -2.f, -3.f));
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		
		double start = glfwGetTime();
		glfwPollEvents();
		do_mouvement();
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		_lightingShader->use();
		
		//lightColor.x = sin(glfwGetTime() * 2.f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		//lightPos.x = 2.0f + sin(glfwGetTime()) * 2.f;
		//lightPos.y = (sin(glfwGetTime()) /2.f) * 2.f;
		//lightPos.z = (sin(glfwGetTime()) / 2.f) * 2.f;
		
	
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture("awesomeface"));
		glUniform1i(glGetUniformLocation(_lightingShader->getProgram(), "ourTexture2"), 1);
		*/

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence

		_lightingShader->setVec3("viewPos", camera->getPos());
		/*_lightingShader->setVec3("light.ambient", ambientColor);
		_lightingShader->setVec3("light.diffuse", diffuseColor);
		_lightingShader->setVec3("light.specular", 1.0f);
		_lightingShader->setVec3("light.direction", lightDir);

		_lightingShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		//_lightingShader->setInt("material.diffuse", 1.0f, 0.5f, 0.31f);*/
		_lightingShader->setInt("material.diffuse", 0);
		_lightingShader->setInt("material.specular", 1);
		_lightingShader->setFloat("material.shininess", 32.f);

		_lightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		//_lightingShader->setVec3("lightPos", lightPos);
		
		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		_lightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		_lightingShader->setVec3("dirLight.ambient", ambient);
		_lightingShader->setVec3("dirLight.diffuse", diffuse);
		_lightingShader->setVec3("dirLight.specular", specular);
		// point light 1
		_lightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
		_lightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		_lightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		_lightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		_lightingShader->setFloat("pointLights[0].constant", 1.0f);
		_lightingShader->setFloat("pointLights[0].linear", 0.09f);
		_lightingShader->setFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		_lightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
		_lightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		_lightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		_lightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		_lightingShader->setFloat("pointLights[1].constant", 1.0f);
		_lightingShader->setFloat("pointLights[1].linear", 0.09f);
		_lightingShader->setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		_lightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
		_lightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		_lightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		_lightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		_lightingShader->setFloat("pointLights[2].constant", 1.0f);
		_lightingShader->setFloat("pointLights[2].linear", 0.09);
		_lightingShader->setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		_lightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
		_lightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		_lightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		_lightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		_lightingShader->setFloat("pointLights[3].constant", 1.0f);
		_lightingShader->setFloat("pointLights[3].linear", 0.09f);
		_lightingShader->setFloat("pointLights[3].quadratic", 0.032f);
		// spotLight
		_lightingShader->setVec3("spotLight.position", camera->getPos());
		_lightingShader->setVec3("spotLight.direction", camera->getFront());
		_lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		_lightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		_lightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		_lightingShader->setFloat("spotLight.constant", 1.0f);
		_lightingShader->setFloat("spotLight.linear", 0.09f);
		_lightingShader->setFloat("spotLight.quadratic", 0.032f);
		_lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		_lightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


		glm::mat4 view;
		view = camera->viewMatrix();//glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
									//Projection matrix will clip object that are outside the screen
		glm::mat4 projection = camera->projectionMatrix();//glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		//Model Matrix transform local space to World Coordinate space
		glUniformMatrix4fv(glGetUniformLocation(_lightingShader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(_lightingShader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture("container"));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture("container2_specular"));
		glBindVertexArray(VAO);
		for (unsigned i = 0; i != 10; i++)
		{
			glm::mat4 model, inverseModelView;
			model = glm::translate(model, cubePositions[i]);
			inverseModelView = glm::inverse(model * view) ;
			//model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(50.f), glm::vec3(0.5f, 1.0f, 0.0f));
			//model = glm::rotate(model, glm::radians(-10.f), glm::vec3(1.0f, 0.0f, 0.0f));

			//View Matrix should transform World Coordinate space to view Coordinate
			//trans = glm::rotate(trans, (GLfloat)glfwGetTime() * glm::radians(70.f), glm::vec3(1.0f, 0.f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(_lightingShader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(_lightingShader->getProgram(), "inverseModelView"), 1, GL_FALSE, glm::value_ptr(inverseModelView));
			

			//glBindTexture(GL_TEXTURE_2D, textureManager->getTexture("matrix"));
			//glActiveTexture(GL_TEXTURE2);
			
			//glUniform1i(glGetUniformLocation(_lightingShader->getProgram(), "material.diffuse"), 0);
		//	glUniform1i(glGetUniformLocation(_lightingShader->getProgram(), "material.specular"), 1);
			//glUniform1i(glGetUniformLocation(_lightingShader->getProgram(), "material.emission"), 1);
			
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		/*** PLANE SHADER **/
		planeShader.use();
		//glm::mat4 modelPlane;
		glm::mat4 inverseModelView;
		planeShader.setVec3("viewPos", camera->getPos());
		planeShader.setInt("material.diffuse", 0);
		planeShader.setInt("material.specular", 1);
		planeShader.setFloat("material.shininess", 32.f);

		planeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		//_lightingShader->setVec3("lightPos", lightPos);

		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
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
		inverseModelView = glm::inverse(view * plane.getModel());
		
		//inverseModelView = glm::inverse(view * modelPlane);
		planeShader.setMat4("model", plane.getModel());
		planeShader.setMat4("inverseModelView", inverseModelView);
		planeShader.setMat4("view", view);
		planeShader.setMat4("projection", projection);
		planeShader.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
		glBindVertexArray(pGLp.getVAO());

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		lightShader.use();
		
		glm::mat4 model;
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniform3f(glGetUniformLocation(lightShader.getProgram(), "our_color"), lightColor.x, lightColor.y, lightColor.z);
		
		glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		double stop = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Sleep(1000 / 60 - (stop - start));
	}
	glfwTerminate();
	delete _lightingShader;
	delete textureManager;
	delete camera;
	return 0;
}