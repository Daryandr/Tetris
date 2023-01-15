#include <SFML/Graphics.hpp>
using namespace sf;

class Cube {
private:
	Sprite sprite;
	Texture texture;
public:
	Cube() {}
	Cube(Texture text) :texture(text) {
		sprite = Sprite(texture, IntRect(0, 0, 18, 18));
	}
	Cube(const Cube& copy) :sprite(copy.sprite), texture(copy.texture) {};
	void SetPosition(float x, float y) {
		sprite.setPosition(x, y);
		sprite.move(28, 31);
	}
	Sprite getSprite() { return sprite; }
	void setColor(int n) {
		sprite = Sprite(texture, IntRect(n * 18, 0, 18, 18));
	}
};