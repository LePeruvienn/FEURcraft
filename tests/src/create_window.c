#include "window.h"

int main()
{
	window w = create_window(960, 600, "Create Window test");

	free_window(w);

	return 0;
}
