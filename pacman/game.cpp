#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

const float epsilon = .2f;

class WallGridLayout {
	public:
		std::vector<std::vector<bool>> wall_grid;
		float arena_half_size_y, arena_half_size_x;

		WallGridLayout() {
			arena_half_size_y = 46.5f, arena_half_size_x = 42.f;

			wall_grid = {
				{true, true, true, true, true, true, true, true, true, true, true, true, true, true},
				{true, false, false, false, false, false, false, false, false, false, false, false, false, true},
				{true, false, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, false, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, false, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, false, false, false, false, false, false, false, false, false, false, false, false, false},
				{true, false, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, false, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, false, false, false, false, false, false, true, true, false, false, false, false, true},
				{true, true, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, true, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, true, true, true, true, true, false, true, true, false, false, false, false, false},
				{true, true, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, true, true, true, true, true, false, true, true, false, true, true, true, true},
				{false, false, false, false, false, false, false, false, false, false, true, false, false, false},
				{true, true, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, true, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, true, true, true, true, true, false, true, true, false, false, false, false, false},
				{true, true, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, true, true, true, true, true, false, true, true, false, true, true, true, true},
				{true, false, false, false, false, false, false, false, false, false, false, false, false, true},
				{true, false, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, false, true, true, true, true, false, true, true, true, true, true, false, true},
				{true, false, false, false, true, true, false, false, false, false, false, false, false, false},
				{true, true, true, false, true, true, false, true, true, false, true, true, true, true},
				{true, true, true, false, true, true, false, true, true, false, true, true, true, true},
				{true, false, false, false, false, false, false, true, true, false, false, false, false, true},
				{true, false, true, true, true, true, true, true, true, true, true, true, false, true},
				{true, false, true, true, true, true, true, true, true, true, true, true, false, true},
				{true, false, false, false, false, false, false, false, false, false, false, false, false, true},
				{true, true, true, true, true, true, true, true, true, true, true, true, true, true}
			};


			
			for (int row = 0; row < wall_grid.size(); row++) {
				int size = wall_grid[row].size();
				for (int col = size-1; col != -1; col--)
				{
					wall_grid[row].push_back(wall_grid[row][col]);
				}
			}
		}
		
		void drawWall(u32 wall_color) {
			for (int i = 0; i < 31; i++) {
				for (int j = 0; j < 28; j++) {
					if (wall_grid[i][j]) drawRect(3 * j + -40.5f, -3 * i + 45.f, 1.4f, 1.4f, wall_color);
				}
			}
		}

		void drawArena() {
			drawRect(0.f, 0.f, arena_half_size_x, arena_half_size_y, 0x000000);
		}
};


class PacmanMovement {
	public:
		float speed;
		float pacman_pos_x, pacman_pos_y;
		float pacman_speed_x, pacman_speed_y;
		std::vector<std::vector<bool>> wall_grid;
		std::vector<std::vector<int>> pellet_grid;
		int score;

		PacmanMovement(std::vector<std::vector<bool>> wall_layout) {
			wall_grid = wall_layout; // i dont like how this is named, or the reuse of the variable

			pellet_grid = {
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
			{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
			};
			for (int row = 0; row < pellet_grid.size(); row++) {
				int size = pellet_grid[row].size();
				for (int col = size - 1; col != -1; col--)
				{
					pellet_grid[row].push_back(pellet_grid[row][col]);
				}
			}

			score = 0;
			speed = 20.0f;
			pacman_pos_x = 0.f, pacman_pos_y = -6.f;
			pacman_speed_x = 0.f, pacman_speed_y = 0.f;
		}

		void updatePacman(Input* input, float dt) {

			if (pacman_pos_x > 40.5f && std::abs(pacman_pos_y - 3.f) < epsilon) {
				pacman_pos_x = -40.f;
				pacman_pos_y = 3.f;
			}
			else if (pacman_pos_x < -40.5f && std::abs(pacman_pos_y - 3.f) < epsilon) {
				pacman_pos_x = 40.f;
				pacman_pos_y = 3.f;
			}

			if (std::abs(fmod(pacman_pos_x - 1.5f, 3.f)) < epsilon && std::abs(fmod(pacman_pos_y, 3.f)) < epsilon) {
				std::pair<int, int> box_pos = calculateBox();
				int box_row = box_pos.first;
				int box_col = box_pos.second;
				
				eatPellet(box_row, box_col);

				if (wall_grid[box_row + 1][box_col] || wall_grid[box_row - 1][box_col]) {
					pacman_speed_y = 0;
				}
				if (wall_grid[box_row][box_col + 1] || wall_grid[box_row][box_col - 1]) {
					pacman_speed_x = 0;
				}

				if (wall_grid[box_row - 1][box_col] == false && isDown(BUTTON_UP)) {
					pacman_speed_y = speed;
					pacman_speed_x = 0;
				}
				else if (wall_grid[box_row + 1][box_col] == false && isDown(BUTTON_DOWN)) {
					pacman_speed_y = -speed;
					pacman_speed_x = 0;
				}
				else if (wall_grid[box_row][box_col - 1] == false && isDown(BUTTON_LEFT)) {
					pacman_speed_x = -speed;
					pacman_speed_y = 0;
				}
				else if (wall_grid[box_row][box_col + 1] == false && isDown(BUTTON_RIGHT)) {
					pacman_speed_x = speed;
					pacman_speed_y = 0;
				}
			}
			else {
				if (std::abs(fmod(pacman_pos_x-1.5f, 3.f)) < epsilon) {
					if (isDown(BUTTON_UP)) {
						pacman_speed_y = speed;
					}
					else if (isDown(BUTTON_DOWN)) {
						pacman_speed_y = -speed;
					}
				}
				else if (std::abs(fmod(pacman_pos_y, 3.f)) < epsilon) {
					if (isDown(BUTTON_RIGHT)) {
						pacman_speed_x = speed;
					}
					else if (isDown(BUTTON_LEFT)) {
						pacman_speed_x = -speed;
					}
				}
			}
			updatePacmanPos(dt);
			drawPacman();
		}

		void updatePacmanPos(float dt) {
			pacman_pos_x += pacman_speed_x * dt;
			pacman_pos_y += pacman_speed_y * dt;
		}

		void drawPacman() {
			drawRect(pacman_pos_x, pacman_pos_y, 1.5f, 1.5f, 0xf0f000);
		}

		std::pair<int, int> calculateBox() {
			return { std::round((pacman_pos_y - 45.f) / -3.f), std::round((pacman_pos_x + 40.5f) / 3.f) };
		}

		void eatPellet(int row_box, int col_box) {
			if (pellet_grid[row_box][col_box] == 1) {
				pellet_grid[row_box][col_box] = 0;
				++score;
			}
		}

		void drawPellets(u32 pellet_color) {
			for (int i = 0; i < 31; i++) {
				for (int j = 0; j < 28; j++) {
					if (pellet_grid[i][j] == 1) drawRect(3 * j + -40.5f, -3 * i + 45.f, .2f, .2f, pellet_color);
				}
			}
		}

		void displayScore() {
			drawNumber(score, -45.f, 0.f, .7f, 0x000000);
		}
};

//class PelletLayout {
//public:
//	std::vector<std::vector<int>> pellet_grid;
//	int score;
//
//	PelletLayout() {
//		pellet_grid = {
//			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
//			{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
//			{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
//			{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//			{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//		};
//
//
//
//		for (int row = 0; row < pellet_grid.size(); row++) {
//			int size = pellet_grid[row].size();
//			for (int col = size - 1; col != -1; col--)
//			{
//				pellet_grid[row].push_back(pellet_grid[row][col]);
//			}
//		}
//	}
//};

WallGridLayout wall_layout;
PacmanMovement pacman(wall_layout.wall_grid);

internal void
simulate_game(Input* input, float dt) {

	clearScreen(0xffffff);

	wall_layout.drawArena();

	wall_layout.drawWall(0x0000ff);

	pacman.drawPellets(0xFFA500);
	
	pacman.updatePacman(input, dt);

	pacman.displayScore();
	
}
