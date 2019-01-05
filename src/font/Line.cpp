#include "Line.h"

namespace font {
	Line::Line(double spaceWidth, double fontSize, double maxLength) : spaceSize(spaceWidth * fontSize), maxLength(maxLength) {
	
	}
	
	bool Line::addWord(Word* word) {
		double additionalLength = word->width;
		additionalLength += !words.empty() ? spaceSize : 0;
		if (currentLineLength + additionalLength <= maxLength) {
			words.push_back(word);
			currentLineLength += additionalLength;
			return true;
		}
		return false;
	}
}