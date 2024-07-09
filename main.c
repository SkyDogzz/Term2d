#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#define FPS 60
#define SLEEP (1000000 / FPS)

typedef struct Engine {
	int running;
} Engine;

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

	while (engine.running)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		clear_screen();
		put_point(10, 10, '@');
		print_debug_info(w.ws_row, w.ws_col, frames);
		frames++;
		usleep(SLEEP);
	}
	return 0;
}
