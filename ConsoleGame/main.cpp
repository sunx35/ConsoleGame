// Игра в консоле, где есть рамки поля, персонаж (Player). Все описано при помощи символов.
// Персонаж может перемещаться влево-вправо.
// Возможно персонаж будет стрелять, или отбивать мячик.
// 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

// player
class Player {
	string body = "***";
	int pos_x = 0;
	int pos_y = 0;
};

int main() {
	// draw field
	Field field(80, 40);

	field.PrintField();

	// draw player

	
}