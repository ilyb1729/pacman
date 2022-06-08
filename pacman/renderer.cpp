internal void 
clear_screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void 
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {	

	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//change to pixels 
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}



/*
internal void
draw_pellet(int xGrid, int yGrid, float pellet_radius, u32 color) {

}*/



internal void
draw_wall(std::vector<std::vector<int>> wall_grid, u32 color) {
	//do calculations to find the size of each box
	//do more calcuations to find the positions of the center
	//31*2-->for each center on the vertical
	//28*2--> for each center on the horizontal
	//draw rectangle of different color to represent a wall
	//draw rectangle of different color to represent a wall
	//draw a border 93 to 84% of the smaller dimension
	//case-work for how the walls look like later

	for (int i=0; i<31; i++) {
		for (int j=0; j<28; j++) {
			if (wall_grid[i][j] == false) draw_rect(3 * j + 1.5f - 84.f/2, -3 * i + 1.5f + 93.f/2 - 3, 1.4f, 1.4f, color);
		}
	} 
				
}
