#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace shapes::raw {
	namespace Cube {
		glm::vec3 vFrontBottomLeft(-0.5f, 0.0f, 0.5f); // front bottom left 0
		glm::vec3 vFrontTopLeft(-0.5f, 1.0f, 0.5f); // front top left 1
		glm::vec3 vFrontTopRight(0.5f, 1.0f, 0.5f); // front top right 2
		glm::vec3 vFrontBottomRight(0.5f, 0.0f, 0.5f); // front bottom right 3
		
		glm::vec3 vBackBottomLeft(-0.5f, 0.0f, -0.5f); // back bottom left 4
		glm::vec3 vBackTopLeft(-0.5f, 1.0f, -0.5f); // back top left 5
		glm::vec3 vBackTopRight(0.5f, 1.0f, -0.5f);// back top right 6
		glm::vec3 vBackBottomRight(0.5f, 0.0f, -0.5f); // back bottom right 7
		
		static std::vector<glm::vec3> vertices = {
				vFrontTopRight, vFrontTopLeft, vFrontBottomLeft,
				vFrontBottomRight, vFrontTopRight, vFrontBottomLeft,
				
				vBackBottomLeft, vBackTopLeft, vBackTopRight,
				vBackBottomLeft, vBackTopRight, vBackBottomRight,
				
				vBackTopRight, vFrontTopRight, vFrontBottomRight,
				vFrontBottomRight, vBackBottomRight, vBackTopRight,
				
				vFrontTopLeft, vBackTopLeft, vBackBottomLeft,
				vFrontBottomLeft, vFrontTopLeft, vBackBottomLeft,
				
				vBackTopRight, vBackTopLeft, vFrontTopLeft,
				vFrontTopLeft, vFrontTopRight, vBackTopRight,
				
				vBackBottomLeft, vFrontBottomRight, vFrontBottomLeft,
				vFrontBottomRight, vBackBottomLeft, vBackBottomRight,
		};
		
		static std::vector<unsigned int> indices = {
				0, 1, 2,
				3, 4, 5,
				
				6, 7, 8,
				9, 10, 11,
				
				12, 13, 14,
				15, 16, 17,
				
				18, 19, 20,
				21, 22, 23,
				
				24, 25, 26,
				27, 28, 29,
				
				30, 31, 32,
				33, 34, 35,
		};
		
		glm::vec2 uBottomLeft(0.0f, 0.0f);
		glm::vec2 uTopLeft(0.0f, 1.0f);
		glm::vec2 uBottomRight(1.0f, 0.0f);
		glm::vec2 uTopRight(1.0f, 1.0f);
		
		static std::vector<glm::vec2> uvs = {
				uBottomLeft,
				uTopLeft,
				uTopRight,
				uBottomRight,
				
				uBottomLeft,
				uTopLeft,
				uTopRight,
				uBottomRight,
		};
		
		glm::vec3 nForward(0.0f, 0.0f, 1.0f);
		glm::vec3 nBackward(0.0f, 0.0f, -1.0f);
		glm::vec3 nRight(1.0f, 0.0f, 0.0f);
		glm::vec3 nLeft(-1.0f, 0.0f, 0.0f);
		glm::vec3 nUp(0.0f, 1.0f, 0.0f);
		glm::vec3 nDown(0.0f, -1.0f, .0f);
		
		static std::vector<glm::vec3> normals = {
				glm::vec3(1.0f),
				glm::vec3(1.0f),
				
				glm::vec3(1.0f),
				glm::vec3(1.0f),
				
				glm::vec3(1.0f),
				glm::vec3(1.0f),
				
				glm::vec3(1.0f),
				glm::vec3(1.0f),
				
				glm::vec3(1.0f),
				glm::vec3(1.0f),
				
				glm::vec3(0.0f),
				glm::vec3(0.0f)
		};
	}
}