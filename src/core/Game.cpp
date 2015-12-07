#include "Game.h"

#include <iostream>

#include "Timer.h"
#include "gamestates/Gamestate.h"
#include "gamestates/EmptyGamestate.h"

Game::Game()
    : IsRunning(true), GAME_NAME("GAME_NAME"), GAME_VERSION("0.0.0.1")
{
	ActiveGamestate = std::unique_ptr<Gamestate>(new EmptyGamestate());
}

void Game::Run(int argc, char* argv[])
{
    const float LOGIC_STEP     = 1.0f / 60.0f;
    const float MAX_FRAME_TIME = 1.0f / 10.0f;
    
    float frameTime   = 0.0;
    float accumulator = 0.0;

	Timer timer;

    while (IsRunning)
    {
		HandleEvents();

        frameTime = timer.Elapsed();
        
        if (frameTime > MAX_FRAME_TIME)
        {
            frameTime = MAX_FRAME_TIME;
        }

        accumulator += frameTime;

        while (accumulator >= LOGIC_STEP)
        {
            Update(LOGIC_STEP);
            accumulator -= LOGIC_STEP;
        }

        Draw(accumulator / LOGIC_STEP);
    }
}

void Game::SwitchGamestate(std::unique_ptr<Gamestate> newState)
{
    ActiveGamestate = std::move(newState);
}

void Game::HandleEvents()
{
	// ToDo: Add InputHandler that pumps the MessageBus
	ActiveGamestate->HandleEvents();
}

void Game::Update(const float dt)
{
    ActiveGamestate->UpdateLogic(dt);

    if (ActiveGamestate->IsFinished())
    {
		if (ActiveGamestate->IsShutdown())
		{
			IsRunning = false;
		}
		else
		{
			SwitchGamestate(ActiveGamestate->GetNextGamestate());
		}
    }
}

void Game::Draw(const float interp)
{
    ActiveGamestate->Draw(interp);
}
