#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;
float arena_half_size_y = 93.f/2, arena_half_size_x = 84.f/2;

class WallGridLayout {
	public:
		std::vector<std::vector<int>> wall_grid;

		WallGridLayout() {
			wall_grid = {
				{false, false, false, false, false, false, false, false, false, false, false, false, false, false},
				{false, true, true, true, true, true, true, true, true, true, true, true, true, false},
				{false, true, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, true, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, true, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, true, true, true, true, true, true, true, true, true, true, true, true, true},
				{false, true, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, true, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, true, true, true, true, true, true, false, false, true, true, true, true, false},
				{false, false, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, false, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, false, false, false, false, false, true, false, false, true, true, true, true, true},
				{false, false, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, false, false, false, false, false, true, false, false, true, false, false, false, false},
				{true, true, true, true, true, true, true, true, true, true, false, true, true, true},
				{false, false, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, false, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, false, false, false, false, false, true, false, false, true, true, true, true, true},
				{false, false, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, false, false, false, false, false, true, false, false, true, false, false, false, false},
				{false, true, true, true, true, true, true, true, true, true, true, true, true, false},
				{false, true, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, true, false, false, false, false, true, false, false, false, false, false, true, false},
				{false, true, true, true, false, false, true, true, true, true, true, true, true, true},
				{false, false, false, true, false, false, true, false, false, true, false, false, false, false},
				{false, false, false, true, false, false, true, false, false, true, false, false, false, false},
				{false, true, true, true, true, true, true, false, false, true, true, true, true, false},
				{false, true, false, false, false, false, false, false, false, false, false, false, true, false},
				{false, true, false, false, false, false, false, false, false, false, false, false, true, false},
				{false, true, true, true, true, true, true, true, true, true, true, true, true, false},
				{false, false, false, false, false, false, false, false, false, false, false, false, false, false}
			};


			
			for (int row = 0; row < wall_grid.size(); row++) {
				int size = wall_grid[row].size();
				for (int col = size-1; col != -1; col--)
				{
					wall_grid[row].push_back(wall_grid[row][col]);
				}
			}
		}
};



// try to make a layout class that stores each of the aspects of the board?

internal void
simulate_game(Input* input, float dt) {

	WallGridLayout wall_layout;

	clear_screen(0xffffff);

	draw_rect(0.f, 0.f, arena_half_size_x, arena_half_size_y, 0x000000);

	draw_wall(wall_layout.wall_grid, 0x0000ff);

	
	float speed = 50.0f; //units per second
	if (is_down(BUTTON_UP)) player_pos_y += speed * dt;
	if (is_down(BUTTON_DOWN)) player_pos_y -= speed * dt;
	if (is_down(BUTTON_RIGHT)) player_pos_x += speed * dt;
	if (is_down(BUTTON_LEFT)) player_pos_x -= speed * dt;

	draw_rect(player_pos_x, player_pos_y, 1.5f, 1.5f, 0xf0f000);
	
}
