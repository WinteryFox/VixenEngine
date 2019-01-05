#include "Character.h"

namespace font {
	Character::Character(unsigned int id, double xCoord, double yCoord, double xSizeCoord, double ySizeCoord,
	          double xOffset, double yOffset, double sizeX, double sizeY, double advance) : id(id), xCoord(xCoord),
	                                                                                        yCoord(yCoord),
	                                                                                        xMaxCoord(xMaxCoord),
	                                                                                        yMaxCoord(yMaxCoord),
	                                                                                        xOffset(xOffset),
	                                                                                        yOffset(yOffset),
	                                                                                        sizeX(sizeX),
	                                                                                        sizeY(sizeY),
	                                                                                        advance(advance) {
	}
}