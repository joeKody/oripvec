#include <stdio.h>
#include "oripve.h"

#define WIDTH 800
#define HEIGHT 600

int main(void)
{
	uint32_t background[HEIGHT * WIDTH] = {0};
	orc_canvas bg_canvas = {
		.pixels = background,
		.height = HEIGHT,
		.width = WIDTH
	};

    orc_rect rectangle = {
        .pos = (orc_vec2) {300, 240},
        .height = 300,
        .width = 400
    };

	orc_fill(bg_canvas, 0xFF272727);
    orc_fill_rect(bg_canvas, rectangle, 0xFF0011EE);

	// retarded error handling
	const char * output_path = "output.ppm";
	int err = orc_export_to_ppm(bg_canvas, output_path); 
	if (err)
	{
		fprintf(stderr, "ERROR: could not export file at %s: %s\n", output_path, strerror(err));
		return 1;
	}

	return 0;
}
