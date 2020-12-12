#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>

#define WINW 320
#define WINH 640
#define ROWS 20
#define COLS 10
#define BLOCK_SIZE 32

/* Constants */
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Rect rect;
SDL_Event event;

typedef struct {
	int x;
	int y;
	int id;
	int shape[4][4];
} piece;

/* Tetrominoes */

int mapius[200] = {0};

int
I[4][4] = 
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
};

int
O[4][4] = 
{
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
};

int
Z[4][4] = 
{
	{0, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
};

int
S[4][4] = {
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
};


int
L[4][4] = 
{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
};

int
T[4][4] = 
{
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
};

int
J[4][4] = {
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
};


int (*shapes[7])[4][4] = {
	&I,
	&T,
	&O,
	&L,
	&Z,
	&S,
	&J,
};


/* Declarations */
void input();
int init();
void new_piece(piece*);
void draw(piece*, int*);

// Color the Blocks according to their shape


void 
save_map(piece* p, int* map)
{

	
	for (int i = 0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			if (map[(p->x / 32) + (p->y / 32)] == 1) {
				 continue; 
			}
			
			
				
		}
	}


}

void
new_piece(piece* p)
{
	p->id = rand() % 7;
	p->x = 64;
	p->y = -128;
	memcpy(p->shape, shapes[p->id], sizeof(p->shape));
	for (int i = 0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			printf("%d ", p->shape[i][j]);
		}
		puts("");
	}
}

void
draw_map(int* map)
{
	int counter = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j=0; j < COLS; j++) {
			printf("%d",  map[counter++]);
		}
		puts("");
	}
	puts("");

}

void
draw(piece* p, int* map)
{
	/* Screen */
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);


	/* MAP */
	
	SDL_Rect rr = { 0, 0, BLOCK_SIZE, BLOCK_SIZE };
	for (int i = 0; i < ROWS; i++) {
		for (int j=0; j < COLS; j++) {
			if (map[i * COLS + j] == 1) {
				/* Inverted */
				rr.y = i * 32;
				rr.x = j * 32;
				SDL_RenderDrawRect(renderer,&rr);
			}
		}
	}
	
	/* Pieces */
	SDL_Rect r = {p->x, p->y, BLOCK_SIZE, BLOCK_SIZE};
	SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);

	int counter = ((fabs(p->x) / BLOCK_SIZE) * COLS) + (p->y / BLOCK_SIZE);

	for (int i = 0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			if (p->shape[i][j] == 1) {
				/* Inverted */
				r.x = p->x * j;
				r.y = p->y  * i;
				if (p->x >= 0) map[counter] = 1;
				SDL_RenderDrawRect(renderer,&r);
			}

			counter++;
		}
		counter = counter + COLS - 4; /* 4 the row and col size of the tetrominoes' map */
	}
	SDL_RenderPresent(renderer);
	
	
}

int 
init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(WINW, WINH, SDL_WINDOW_OPENGL, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    return 0;
}


int
main()
{
	init();
	srand(time(NULL));
	int map[ROWS*COLS] = {0};
	int last_time = 0;
	int lag_time = 100;
	int curr_time;
	int counter = -1;

	draw_map(map);
	piece p;
	new_piece(&p);
	
	while (1) {

		curr_time = SDL_GetTicks();

		if (event.type == SDL_QUIT) {
			return 0;
		}
		/* Frames */
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					p.x = p.x - 32;
					printf("Here");
					draw(&p, map);
					break;

				case SDLK_RIGHT:
					p.x = p.x + 32;
					draw(&p, map);
					break;

				case SDLK_DOWN:

				case SDLK_SPACE:

				default:
					break;
				}
			}
		}

		if (curr_time > last_time + 200) {
			draw_map(map);
			if (counter++ > ROWS - 1) {
				counter = 0;
				save_map(&p, map);
				new_piece(&p); 
			}
			p.y = p.y + 32;
			draw(&p, map);
			last_time = curr_time;
		}
	}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
	return 0;
}
