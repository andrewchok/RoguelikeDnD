#pragma once
#ifndef INFOSCREEN
#define INFOSCREEN

#include <iostream>
#include <string>
#include <conio.h>
#include "KeyStrokes.h"
#include "PlayerCharacter.h"

class InfoScreen
{
public:
	InfoScreen() {};
	~InfoScreen() {};

	void drawInfoScreen()
	{
		system("CLS");
		std::cout <<
			"------------------------- .___        _____        -----------------------------\n"
			"------------------------- |   | _____/ ____\\____   -----------------------------\n"
			"------------------------- |   |/    \\   __\\/  _ \\  -----------------------------\n"
			"------------------------- |   |   |  \\  | (  <_> ) -----------------------------\n"
			"------------------------- |___|___|  /__|  \\____/  -----------------------------\n"
			"                                   \\/  			\n"
			"ASCII Characters and what they represent:\n"
			"	-  |	walls\n"
			"	+	doors\n"
			"	.	room flooring\n"
			"	#	corridor / hallway\n"
			"	G  V 	enemies (various upper case letters)\n"
			"	@	player (you)\n"
			"	%	stairs\n"
			"	!	rest area\n"
			"	$	gold\n"
			"	&	ration (food)\n"
			"\n"
			"Player Controls:\n"
			"	Use arrow keys to move (or wasd)\n"
			"	press < e > to use tile block player is on top of(use rest area, use stairs)\n"
			"	Press < F12 > followed by < q > to quit game\n"
			"	Press < f > for eat option\n"
			"\n"
			"Press <space> to continue...\n";

		char wait = '~';
		while (wait != KEY_SPACE)
		{
			wait = _getch();
		}
	}
};


#endif