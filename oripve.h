#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

// Types
typedef struct orc_canvas{
	uint32_t * pixels;
	size_t width;
	size_t height;
} orc_canvas;

typedef struct orc_vec2{
	float x;
	float y;
} orc_vec2;

typedef struct orc_rect{
	orc_vec2 pos;
	size_t width;
	size_t height;
} orc_rect;

// Functions
void orc_fill (orc_canvas canvas, uint32_t color);

void orc_fill_rect(orc_canvas canvas, orc_rect rect, uint32_t color);

int orc_export_to_ppm (orc_canvas canvas, const char * file_path);