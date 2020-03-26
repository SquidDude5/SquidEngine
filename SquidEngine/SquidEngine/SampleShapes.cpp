
#include "SquidEngine.h"
#include "SampleShapes.h"
#include "Primitives.h"
#include "Shape.h"

using namespace std;

Square::Square(float x, float y, float z) : Shape(x, y, z) {}

//Build the Square
void Square::build() {

	vector<Vertex> vertices = {
			Vertex(-0.5f,  0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),   // top left 
			Vertex(0.5f,  0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),  // top right
			Vertex(0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),  // bottom right
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f)  // bottom left
	};

	vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};

	createBuffer(vertices, indices);
}


Cube::Cube(float x, float y, float z) : Shape(x, y, z) {}

void Cube::build() {

	glm::vec3 frontTopLeft(-0.5f, 0.5f, 0.5f);
	glm::vec3 frontTopRight(0.5f, 0.5f, 0.5f);
	glm::vec3 frontBottomRight(0.5f, -0.5f, 0.5f);
	glm::vec3 frontBottomLeft(-0.5f, -0.5f, 0.5f);

	glm::vec3 backTopLeft(-0.5f, 0.5f, -0.5f);
	glm::vec3 backTopRight(0.5f, 0.5f, -0.5f);
	glm::vec3 backBottomRight(0.5f, -0.5f, -0.5f);
	glm::vec3 backBottomLeft(-0.5f, -0.5f, -0.5f);

	vector<Vertex> vertices = {	

		//Front
		Vertex(frontTopLeft, glm::vec3(0,0,-1), glm::vec2(0.25,0.66)), // top left 
		Vertex(frontTopRight, glm::vec3(0,0,-1), glm::vec2(0.5,0.66)),  // top right
		Vertex(frontBottomRight, glm::vec3(0,0,-1), glm::vec2(0.5,0.34)),  // bottom right
		Vertex(frontBottomLeft, glm::vec3(0,0,-1), glm::vec2(0.25,0.34)), // bottom left

		//Back
		Vertex(backTopLeft, glm::vec3(0,0,1), glm::vec2(0.75,0.66)), // top left 
		Vertex(backTopRight, glm::vec3(0,0,1), glm::vec2(1,0.66)),  // top right
		Vertex(backBottomRight, glm::vec3(0,0,1), glm::vec2(1,0.34)),  // bottom right
		Vertex(backBottomLeft, glm::vec3(0,0,1), glm::vec2(0.75,0.34)), // bottom left
		
		//Top
		Vertex(frontTopLeft, glm::vec3(0,1,0), glm::vec2(0.255,0.995)),
		Vertex(frontTopRight, glm::vec3(0,1,0), glm::vec2(0.495,0.995)),
		Vertex(backTopRight, glm::vec3(0,1,0), glm::vec2(0.495,0.675)),
		Vertex(backTopLeft, glm::vec3(0,1,0), glm::vec2(0.255,0.675)),

		//Bottom
		Vertex(frontBottomLeft, glm::vec3(0,-1,0), glm::vec2(0.255,0.05)),
		Vertex(frontBottomRight, glm::vec3(0,-1,0), glm::vec2(0.495,0.05)),
		Vertex(backBottomRight, glm::vec3(0,-1,0), glm::vec2(0.495,0.34)),
		Vertex(backBottomLeft, glm::vec3(0,-1,0), glm::vec2(0.255,0.34)),

		//Left
		Vertex(frontTopLeft, glm::vec3(1,0,0), glm::vec2(0,0.66)),
		Vertex(backTopLeft, glm::vec3(1,0,0), glm::vec2(0.25,0.66)),
		Vertex(backBottomLeft, glm::vec3(1,0,0), glm::vec2(0.25,0.34)),
		Vertex(frontBottomLeft, glm::vec3(1,0,0), glm::vec2(0,0.34)),

		//Right
		Vertex(frontTopRight, glm::vec3(-1,0,0), glm::vec2(0.5,0.66)),
		Vertex(backTopRight, glm::vec3(-1,0,0), glm::vec2(0.75,0.66)),
		Vertex(backBottomRight, glm::vec3(-1,0,0), glm::vec2(0.75,0.34)),
		Vertex(frontBottomRight, glm::vec3(-1,0,0), glm::vec2(0.5,0.34))
		
	};

	vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10, 11,

		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,

		20, 21, 23,
		21, 22, 23,
	};

	createBuffer(vertices, indices);
}


