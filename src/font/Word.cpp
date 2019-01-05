#include "Word.h"

namespace font {
	Word::Word(double fontSize) : fontSize(fontSize) {
	
	}
	
	void Word::addCharacter(Character* character) {
		characters.push_back(character);
		width += character->advance * fontSize;
	}
}