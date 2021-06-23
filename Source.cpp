#include "LevelEditor.h"
#include "Game.h"

int main() {
	int userChoice = 0;

	cout << "Welcome to Development Suite v0.2a" << endl;
	cout << "1. Run Level Editor" << endl;
	cout << "2. Run Game" << endl;
	cout << "User: "; cin >> userChoice;

	if (userChoice == 1) {
		LevelEditor l("gameWorld");
	}
	if (userChoice == 2) {
		Game g("gameWorld");
	}

	return 0;
}