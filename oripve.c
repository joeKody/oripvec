#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
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

// Functions (?)

void orc_fill (orc_canvas canvas, uint32_t color)
{
	for (int i = 0; i < canvas.width * canvas.height; i++)
	{
		canvas.pixels[i] = color;
	}

}

// idk what ppm is and how to handle files in c. so im copying and paste here
/* ppm file format, newlines/spaces = whitespaces
	P6 				(file format, ppm = P6)
	WIDTH HEIGHT 	(decimal)
	MAX_COLOR_value	(decimal less than 2bytes)
	R1
	G1
	B1
	R2... (and so on)
*/
// idk how to handle error lmao
int orc_export_to_ppm (orc_canvas canvas, const char * file_path)
{
	FILE * f = NULL;
	{
		f = fopen(file_path, "wb");
		if (f == NULL)
			return -1;
		
		fprintf(f, "P6\n%zu %zu\n255\n", canvas.width, canvas.height); 
		
		if (ferror(f))
		{
			if (f)
				fclose(f);
			return -1;	
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
				return -1;
			}
		}
	}
	if (f)
		fclose(f);
	return 0;
}


int main(void)
{
	// array 	 height width  rgb = 0
	uint32_t bruh[600 * 800] = {0};
	orc_canvas balls = {
		.pixels = bruh,
		.height = 600,
		.width = 800
	};

	orc_fill(balls, 0xFF00FF00); // fill balls with green;
	
	// retarded error handling
	int error = orc_export_to_ppm(balls, "output.ppm"); 
	if (error < 0)
	{
		printf("ayo smth went wrong about exporting the file\n");
		return -1;
	}

	printf("ezclap\n");
	return 0;
}
