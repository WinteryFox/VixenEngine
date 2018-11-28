#include <utility>

#include "Phong.h"

namespace graphics::shaders::phong {
	Phong::Phong(std::string vertexFilePath, std::string fragmentFilePath) : Shader(std::move(vertexFilePath),
	                                                                                std::move(fragmentFilePath)) {
		
	}
}