#include "GameManager.h"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(0));
	GameManager gameManager;
	gameManager.mainLoop();
	return 0;
}