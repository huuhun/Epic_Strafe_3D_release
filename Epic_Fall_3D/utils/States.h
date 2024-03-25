#pragma once

enum class PlayState
{
	PLAYING = 0,
	MENU = 1,
	GAME_OVER = 2,
};

enum class RenderFlag
{
	RenderCube = 0,
	RenderBoundary = 1,
	RenderEnterText = 2,
	RenderGameOverText = 3,
	RenderSpinCube = 4,
};