#include "MyGame.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	MyGame::Singleton()->Iniciar();

	return 0;
}

