#pragma once

namespace font {
	class Character {
	public:
		unsigned int id;
		double xCoord;
		double yCoord;
		double xMaxCoord;
		double yMaxCoord;
		double xOffset;
		double yOffset;
		double sizeX;
		double sizeY;
		double advance;
	
		Character(unsigned int id, double xCoord, double yCoord, double xSizeCoord, double ySizeCoord,
		          double xOffset, double yOffset, double sizeX, double sizeY, double advance);
	};
}