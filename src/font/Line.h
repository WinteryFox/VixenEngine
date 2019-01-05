#pragma once

#include "Word.h"

namespace font {
	class Line {
	public:
		double maxLength;
		double spaceSize;
		
		std::vector<Word*> words;
		double currentLineLength = 0;
		
		Line(double spaceWidth, double fontSize, double maxLength);
		
		bool addWord(Word* word);
	};
}