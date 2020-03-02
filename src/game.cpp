#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include <singleRotation.hpp>

using namespace sf;
using namespace std;

#define BORDER 120

namespace game {
	int play = 1;

	Vector2u win_size;

	Font reg_font;
	Font bol_font;
	Text title_text;
	Text frame_text;
	Text playm_text;
	Text device_text;

	Color state0 = Color(30, 30, 30, 255);
	Color state1 = Color(200, 200, 100, 255);
	CellGrid CG = CellGrid(5, 55, 300, 300, 2, {
		state0,
		state1
	});

	
	void load(RenderWindow *window) {
		win_size = window->getSize();
		
		if (!reg_font.loadFromFile("ubuntumono-r.ttf"))
			cout << "The font 'myfont' hasn't been initialized correctly." << endl;
		else cout << "The font 'myfont' has been initialized succesfully!" << endl;
		if (!bol_font.loadFromFile("ubuntumono-b.ttf"))
			cout << "The font 'bol_font' hasn't been initialized correctly." << endl;
		else cout << "The font 'bol_font' has been initialized succesfully!" << endl;
		
		title_text.setFont(bol_font);
		title_text.setCharacterSize(18);
		title_text.setFillColor(Color::White);
		title_text.setPosition(230, 15);
		title_text.setString("Program made by Speykious");

		frame_text.setFont(reg_font);
		frame_text.setCharacterSize(14);
		frame_text.setFillColor(Color::White);
		frame_text.setPosition(5, 5);

		playm_text.setFont(reg_font);
		playm_text.setCharacterSize(14);
		playm_text.setFillColor(Color::White);
		playm_text.setPosition(5, win_size.y-35);

		device_text.setFont(reg_font);
		device_text.setCharacterSize(14);
		device_text.setFillColor(state1);
		device_text.setPosition(530, 35);
		device_text.setString("On the CPU");

		for (int j = BORDER; j<CG.getHeight()-BORDER; j++) {
			for (int i = BORDER; i<CG.getWidth()-BORDER; i++) {
				if (rand()%100<20) CG.setCell(i, j, 1);
			}
		}
		CG.setCell(3, 20, 0);
	}

	int paircut = 0;
	int the_quad[4];
	string playmode;

	double fps;
	long frame = 0;
	double rtime = 0, time = 0, refresh = 0.5;
	void update(double dt) {
		rtime += dt;
		time += dt;
		
		frame+=play;
		switch (play) {
			case -1: playmode = "Backwards"; break;
			case  0: playmode = "Pause"; break;
			case  1: playmode = "Forwards"; break;
		}
		if (rtime>refresh) {
			fps = 1.0/dt;
			rtime -= refresh;
		}

		frame_text.setString("Framerate: "+to_string(fps)+" Hz"+"\n"
							+"Time:      "+to_string(time)+" s"+"\n"
							+"Frame:     "+to_string(frame));
		playm_text.setString("Playmode: " + playmode
						+ "\nPress J (Backwards), K (Pause) or L (Forwards)");


		if (play==1) {
			for (int j = paircut; j<CG.getHeight()-1+paircut; j+=2) {
				for (int i = paircut; i<CG.getWidth()-1+paircut; i+=2) {
					// 1 3 | 0 1 | 2 0
					// 0 2 | 2 3 | 3 1
					CG.getQuad(i, j, &the_quad);
					if (CellGrid::compareQuad(&the_quad, 1, 0, 0, 0)) CellGrid::setQuad(&the_quad, 0, 1, 0, 0);
					else if (CellGrid::compareQuad(&the_quad, 0, 1, 0, 0)) CellGrid::setQuad(&the_quad, 0, 0, 0, 1);
					else if (CellGrid::compareQuad(&the_quad, 0, 0, 0, 1)) CellGrid::setQuad(&the_quad, 0, 0, 1, 0);
					else if (CellGrid::compareQuad(&the_quad, 0, 0, 1, 0)) CellGrid::setQuad(&the_quad, 1, 0, 0, 0);
					CG.setQuad(i, j, &the_quad);
				}
			}
			paircut = (paircut+1)%2;
		}
		else if (play==-1) {
			paircut = (paircut+1)%2;
			for (int j = paircut; j<CG.getHeight()-1+paircut; j+=2) {
				for (int i = paircut; i<CG.getWidth()-1+paircut; i+=2) {
					// 1 3 | 0 1 | 2 0
					// 0 2 | 2 3 | 3 1
					CG.getQuad(i, j, &the_quad);
					if (CellGrid::compareQuad(&the_quad, 1, 0, 0, 0)) CellGrid::setQuad(&the_quad, 0, 0, 1, 0);
					else if (CellGrid::compareQuad(&the_quad, 0, 1, 0, 0)) CellGrid::setQuad(&the_quad, 1, 0, 0, 0);
					else if (CellGrid::compareQuad(&the_quad, 0, 0, 0, 1)) CellGrid::setQuad(&the_quad, 0, 1, 0, 0);
					else if (CellGrid::compareQuad(&the_quad, 0, 0, 1, 0)) CellGrid::setQuad(&the_quad, 0, 0, 0, 1);
					CG.setQuad(i, j, &the_quad);
				}
			}
		}
	}

	void draw(RenderWindow *window) {
		window->draw(title_text);
		window->draw(frame_text);
		window->draw(playm_text);
		window->draw(device_text);
		CG.draw(window);
	}

	int getPlay() {
		return play;
	}

	void setPlay(int value) {
		play = value;
	}
}