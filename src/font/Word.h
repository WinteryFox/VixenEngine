#pragma once

#include <vector>
#include "Character.h"

namespace font {
	class Word {
	public:
		std::vector<Character*> characters;
		double width = 0;
		
	private:
		double fontSize;
		
	public:
		explicit Word(double fontSize);
		
		void addCharacter(Character* character);
	};
}