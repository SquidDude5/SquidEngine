
#include "App.h"
#include "SquidEngine.h"
#include "Cube.h"
#include "CameraFPS.h"
#include "BasicLightingShader.h"
#include <iostream>
#include "Model.h"
#include "Light.h"
#include "UniformBuffer.h"

Cube* testCube;
Model* building;
Model* bauble;
Material* testMat;
SkyboxLightingShader* lightingShader;
SkyBox* skybox;
DirectionalLight dirLight(-1.0f,-0.25f,0.0f);
CameraFPS cam(0, 0, 3, 0, 0, -1);
Model* cottage;


glm::mat4 lightRotator(1.0f);
glm::vec3 lightDir1(0, 0, 0);
glm::vec3 lightDir2(0, 0, 0);

void Game::onInit() {
	cam.setRenderDistance(0.01f,500.0f);

	testCube = new Cube(0,0,0);
	building = new Model(-5,0,5,"Resources/Models/Buildings/Residential Buildings 001.obj");
	//bauble = new Model(0, 5, 0,"Resources/Models/BigModels/Bauble/Christmastree_Ball.obj");
	cottage = new Model(5, 0, 5, "Resources/Models/Cottage/cottage.obj");
	cottage->setScale(0.01f, 0.01f, 0.01f);

	std::vector<std::string> skyboxImages = {
		"Resources/Textures/skybox/right.jpg",
		"Resources/Textures/skybox/left.jpg",
		"Resources/Textures/skybox/top.jpg",
		"Resources/Textures/skybox/bottom.jpg",
		"Resources/Textures/skybox/front.jpg",
		"Resources/Textures/skybox/back.jpg"
	};

	skybox = new SkyBox(skyboxImages);

	testMat = new Material(
		"Resources/Textures/star.png", 
		"Resources/Textures/starSpecular.bmp", 
		64);

	testCube->setMaterial(*testMat);

	lightingShader = new SkyboxLightingShader();
	lightingShader->onInit();
	

	lightingShader->setMainCamera(cam);

	lightingShader->addShape(*testCube);
	lightingShader->addModel(*building);
	lightingShader->addModel(*cottage);
	//lightingShader->addModel(*bauble);

	lightingShader->addDirectionalLight(dirLight);
	lightingShader->setSkybox(*skybox);

	ViewPort views[] = { 
		ViewPort(0,0,0.5f,1.0f),
		ViewPort(0.5f,0,0.5f,1.0f)
	};

	//setViewPorts(views,2);
	lightRotator = glm::rotate(lightRotator, 0.01f, glm::vec3(0, 0, 1));
	lightDir1 = dirLight.direction;
	lightDir2 = -dirLight.direction;
}


void Game::onDraw(double deltaTime, int viewID, ViewPort& view) {
	cam.updateFPS(60);
	cam.setView(view);

	if (viewID == 0) {
		lightDir1 = glm::vec4(lightDir1, 1) * lightRotator;
		dirLight.direction = lightDir1;
	}
	else {
		lightDir2 = glm::vec4(lightDir2, 1) * lightRotator;
		dirLight.direction = lightDir2;
	}

}


void Game::onInputCheck(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_W) == true) { cam.moveForward(); }
	if (glfwGetKey(window, GLFW_KEY_S) == true) { cam.moveBackward(); }
	if (glfwGetKey(window, GLFW_KEY_A) == true) { cam.moveLeft(); }
	if (glfwGetKey(window, GLFW_KEY_D) == true) { cam.moveRight(); }
	if (glfwGetKey(window, GLFW_KEY_C) == true) { cam.moveDown(); }
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == true) { cam.moveDown(); }
	if (glfwGetKey(window, GLFW_KEY_SPACE) == true) { cam.moveUp(); }
}


void Game::onMouseMove(int mouseX, int mouseY) {
	cam.updateCursorPos(mouseX, mouseY, isWindowFocused());
}


void Game::onMouseScroll(double scrollX, double scrollY) {
	cam.setMoveSpeed(cam.getMoveSpeed() + (scrollY*0.5f));
}


void Game::onWindowResize(int width, int height) {  }


void Game::onClose() {
	testCube->destroy();
	testMat->destroy();
	lightingShader->destroy();
	delete testCube;
	delete testMat;
	delete lightingShader;
}





int main() {
	Game gameInstance;
	createEngineWindow(800, 600, "SquidEngine");



	runEngine(gameInstance);

	return 0;
}