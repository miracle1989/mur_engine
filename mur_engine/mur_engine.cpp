// mur_engine.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "LightingTechnique.h"
#include "shadow_map_technique.h"
#include "ShadowMapFBO.h"
#include "SimpleTechnique.h"
#include "Model.h"
#include "Camera.h"
#include <iostream>

#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH  1024

class APP
{
public:
	APP()
	{
		m_DirLight.Name = "DL1";
		m_DirLight.Color = glm::vec3(1.0, 1.0, 1.0);
		m_DirLight.AmbientIntensity = 0.5f;
		m_DirLight.DiffuseIntensity = 0.9f;
		m_DirLight.Direction = glm::vec3(1.0, -1.0, 0.0);

		const GLubyte* c = glGetString(GL_VERSION);
		printf("OpenGL version is %s", c);
	}

	void Init()
	{
		GLenum error = glGetError();

		if (!m_LightTech.Init())
		{
			assert(0);
			printf("light tech init fail");
		}

		m_LightTech.Enable();	
		m_LightTech.SetTextureUnit(COLOR_TEXTURE_UNIT_INDEX);
		m_LightTech.SetShadowMapTextureUnit(SHADOW_TEXTURE_UNIT_INDEX);
		m_LightTech.SetDirectionalLight(1, m_DirLight);
		m_LightTech.SetSpecularIntensity(0.0);
		m_LightTech.SetSpecularPower(0);
		m_LightTech.SetPointLight(0, NULL);
		m_LightTech.SetSpotLight(0, NULL);

		if (!m_shadowTech.Init())
		{
			assert(0);
			printf("shadow tech init fail");
		}

		if (!m_ShadowFBO.Init(WINDOW_WIDTH, WINDOW_HEIGHT))
		{
			assert(0);
			printf("shadow fbo init fail");
		}

		glEnable(GL_DEPTH_TEST);

		m_Model.LoadModel("../Content/bunny.obj");

		m_Quad.LoadModel("../Content/quad.obj");

		GLCheckError();
	}
	
	~APP() {};

	void ShadowPass()
	{
		m_ShadowFBO.BindForWriting();
		
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);

		m_shadowTech.Enable();

		float l = -100.f;
		float r = 100.f;
		float b = -100.f;
		float t = 100.f;
		float n = -10.f;
		float f = 100.f;

		glm::mat4 ortho = glm::ortho(l, r, b, t, n, f);
		glm::mat4 view = glm::lookAt(glm::vec3(0), m_DirLight.Direction, glm::vec3(0.0f, 1.0f, 0.0f));

		m_shadowTech.SetMVP(ortho * view);

		m_Model.Draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderPass()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_ShadowFBO.BindForReading(SHADOW_TEXTURE_UNIT);

		glm::mat4 viewMat = m_Camera.GetViewMatrix();
		glm::mat4 projMat = glm::perspective(glm::radians(/*m_Camera.GetFovy()*/90.f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 modelMat = glm::mat4();
		modelMat = glm::translate(modelMat, glm::vec3(0.0f, -10.0f, -20.f));
		static float rot = 0;
		modelMat = glm::rotate(modelMat, glm::radians(rot), glm::vec3(0.0, 1.0, 0.0));
		rot = rot + 5;

		GLenum error = glGetError();

		m_LightTech.Enable();
		m_LightTech.SetEyeWorldPos(m_Camera.GetPos());
		m_LightTech.SetMVP(projMat * viewMat * modelMat);
		m_LightTech.SetWorldMatrix(modelMat);

		//		m_Quad.Draw();
		m_Model.Draw();
	}

	void Run()
	{
		ShadowPass();

		RenderPass();
	}

private:
	LightingTechnique   m_LightTech;
	DirectionalLight    m_DirLight;
	ShadowMapTechnique  m_shadowTech;
	ShadowMapFBO        m_ShadowFBO;
	Model               m_Model;
	Model               m_Quad;
	Camera              m_Camera;
};

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MUR_ENGINE", NULL, NULL);
	if (window == NULL)
	{
		printf( "Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, NULL);
	glfwSetCursorPosCallback(window, NULL);
	glfwSetScrollCallback(window, NULL);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	 //glad: load all OpenGL function pointers
	 //---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return -1;
	}

	APP app;

	app.Init();
	
	float deltaTime = 0;
	float lastFrame = 0;

	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GLCheckError();
		app.Run();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

