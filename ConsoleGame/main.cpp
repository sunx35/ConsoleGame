// Игра в консоле, где есть рамки поля, персонаж (Player). Все описано при помощи символов.
// Персонаж может перемещаться влево-вправо.
// Возможно персонаж будет стрелять, или отбивать мячик.
// 

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <Windows.h>
#include <WinUser.h>
//#include <Windows.h>
//#include <conio.h>

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
		player.SetPosition(width_ / 2 - player.GetBodyLength() / 2);

		string& player_string = field_[field_.size() - 2];
		player_string.replace((player.GetPosition() + 1), player.GetBodyLength(), player.GetBody());
	}

	void UpdatePlayer(Player& player) {
		string& player_string = field_[field_.size() - 2];
		player_string = vertical_bound_char_ + string(width_, ' ') + vertical_bound_char_;
		player_string.replace((player.GetPosition() + 1), player.GetBodyLength(), player.GetBody());
	}

	void PrintField() const {
		for (auto &each : field_) {
			cout << each << endl;
		}
	}

	int GetWidth() const {
		return width_;
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

	// create player
	Player player = Player();

	// add player
	field.AddPlayer(player);

	// draw field
	//field.PrintField();

	auto start_time = chrono::steady_clock::now();
	int interval = 100; // ms

	/*char c;
	int key_code;*/

	while (true) {
		if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count() > interval) {
			start_time = chrono::steady_clock::now();

			// input
			//c = _getch();
			//key_code = static_cast<int>(c);
			//if (key_code == 75)
			//{
			//	//cout << "Нажата клавиша Влево\n";
			//	player.SetPosition(player.GetPosition() - 1);
			//}
			//if (key_code == 77)
			//{
			//	//cout << "Нажата клавиша Вправо\n";
			//	player.SetPosition(player.GetPosition() + 1);
			//}

			if (GetAsyncKeyState(VK_LEFT)) //проверяем, нажата ли клафиша влево
			{
				int new_pos = player.GetPosition() - 1;
				if (new_pos >= 0 && new_pos <= field.GetWidth() - player.GetBodyLength()) {
					player.SetPosition(new_pos);
				}
			}
			if (GetAsyncKeyState(VK_RIGHT)) //проверяем, нажата ли клафиша вправо
			{
				int new_pos = player.GetPosition() + 1;
				if (new_pos >= 0 && new_pos <= field.GetWidth() - player.GetBodyLength()) {
					player.SetPosition(new_pos);
				}
			}
			
			// update player
			field.UpdatePlayer(player);

			// update field
			system("cls");
			field.PrintField();
		}
	}
}