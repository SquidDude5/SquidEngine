#include "BasicLightingShader.h"
#include <iostream>

void BasicLightingShader::onInit() {
	
	newShaderPass(
		"Shaders/LightingShader/LightingShader.vert",
		"Shaders/LightingShader/LightingShader.frag");

	finishShaderPass();
}


void BasicLightingShader::onNextPass(int shaderStage, unsigned int shaderID) {
	useLighting(shaderStage);
	useCamera(shaderStage,mainCamera);
	drawShapes(shaderStage);
}



void SkyboxLightingShader::onInit() {
	

	newShaderPass(
		"Shaders/SkyboxLightingShader/SkyboxReflectionShader.vert",
		"Shaders/SkyboxLightingShader/SkyboxReflectionShader.frag");

	finishShaderPass();
	
	newShaderPass(
		"Shaders/SkyboxLightingShader/SkyboxShader.vert",
		"Shaders/SkyboxLightingShader/SkyboxShader.frag");

	finishShaderPass();
	
	newShaderPass(
		"Shaders/SkyboxLightingShader/SkyboxLightingShader.vert",
		"Shaders/SkyboxLightingShader/SkyboxLightingShader.frag");

	finishShaderPass();
	
	skyboxLightingBuffer = new ScaledFrameBuffer(1,1);
	
}



void SkyboxLightingShader::onNextPass(int shaderStage, unsigned int shaderID) {
	
	useCamera(shaderStage, mainCamera);

	
	if (shaderStage == 0) {
		
		glActiveTexture(GL_TEXTURE20); // Safe number to avoid overwriting material textures
		glBindTexture(GL_TEXTURE_CUBE_MAP, sceneSkyBox->getTextureID());
		skyboxLightingBuffer->use();
		
		drawShapes(shaderStage);
		targetBuffer->use();
	}

	if (shaderStage == 1) {
		glDepthFunc(GL_LEQUAL);
		glm::mat4 viewMatrixNoTranslation = glm::mat4(glm::mat3(mainCamera->getViewMatrix()));
		//setMat4(shaderStage, VIEW_MATRIX_UNIFORM, viewMatrixNoTranslation, -1);
		imageMatricesUBO->setData(0,sizeof(glm::mat4),&viewMatrixNoTranslation);
		setMat4(shaderStage, MODEL_MATRIX_UNIFORM, sceneSkyBox->getModelMatrix(), -1);
		sceneSkyBox->draw();
		glDepthFunc(GL_LESS);
	}



	if (shaderStage == 2) {
		glActiveTexture(GL_TEXTURE20); // Safe number to avoid overwriting material textures
		glBindTexture(GL_TEXTURE_2D, skyboxLightingBuffer->getTextureOutput());
		
		int loc = glGetUniformLocation(shaderID, getIndexedUniform("skyboxReflections", -1).c_str());
		glUniform1i(loc, 20);


		useLighting(shaderStage);
		drawShapes(shaderStage);
	}

}

void SkyboxLightingShader::destroy() {
	std::cout << "Lighting Shader destroyed" << std::endl;
	skyboxLightingBuffer->destroy();
	delete skyboxLightingBuffer;
	ShaderProgram2::destroy();
}





