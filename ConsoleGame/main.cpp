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

// ball
class Ball {
public:
	//Ball() = default;

	Ball(string body = "()"s, int pos_x = 0, int pos_y = 0) : body_(body), pos_x_(pos_x), pos_y_(pos_y) {};

	size_t GetBodyLength() {
		return body_.size();
	}

	string GetBody() {
		return body_;
	}

	pair<int, int> GetPosition() const {
		return { pos_x_, pos_y_ };
	}

	void SetPosition(int x, int y) {
		pos_x_ = x;
		pos_y_ = y;
	}

private:
	string body_ = "()";
	int pos_x_ = 0;
	int pos_y_ = 0;
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

	void AddBall(int pos_x, int pos_y, Ball& ball) {
		ball.SetPosition(pos_x, pos_y);

		string& ball_string = field_[pos_y];
		ball_string.replace(pos_x, ball.GetBodyLength(), ball.GetBody());
	}

	void UpdateBall(Ball& ball) {
		// две строки, которые нужно изменить
		/*
		string& before = field_[ball.GetPosition().second + 1];
		bool direction_up = false;
		string* after = nullptr;
		if (direction_up) {
			after = &field_[ball.GetPosition().second + 1 - 1];
		}
		else {
			after = &field_[ball.GetPosition().second + 1 + 1];
		}
		*/

		// меняем реальную позицию ball, в зависимости от того, куда двигается мяч.
		bool direction_up = false;
		bool direction_right = true;

		string* before = &field_[ball.GetPosition().second + 1];
		string* after = nullptr;
		if (direction_up) {
			after = &field_[ball.GetPosition().second + 1 - 1];
		}
		else {
			after = &field_[ball.GetPosition().second + 1 + 1];
		}

		int prev_x = ball.GetPosition().first;
		int prev_y = ball.GetPosition().second;

		int next_x;
		int next_y;

		direction_right ? next_x = prev_x + ball.GetBodyLength() : prev_x - ball.GetBodyLength();
		direction_up ? next_y = prev_y - 1 : next_y = prev_y + 1;

		// set pos
		ball.SetPosition(next_x, next_y);

		// просто перерисовываем строки поля, где был и есть мяч.
		before->replace(prev_x + 1, ball.GetBodyLength(), "  "s);
		after->replace(next_x + 1, ball.GetBodyLength(), ball.GetBody());

		/*
		before.replace(ball.GetPosition().first + 1, ball.GetBodyLength(), " "s);

		bool direction_right = true;
		if (direction_right) {
			ball.SetPosition(ball.GetPosition().first + 1 + ball.GetBodyLength(), );
			after->replace(ball.GetPosition().first + 1 + ball.GetBodyLength(), ball.GetBodyLength(), ball.GetBody());
		}
		else {
			after->replace(ball.GetPosition().first + 1 - ball.GetBodyLength(), ball.GetBodyLength(), ball.GetBody());
		}
		*/
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

	// create ball
	Ball ball = Ball();

	// add ball
	field.AddBall(5, 20, ball);

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

			field.UpdateBall(ball);

			// update field
			system("cls");
			field.PrintField();
		}
	}
}