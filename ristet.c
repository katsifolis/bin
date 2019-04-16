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
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
};


int
L[4][4] = 
{
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
};

int
T[4][4] = 
{
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
};

int
J[4][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
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
	
	int counter = (p.x + p.y) / BLOCK_SIZE;
	for (int i = 0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			if (p.shape[i][j] == 1 && map[counter] == 0) {
				/* Inverted */
				r.x = (j * 32);
				r.y = (i * 32);
				map[counter] = 1;
				SDL_RenderDrawRect(renderer,&r);
			}
			counter++;
		}
		counter = counter + COLS - 4;
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
	piece p = {0, 0, 0, 0};
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
			case SDLK_a:
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xee);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
			}
		}
		/* Frames */
		if (curr_time > last_time + 100) {
			draw(p, map);
			last_time = curr_time;
			break;
		}
    }

	draw_map(map);	
	SDL_Delay(1000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
	return 0;
}
