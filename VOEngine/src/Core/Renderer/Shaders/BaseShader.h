#pragma once
class BaseShader {
	virtual void loadFromDisk() = 0;
	virtual void loadFromMemory() = 0;
	virtual void loadFromString() = 0;
	virtual unsigned int getID() = 0;
	
};