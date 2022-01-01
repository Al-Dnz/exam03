#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
**	(x, y) =>  str[y * width + x]
*/


typedef struct background
{
	int width;
	int height;
	char color;
}	t_zone;

typedef struct circle
{
	char type;
	float x;
	float y;
	float radius;
	char color;
} t_circle;

typedef struct error
{
	int d;
	char c;
	float f;
} t_err;

void	draw(char *str, t_zone zone)
{
	int i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if ((i + 1) % zone.width == 0)
			write(1, "\n", 1);
		i++;
	}
}


char *matrix_generator(int width, int height, char col)
{
	char *str;
	int i = 0;

	str = malloc(sizeof(char) * ((width * height) + 1));
	if (str == NULL)
		return (NULL);
	while (i < width * height)
		str[i++] = col;
	str[i] = 0;
	return (str);
}

int valid_dimension(t_circle circle)
{
	return(circle.radius > 0 && circle.radius < 300  && (circle.type == 'c' || circle.type == 'C'));
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	set_circle(char *matrix, t_zone zone, t_circle circle)
{
	int i;
	int j;


       i = 0;
       while ( i < zone.height)
       {
       	j = 0;
       	while (j < zone.width)
       	{
		if (sqrt((circle.x - j) * (circle.x - j) + (circle.y - i) * (circle.y - i)) <= circle.radius)
			matrix[i * zone.width + j] = circle.color;
		if (circle.type == 'c')
		{
			if (sqrt((circle.x - j) * (circle.x - j) + (circle.y - i) * (circle.y - i)) <= circle.radius - 1)
				matrix[i * zone.width + j] = zone.color;
		}
       		j++;
       	}
       	i++;
       }
       

}
 
int main(int argc, char **argv)
{
	FILE *file;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1); 
	}
	if (!(file = fopen(argv[1], "r")))
	{
		write(1, "FILE NO EXIST\n", 14);
		return (1);
	}
	t_zone zone;
	t_circle circle;

	char *matrix;
	int ret;

	if ((ret = fscanf(file, "%d %d %c\n", &zone.width, &zone.height, &zone.color)) != 3)
	{
		printf("(0)probleme dimension zone\n");
		return (1);
		fclose(file);
	}
	if (ret == -1)
	{
		printf("(1)probleme dimension zone\n");
		return (1);
	}
	printf("scanf_ret = %d\n", ret);
	matrix = matrix_generator(zone.width, zone.height, zone.color);
	if (matrix == NULL)
		return (1);
//	circle = (t_circle){0, -1, -1, -1, -1, 0};
	while ((ret = fscanf(file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color)) == 5)
	{
		if (ret != 5 || !valid_dimension(circle))
		{
			if (!valid_dimension(circle))
				printf("(2)probleme dimnesion circle\n");
			else if (ret != 5)
				printf("(3)probleme dimension file\n");
			free(matrix);
			matrix = NULL;
			fclose(file);
			return (1);
		}
		set_circle(matrix, zone, circle);
	}

	draw(matrix, zone);

	return (0);
	// printf("zone\nw=%d, h=%d col=%c\n", zone.width, zone.height, zone.color);
	// printf("scanf_ret = %d\n", ret);
	// printf("circle\ntype=%c x=%f y=%f w=%f h=%f col=%c\n", circle.type, circle.x, circle.y, circle.width, circle.height, circle.color);
	// printf("scanf_ret = %d\n", ret);
}
