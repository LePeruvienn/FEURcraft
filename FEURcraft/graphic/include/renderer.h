#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "window.h"

#include <stdbool.h>

typedef struct Renderer Renderer;

struct Renderer
{
	Camera camera;
	Window* window;
};

bool renderer_init(Renderer* renderer, Window* window);

void renderer_update_viewport(Renderer* renderer);

void renderer_clear();

#endif // RENDERER_H
