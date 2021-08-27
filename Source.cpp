#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
using namespace sf;

int main()
{
	const int FIELD_NUM = 10, WIDTH = 32;
	srand(time(0));
	RenderWindow window(VideoMode(400, 400), "Miner");

	Texture t;
	t.loadFromFile("image/sprite.jpg");
	Sprite s(t);

	int gridLogic[FIELD_NUM + 2][FIELD_NUM + 2];//bigger array was taken to prevent out of range,when init mines and numbers
	int gridView[FIELD_NUM + 2][FIELD_NUM + 2];
	/*creating mines in 1 to FIELD_NUM - 2 range(0 -non-active field,1-active field)
	* {
	*	0	0	0	0	0	0
	*	0	1	1	1	1	0
	*	0	1	1	1	1	0
	*	0	1	1	1	1	0
	*	0	1	1	1	1	0
	*	0	0	0	0	0	0
	* }
	*/
	for (int i = 1; i <= FIELD_NUM - 2; i++)
		for (int j = 1; j <= FIELD_NUM - 2; j++)
		{
			gridView[i][j] = 10;
			if (rand() % 5 == 0)gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;

		}
	for (int i = 1; i <= FIELD_NUM - 2; i++)
		for (int j = 1; j <= FIELD_NUM - 2; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / WIDTH;
		int y = pos.y / WIDTH;

		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			// Определяем, была ли нажата кнопка мыши?
			if (e.type == Event::MouseButtonPressed)

				// Если была нажата левая кнопка мыши, то открываем клетку
				if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];

			// Если была нажата правая кнопка мыши, то отображаем флажок
				else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
		}
		window.clear(Color::White);
		for (int i = 1; i <= FIELD_NUM - 2; i++)
			for (int j = 1; j <= FIELD_NUM - 2; j++)
			{
				if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];
				s.setTextureRect(IntRect(gridView[i][j] * WIDTH, 0, WIDTH, WIDTH));
				s.setPosition(i * WIDTH, j * WIDTH);
				window.draw(s);
			}

		window.display();
	}
	return 0;
}