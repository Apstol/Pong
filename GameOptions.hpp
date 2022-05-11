#pragma once

namespace GameOptions
{
	enum NumPlayers
	{
		OnePlayer,
		TwoPlayers,

		PlayersOptionsCount
	};

	enum Speed
	{
		Slow,
		Medium,
		Fast,

		SpeedCount
	};

	enum GameOver
	{
		PlayAgain,
		Exit,

		GameOverCount
	};
}
