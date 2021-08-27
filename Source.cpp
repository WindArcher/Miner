#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
using namespace sf;

int main()
{
	int FIELD_NUM = 4; const int WIDTH = 32;
	srand(time(0));
	RenderWindow window(VideoMode(400, 400), "Miner");
	std::cout << "Enter field size: ";
	std::cin >> FIELD_NUM;
	Texture t;
	t.loadFromFile("image/sprite.jpg");
	Sprite s(t);

	std::vector<std::vector<int>> gridLogic(FIELD_NUM + 2, std::vector<int>(FIELD_NUM + 2));//bigger array was taken to prevent out of range,when init mines and numbers
	std::vector<std::vector<int>> gridView(FIELD_NUM + 2, std::vector<int>(FIELD_NUM + 2));
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
	for (int i = 1; i <= FIELD_NUM; i++)
		for (int j = 1; j <= FIELD_NUM; j++)
		{
			gridView[i][j] = 10;
			if (rand() % 5 == 0)gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;

		}

	for (int i = 1; i <= FIELD_NUM ; i++)
		for (int j = 1; j <= FIELD_NUM; j++)
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
		Event e;
		window.clear(Color::White);
		for (int i = 1; i <= FIELD_NUM; i++)
			for (int j = 1; j <= FIELD_NUM; j++)
			{

				s.setTextureRect(IntRect(gridView[i][j] * WIDTH, 0, WIDTH, WIDTH));
				s.setPosition(i * WIDTH, j * WIDTH);
				window.draw(s);
			}

		window.display();
		while (window.pollEvent(e))
		{
			Vector2i pos = Mouse::getPosition(window);
			int x = pos.x / WIDTH;
			int y = pos.y / WIDTH;

			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					gridView[x][y] = gridLogic[x][y];
					if (gridLogic[x][y] == 9)
						for (int i = 1; i <= FIELD_NUM; i++)
							for (int j = 1; j <= FIELD_NUM; j++)
							{
								gridView[i][j] = gridLogic[i][j];
							}
				}
				else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
				break;
			}
		}
			
		}
		return 0;
	}