#include <iostream>
#include <utility>
#include <vector>
using namespace std;


enum class Direction : char {
	top, left, right, down
};

struct Position {
	size_t row, col;
	Position(size_t _row = 0, size_t _col = 0) : row(_row), col(_col) {}
};

class Map {
	vector<vector<char>> map;
public:
	explicit Map(size_t _size) {
		if (!_size) throw;
		for (auto i = 0; i < _size; i++)
			map.emplace_back(_size, '.');
	}

	const vector<char>& operator[](size_t index) const { return map[index]; }
	vector<char>& operator[](size_t index) { return map[index]; }

	// in spite of the fact that map size is N x N
	// it returns pair 'cause it seems more natural
	pair<size_t, size_t> size() { return { map.size(), map[0].size() }; }

	friend std::ostream& operator<<(std::ostream& out, const Map& M) {
		for (auto row : M.map) {
			for (auto cell : row)
				out << cell << " ";
			out << endl;
		}
		return out;
	}
};


class Robot {
	Direction direction;
	Position pos;
	Map* map;
public:
	explicit Robot(Map* _map, const Position& _pos, Direction dir)
		: direction(dir), pos(_pos), map(_map) {}

	const Direction& get_direction() const { return direction; }
	const Position& get_position() const { return pos; }

	void rotate(const Direction& dir) { direction = dir; }

	bool can_move() {
		auto map_size = map->size();
		switch (direction) {
		case Direction::top:
			return pos.row > 1;
		case Direction::left:
			return pos.col > 1;
		case Direction::right:
			return pos.col + 1 < map_size.first;
		case Direction::down:
			return pos.row + 1 < map_size.first;
		}
		return false;
	}

	void move() {
		switch (direction) {
		case Direction::top:
			pos.row--;
			break;
		case Direction::left:
			pos.col--;
			break;
		case Direction::right:
			pos.col++;
			break;
		case Direction::down:
			pos.row++;
			break;
		}
	}

	void draw_line(const Position& target, 
		Direction fst_dir, Direction snd_dir, 
		bool main_diag = true) {
		print();

		if (can_move()) move();
		else return;
		rotate(fst_dir);

		int step = 0;
		while (target.col != pos.col || target.row != pos.row) {
			move();
			if (++step == 2) {
				if (direction == fst_dir) rotate(snd_dir);
				else rotate(fst_dir);
				step = 0;
			}

			if (main_diag) {
				if (pos.col == pos.row) print();
			}
			else if (static_cast<size_t>(pos.col + pos.row + 1) == map->size().first) 
				print();

		}
	}
	
	void print() {
		map->operator[](pos.row)[pos.col] = 'X'; // any symbol
	}
};


void print_map(Map&, Robot&);


int main() {
	size_t n;
	if (!(cin >> n)) {
		cerr << "Bad input\n";
		return -1;
	}

	Map map(n);

	cout << "Map at the beginning:\n" << map << endl;
	Robot robot(&map, { 0, 0 }, Direction::top);

	print_map(map, robot);

	cout << "Map at the end:\n" << map << endl;

	cin.get();
	return 0;
}


void print_map(Map& map, Robot& robot) {
	// algorithm is based on concept "less rotations"
	auto[rows, cols] = map.size();

	// now it works only if start-vertex is (0; 0) with top direction
	robot.rotate(Direction::right);
	robot.draw_line({ rows - 1, cols - 1 },
		Direction::down, Direction::right);

	robot.rotate(Direction::top);

	for (int i = 1; i < cols; i++) robot.move();

	robot.rotate(Direction::left);

	robot.draw_line({ rows - 1, 0 },
		Direction::down, Direction::left, false);
}
