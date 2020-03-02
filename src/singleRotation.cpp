#include <singleRotation.hpp>

int CellGrid::compareQuad(int (*quad1)[4], int (*quad2)[4]) {
	return ((*quad1)[0] == (*quad2)[0]
		 && (*quad1)[1] == (*quad2)[1]
		 && (*quad1)[2] == (*quad2)[2]
		 && (*quad1)[3] == (*quad2)[3]);
}

int CellGrid::compareQuad(int (*quad1)[4], int aa, int ab, int ba, int bb) {
	return ((*quad1)[0] == aa
		 && (*quad1)[1] == ab
		 && (*quad1)[2] == ba
		 && (*quad1)[3] == bb);
}

void CellGrid::setQuad(int (*outquad)[4], int aa, int ab, int ba, int bb) {
	(*outquad)[0] = aa;
	(*outquad)[1] = ab;
	(*outquad)[2] = ba;
	(*outquad)[3] = bb;
}

#pragma region Constructors and Desctructor
CellGrid::CellGrid(unsigned int width, unsigned int height, vector<Color> colors) {
	this->x = 0;
	this->y = 0;
	this->csize = 2;
	this->width = width;
	this->height = height;
	this->colors = colors;
	
	this->initCells();
	this->initVertices();
}

CellGrid::CellGrid(int x, int y, unsigned int width, unsigned int height, vector<Color> colors) {
	this->x = x;
	this->y = y;
	this->csize = 2;
	this->width = width;
	this->height = height;
	this->colors = colors;
	
	this->initCells();
	this->initVertices();
}

CellGrid::CellGrid(unsigned int width, unsigned int height, unsigned int csize, vector<Color> colors) {
	this->x = 0;
	this->y = 0;
	this->csize = csize;
	this->width = width;
	this->height = height;
	this->colors = colors;
	
	this->initCells();
	this->initVertices();
}

CellGrid::CellGrid(int x, int y, unsigned int width, unsigned int height, unsigned int csize, vector<Color> colors) {
	this->x = x;
	this->y = y;
	this->csize = csize;
	this->width = width;
	this->height = height;
	this->colors = colors;

	this->initCells();
	this->initVertices();
}

CellGrid::~CellGrid() {}
#pragma endregion


void CellGrid::initVertices() {
	this->cellVertices = vector<Vertex>(4*width*height, Vertex(Vector2f(0, 0), this->colors[0], Vector2f(0, 0)));
	for (int j = 0; j<this->height; j++) {
		for (int i = 0; i<this->width; i++) {
			this->cellVertices[4*this->width*j+4*i].position.x = x+i*this->csize;
			this->cellVertices[4*this->width*j+4*i].position.y = y+j*this->csize;

			this->cellVertices[4*this->width*j+4*i+1].position.x = x+i*this->csize;
			this->cellVertices[4*this->width*j+4*i+1].position.y = y+(j+1)*this->csize;

			this->cellVertices[4*this->width*j+4*i+2].position.x = x+(i+1)*this->csize;
			this->cellVertices[4*this->width*j+4*i+2].position.y = y+(j+1)*this->csize;

			this->cellVertices[4*this->width*j+4*i+3].position.x = x+(i+1)*this->csize;
			this->cellVertices[4*this->width*j+4*i+3].position.y = y+j*this->csize;
		}
	}
}

void CellGrid::initCells() {
	vector<int> col = vector<int>(this->height, 0);
	this->cells = vector<vector<int>>(this->width, col);
}


unsigned int CellGrid::getWidth() { return width; }
unsigned int CellGrid::getHeight() { return height; }

int CellGrid::getCell(int x, int y) {
	return this->cells[x%this->width][y%this->height];
}

void CellGrid::setCell(int x, int y, int v) {
	int xm = x%this->width; int ym = y%this->height;
	this->cells[xm][ym] = v%this->colors.size();

	Color state = this->colors[v%this->colors.size()];
	this->cellVertices[4*this->width*ym+4*xm].color   = state;
	this->cellVertices[4*this->width*ym+4*xm+1].color = state;
	this->cellVertices[4*this->width*ym+4*xm+2].color = state;
	this->cellVertices[4*this->width*ym+4*xm+3].color = state;
}

#pragma region Quad functions
void CellGrid::getQuad(int x, int y, int (*outquad)[4]) {
	(*outquad)[0] = this->getCell(x, y);
	(*outquad)[1] = this->getCell(x+1, y);
	(*outquad)[2] = this->getCell(x, y+1);
	(*outquad)[3] = this->getCell(x+1, y+1);
}

void CellGrid::setQuad(int x, int y, int vaa, int vab, int vba, int vbb) {
	this->setCell(x, y, vaa);
	this->setCell(x+1, y, vab);
	this->setCell(x, y+1, vba);
	this->setCell(x+1, y+1, vbb);
}

void CellGrid::setQuad(int x, int y, int (*inquad)[4]) {
	this->setCell(x, y, (*inquad)[0]);
	this->setCell(x+1, y, (*inquad)[1]);
	this->setCell(x, y+1, (*inquad)[2]);
	this->setCell(x+1, y+1, (*inquad)[3]);
}
#pragma endregion


Color CellGrid::getColor(int i) { return colors[i%colors.size()]; }

int CellGrid::setColor(int i, Color color) {
	if (this->colors.size()>=i) return -1;
	this->colors[i] = color; return 0;
}

void CellGrid::draw(RenderWindow *window) {
	window->draw(&*this->cellVertices.begin(), this->cellVertices.size(), Quads);
}