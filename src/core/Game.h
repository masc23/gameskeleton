#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>

#include "gamestates/Gamestate.h"


class Game
{
public:
    Game();
	void Run(int argc, char* argv[]);

    void SwitchGamestate(std::unique_ptr<Gamestate> newState);

private:
    bool IsRunning;
    std::unique_ptr<Gamestate> ActiveGamestate;

	const std::string GAME_NAME;
	const std::string GAME_VERSION;

	void HandleEvents();
    void Update(const float dt);
    void Draw(const float interp);

    void CreateWindow();
};

#endif
