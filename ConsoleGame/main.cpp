// Игра в консоле, где есть рамки поля, персонаж (Player). Все описано при помощи символов.
// Персонаж может перемещаться влево-вправо.
// Возможно персонаж будет стрелять, или отбивать мячик.
// 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// player
class Player {
public:
	Player() = default;

	size_t GetBodyLength() {
		return body_.size();
	}

	string GetBody() {
		return body_;
	}

	int GetPosition() {
		return pos_x_;
	}

	void SetPosition(int x) {
		pos_x_ = x;
	}

private:
	string body_ = "-----";
	int pos_x_ = 0;
	//int pos_y_ = 0;
};

// field
class Field {
public:
	Field(int width, int height) : width_(width), height_(height) {
		string top_bottom_string = angle_bound_char + string(width_, horizontal_bound_char_) + angle_bound_char;
		string center_string = vertical_bound_char_ + string(width_, ' ') + vertical_bound_char_;

		field_.push_back(top_bottom_string);
		for (int i = 0; i < height_; i++) {
			field_.push_back(center_string);
		}
		field_.push_back(top_bottom_string);
	}

	void AddPlayer(Player& player) {
		string& player_string = field_[field_.size() - 2];
		player_string.replace(40, player.GetBodyLength(), player.GetBody());
	}

	void PrintField() {
		for (auto &each : field_) {
			cout << each << endl;
		}
	}

private:
	int width_ = 80;
	int height_ = 40;
	char horizontal_bound_char_ = '=';
	char vertical_bound_char_ = '|';
	char angle_bound_char = '#';

	vector<string> field_;
};

int main() {
	// create field
	Field field(80, 40);

	/*while (true) {
		field.PrintField();
	}*/

	// create player
	Player player = Player();

	// add player
	field.AddPlayer(player);

	// draw field
	field.PrintField();
	
}