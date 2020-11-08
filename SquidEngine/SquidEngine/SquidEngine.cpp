

#include "SquidEngine.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "SampleShapes.h"
#include "Camera.h"
#include "CameraFPS.h"
#include "Texture.h"
#include "Voxel.h"

using namespace std;

CameraFPS cam(0, 0, 3, 0, 0, -1);

void mainResizeEvent(GLFWwindow* window, int width, int height)
{
	cout << "Resized to :" << width << ", " << height << endl;
}



void cursorCallBack(GLFWwindow* window, double xpos, double ypos) {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
		cam.updateCursorPos(xpos, ypos, true);
	}
	else {
		cam.updateCursorPos(xpos, ypos, false);
	}
	
}

void scrollCallBack(GLFWwindow* window, double scrollX, double scrollY) {

	if (cam.moveSpeed + scrollY < 0) {
		cam.moveSpeed = 0;
	}
	else {
		cam.moveSpeed += scrollY;
	}
	
}

void mouseBtnCallBack(GLFWwindow* window, int button, int action, int mods) {
	if (glfwGetWindowAttrib(window, GLFW_HOVERED)) {
		if (button == GLFW_MOUSE_BUTTON_1) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}

void processCameraInput(Window& window, CameraFPS& cam) //Cant get current context with wrapper
{
	if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetInputMode(window.form, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
		cam.moveForward();
	}

	if (window.getKey(GLFW_KEY_S) == GLFW_PRESS) {
		cam.moveBackward();
	}

	if (window.getKey(GLFW_KEY_A) == GLFW_PRESS) {
		cam.moveLeft();
	}

	if (window.getKey(GLFW_KEY_D) == GLFW_PRESS) {
		cam.moveRight();
	}

	if (window.getKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
		cam.moveUp();
	}

	if (window.getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cam.moveDown();
	}
}



int main()
{
	cout << "Hello World" << endl;

	Window mainWindow(800, 600, "SquidEngine");

	mainWindow.show();
	glfwSetFramebufferSizeCallback(mainWindow.form, mainResizeEvent);
	glfwSetCursorPosCallback(mainWindow.form, cursorCallBack);
	glfwSetMouseButtonCallback(mainWindow.form, mouseBtnCallBack);
	glfwSetScrollCallback(mainWindow.form, scrollCallBack);
	mainWindow.setActive();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	ViewPort viewMain(0.0f, 0.0f, 1.0f, 1.0f);
	ViewPort view1(0.0f, 0.5f,0.5f, 0.5f);
	ViewPort view2(0.5f, 0.5f, 0.5f, 0.5f);
	ViewPort view3(0.0f, 0.0f, 0.5f, 0.5f);
	ViewPort view4(0.5f, 0.0f, 0.5f, 0.5f);

	vector<ViewPort> viewsMain = { viewMain };
	vector<ViewPort> views = { view1, view2, view3, view4 };

	ShaderProgram basicShader("Shaders/BasicShader/BasicShader.vert", "Shaders/BasicShader/BasicShader.frag");
	ShaderProgram lightingShader("Shaders/LightingShader/LightingShader.vert", "Shaders/LightingShader/LightingShader.frag");

	ShaderProgram shader = lightingShader;
	shader.createShaderProgram();
	shader.use();

	Texture moon("Resources/Textures/moon.jpg");
	Texture star("Resources/Textures/star.png");
	Texture cubeMap("Resources/Textures/floor.bmp");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	MaterialList Materials;

	/*
	Voxel voxelArea(0,0,0);
	voxelArea.setMaterial(Materials.obsidian);
	voxelArea.setSeed(427942);
	voxelArea.setSurfaceLevel(0.4f);
	voxelArea.setFrequency(1.0f);
	voxelArea.setOctaves(8.0f);
	voxelArea.outputNoise("debugImages/voxel.png",256,256);
	voxelArea.populatePoints(100, 50, 100);
	voxelArea.setScale(20.0f, 10.0f, 20.0f);
	voxelArea.build();
	*/

	glm::mat4 worldMatrix(1.0f);
	shader.setMat4(WORLD_MATRIX_UNIFORM, worldMatrix);

	SpotLight spotLight(cam.eyePos.x, cam.eyePos.y, cam.eyePos.z-1, cam.lookVec.x, cam.lookVec.y, cam.lookVec.z);
	//spotLight.innerCutOff = glm::cos(glm::radians(12.5f));
	//spotLight.outerCutOff = glm::cos(glm::radians(15.5f));
	unsigned int spotLightHandle = shader.addSpotLight(spotLight);

	PointLight pointLight(0, 1.5f, 0);
	shader.addPointLight(pointLight);

	PointLight pointLight2(-1.5f, 1.5f, 0);
	shader.addPointLight(pointLight2);

	DirectionalLight dirLight(-0.5f, -0.5f, -0.5f);
	shader.addDirectionalLight(dirLight);

	Cube testCube(0.0f, 0.0f, 0.0f);
	testCube.setMaterial(Materials.emerald);
	testCube.addTexture(star.getID());
	testCube.build();

	double frameStart = glfwGetTime();
	while (!mainWindow.closing())
	{

		processCameraInput(mainWindow,cam);

		vector<ViewPort> viewList = viewsMain;

		for (int i = 0; i < viewList.size(); ++i) {
			viewList[i].use();
			cam.setView(viewList[i]);

			glClearColor(0.43f, 0.71f, 0.86 - ((0.86f / views.size()) * (i)), 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//voxelArea.draw(shader);
			testCube.draw(shader);
		}

		cam.use(shader);

		glfwSwapInterval(1);
		glfwSwapBuffers(glfwGetCurrentContext());
		glfwPollEvents();

		cam.updateFPS(1 / (glfwGetTime() - frameStart));
		frameStart = glfwGetTime();
	}	

	return 0;
}

