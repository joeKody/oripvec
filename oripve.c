#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

// I have no idea what I am doing

// Types (?)

typedef struct orc_canvas
{
	uint32_t * pixels; // a 2D array of all canvas' pixels
	size_t width;
	size_t height; // I have no idea what size_t is 
} orc_canvas;

typedef struct orc_vec2
{
	float x;
	float y;
} orc_vec2;

typedef struct orc_rect
{
	orc_vec2 pos;
	size_t width;
	size_t height;
} orc_rect;

// Functions (?)

void orc_fill (orc_canvas canvas, uint32_t color)
{
	for (int i = 0; i < canvas.width * canvas.height; i++)
	{
		canvas.pixels[i] = color;
	}
}

void orc_fill_rect(orc_canvas canvas, orc_rect rect, uint32_t color)
{
	uint32_t first_pixel = (rect.pos.y * canvas.width) + rect.pos.x;
	// TODO: filling without checking if it is outside border
	uint32_t max_x = rect.pos.x + rect.width;
	uint32_t max_y = rect.pos.y + rect.height;

	// rect_x + dx = current_x
	// dx = rect_x + rect_widh - current_x
	for (size_t dy = 0; dy < rect.height; dy++)
	{
		uint32_t current_y = dy + rect.pos.y;
		if (current_y > canvas.height)
			return;
		if (current_y < 0)
			continue;
		
		for (size_t dx = 0; dx < rect.width; dx++)
		{
			uint32_t current_x = dx + rect.pos.x;
			if (current_x > canvas.width)
				break;
			if (current_x < 0)
				continue;

			canvas.pixels[(current_y * canvas.width) + current_x] = color;
		}
	}
}

/* idk what ppm is and how to handle files in c. so im copying and paste here
	ppm file format, newlines/spaces = whitespaces
	P6 				(file format, ppm = P6)
	WIDTH HEIGHT 	(decimal)
	MAX_COLOR_value	(decimal less than 2bytes)
	R1
	G1
	B1
	R2... (and so on)

	idk how to handle error lmao
*/
int orc_export_to_ppm (orc_canvas canvas, const char * file_path)
{
	FILE * f = NULL;
	{
		f = fopen(file_path, "wb");
		if (f == NULL)
			return errno;
		
		fprintf(f, "P6\n%zu %zu\n255\n", canvas.width, canvas.height); 
		
		if (ferror(f))
		{
			if (f)
				fclose(f);
			return errno;	
		}

		for (size_t i = 0; i < canvas.width * canvas.height; i++)
		{
			uint32_t current_pixel = canvas.pixels[i];	
			uint8_t bytes[3] = 
			{
				(current_pixel>>(8*0))&0xFF,
				(current_pixel>>(8*1))&0xFF,
				(current_pixel>>(8*2))&0xFF
			};

			fwrite(bytes, sizeof(bytes), 1, f);
			if (ferror(f))
			{
				if (f)
					fclose(f);
				return errno;
			}
		}
	}
	if (f)
		fclose(f);
	return 0;
}
