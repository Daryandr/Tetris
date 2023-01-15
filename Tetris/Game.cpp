#include <SFML/Graphics.hpp>
#include "Figure.cpp"
#include "Cube.cpp"
#include <time.h>
using namespace sf;

class Game {
private:
	Texture cube, background, frame, end;
	Figure figure;
	Cube c;
	Sprite sprite_background, sprite_frame, sprite_end;
	Font font;
	Text text;
	int score = 0;
	bool beginGame = true;
public:
	Game() {
		srand(time(0));
		background.loadFromFile("backk.png");
		frame.loadFromFile("framee.png");
		end.loadFromFile("endd.png");
		cube.loadFromFile("tiles.png");
		c = Cube(cube);
		sprite_background = Sprite(background);
		sprite_frame = Sprite(frame);
		sprite_end = Sprite(end);
		sprite_end.setPosition(0, 140);
		font.loadFromFile("arial.ttf");
		text.setFont(font);
		text.setCharacterSize(47);
		text.setFillColor(Color::White);
		text.setPosition(260, 50);
		text.setStyle(Text::Bold);
	}
	void ProcessEvent(const Event& event) {
		if (event.type == Event::KeyPressed)
			if (event.key.code == Keyboard::Up) figure.Rotate();
			else if (event.key.code == Keyboard::Left) figure.Move(-1);
			else if (event.key.code == Keyboard::Right) figure.Move(1);
		if (Keyboard::isKeyPressed(Keyboard::Down)) figure.delay = 0.05;
	}
	void Update(Clock& time) {
		float t = time.getElapsedTime().asSeconds();
		time.restart();
		figure.timer += t;
		figure.Fall();
		if (beginGame)
		{
			beginGame = false;
			figure.FirstAppear();
		}
		CheckLine();
		Speed();
	}
	void Speed() {
		if (score > 12) figure.delay = 0.1;
		else if (score > 9) figure.delay = 0.15;
		else if (score > 6) figure.delay = 0.2;
		else if (score > 3) figure.delay = 0.25;
		else  figure.delay = 0.3;
	}
	void Draw(RenderTarget& render_target) {
		render_target.clear(Color::White);
		render_target.draw(sprite_background);
		text.setString(std::to_string(score));
		render_target.draw(text);
		for (int i = 0; i < figure.getHeight(); i++)
			for (int j = 0; j < figure.getWeight(); j++)
			{
				if (figure.field[i][j] == 0) continue;
				c.setColor(figure.field[i][j]);
				c.SetPosition(j * 18, i * 18);
				render_target.draw(c.getSprite());
			}
		for (int i = 0; i < 4; i++)
		{
			c.setColor(figure.getColor());
			c.SetPosition(figure.a[i].x * 18, figure.a[i].y * 18);
			render_target.draw(c.getSprite());
		}
		render_target.draw(sprite_frame);
	}
	void CheckLine() {
		int k = figure.getHeight() - 1;
		for (int i = figure.getHeight() - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < figure.getWeight(); j++)
			{
				if (figure.field[i][j]) count++;
				figure.field[k][j] = figure.field[i][j];
			}
			if (count < figure.getWeight()) k--;
			else score++;
		}
	}
	bool End(RenderTarget& render_target) {
		for (int i = 0; i < figure.getWeight(); i++)
		{
			if (figure.field[1][i]) {
				render_target.clear(Color::White);
				render_target.draw(sprite_end);
				return true;
			}
		}
		return false;
	}
};