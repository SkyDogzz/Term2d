#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#define ASPECT_RATIO 1.5
#define FPS 60
#define SLEEP (1000000 / FPS)

typedef struct Engine {
	int running;
} Engine;

typedef struct Point {
	float x, y;
} Point;

void clear_screen(void)
{
	printf("\033[2J");
	fflush(stdout);
}

void put_point(int x, int y, char c)
{
	printf("\033[%d;%dH%c", x, y, c);
	fflush(stdout);
}

void print_debug_info(int lines, int columns, int frames)
{
	printf("\033[%d;1H", lines);
	printf ("Lines = %d, Colums = %d, Frames = %d\n", lines, columns, frames);
}

int main (void)
{
	struct Engine engine;
	struct winsize w;
	int frames = 1;
	engine.running = 1;

	int point_nbr = 20;
	struct Point p[20];

	for (int i = 0; i < point_nbr; i++)
	{
		p[i].x = 1 + i;
		p[i].y = 1 + i;
	}

	while (engine.running)
	{
		clear_screen();
		for (int i = 0; i < point_nbr; i++)
		{
			p[i].y += ASPECT_RATIO;
			p[i].x++;
			if(p[i].y >= w.ws_col)
				p[i].y = 0;
			if(p[i].x >= w.ws_row)
				p[i].x = 0;
			put_point(p[i].x / 1, p[i].y / 1, '@');
		}

		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		print_debug_info(w.ws_row, w.ws_col, frames);
		frames++;
		usleep(SLEEP);
	}
	return 0;
}
