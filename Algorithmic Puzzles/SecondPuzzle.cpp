#include <iostream>

using namespace std;
// the second puzzle is similar to what I tried to "dig deeper" in the first puzzle
const int height = 100;
const int width = 100;

// create a 2D array to represent the screen
char screen[height][width];

void setPixel(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height)
		screen[y][x] = '#';
}

// the circle is mirrored on the left and right side
void drawCircle(int centerX, int centerY, int circleRadius) {
	int x = 0;
	int y = circleRadius;
	int decision = 3 - 2*circleRadius; // initial decision parameter
	while (x <= y) {
		// draw the 8 symmetric points
		setPixel(centerX + x, centerY + y);
		setPixel(centerX - x, centerY + y);
		setPixel(centerX + x, centerY - y);
		setPixel(centerX - x, centerY - y);
		setPixel(centerX + y, centerY + x);
		setPixel(centerX - y, centerY + x);
		setPixel(centerX + y, centerY - x);
		setPixel(centerX - y, centerY - x);
		if (decision < 0) {
			decision += 4 * x + 6;
		} else {
			decision += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

int main() {
	for(int row = 0; row < height; row++) {
		for(int col = 0; col < width; col++)
			screen[row][col] = '.';
	}

	int centerX = width / 2;
	int centerY = height / 2;
	const int circleRadius = 5;
	drawCircle(centerX, centerY, circleRadius);

	// print the screen
	for(int row = 0; row < height; row++) {
		for(int col = 0; col < width; col++)
			cout << screen[row][col];
		cout << endl;
	}
	
	return 0;

}