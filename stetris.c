#include <SDL2/SDL.h>
#include <time.h>

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

int
I[4][4] = 
{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
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
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
};

int
S[4][4] = {
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
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
void draw(piece, int[]);
void new_piece(piece*);

// Color the Blocks according to their shape

void
colorize()
{

	return;

}

void
new_piece(piece* p)
{
	p->id = rand() % 7;
	memcpy(p->shape, shapes[p->id], sizeof(p->shape));
	for (int i = 0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			printf("%d ", p->shape[i][j]);
		}
		puts("");
	}
}

void
draw_map(int map[ROWS*COLS])
{
	int counter = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j=0; j < COLS; j++) {
			printf("%d", map[counter++]);
		}
		puts("");
	}

}

void
draw(piece p, int map[ROWS*COLS])
{

	/* Screen */
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	
	/* Pieces */
	SDL_Rect r = {p.x, p.y, BLOCK_SIZE, BLOCK_SIZE};
	SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);


	int counter = ((p.x / BLOCK_SIZE) * COLS) + (p.y / BLOCK_SIZE);

	for (int i = 0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			if (map[counter] == 1 && p.shape[i][j] == 1) {return;}

			if (p.shape[i][j] == 1) {
				/* Inverted */
				r.x = p.x + (j * 32);
				r.y = p.y + (i * 32);
				map[counter] = 1;
				colorize(p.id);
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
//	piece p = {0, 0, 0, 0};
	piece p = {128, 128, 0, 0};
	new_piece(&p);
	
	int gravity = 1;
	int last_time = 0;
	int curr_time;
    while (1) {

		curr_time = SDL_GetTicks();
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT) {
            break;
        }
		/* Input Handling */
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:

			case SDLK_RIGHT:

			case SDLK_DOWN:

			case SDLK_SPACE:

			default:
				break;
			}
		}
		/* Frames */
		if (curr_time > last_time + 200) {
			draw(p, map);
			p.y = p.y + 32;
		//	draw_map(map);
			last_time = curr_time;
		}
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
	return 0;
}
