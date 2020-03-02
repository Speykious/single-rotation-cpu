#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class CellGrid {
	private:
		int x, y;
		unsigned int width, height, csize;
		vector<Color> colors;
		vector<vector<int>> cells;
		vector<Vertex> cellVertices;

		void initVertices();
		void initCells();
	public:
		static int compareQuad(int (*quad1)[4], int (*quad2)[4]);
		static int compareQuad(int (*quad1)[4], int aa, int ab, int ba, int bb);
		static void setQuad(int (*outquad)[4], int aa, int ab, int ba, int bb);

		CellGrid(unsigned int width, unsigned int height, vector<Color> colors);
		CellGrid(int x, int y, unsigned int width, unsigned int height, vector<Color> colors);
		CellGrid(unsigned int width, unsigned int height, unsigned int csize, vector<Color> colors);
		CellGrid(int x, int y, unsigned int width, unsigned int height, unsigned int csize, vector<Color> colors);
		~CellGrid();

		unsigned int getWidth();
		unsigned int getHeight();

		int getCell(int x, int y);
		void setCell(int x, int y, int v);

		void getQuad(int x, int y, int (*outquad)[4]);
		void setQuad(int x, int y, int vaa, int vab, int vba, int vbb);
		void setQuad(int x, int y, int (*inquad)[4]);

		Color getColor(int i);
		int setColor(int, Color);

		void draw(RenderWindow *window);
};