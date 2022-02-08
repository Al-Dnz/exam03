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

void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

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

int is_inside_big(t_circle circle, float j, float i)
{
	float dist;
	dist = sqrtf((circle.x - j) * (circle.x - j) + (circle.y - i) * (circle.y - i));
	if (dist <= circle.radius)
		return 1;
	return 0;
}



int is_inside_little(t_circle circle, float j, float i)
{
	float dist;
	dist = sqrtf((circle.x - j) * (circle.x - j) + (circle.y - i) * (circle.y - i));
	if (dist <= circle.radius - 1.00000000)
		return 1;
	return 0;
}

void	set_circle(char *matrix, t_zone zone, t_circle circle)
{
	int i;
	int j;
	char fond;


       i = 0;
       while ( i < zone.height)
       {
       	j = 0;
       	while (j < zone.width)
       	{

		fond = matrix[i * zone.width + j];
		if (is_inside_big(circle, (float)j, (float)i))
			matrix[i * zone.width + j] = circle.color;
		if (circle.type == 'c')
		{
			if (is_inside_little(circle, (float)j, (float)i))
				matrix[i * zone.width + j] = fond;
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
		ft_putstr("Error: argument\n");
		return (1); 
	}
	if (!(file = fopen(argv[1], "r")))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	t_zone zone;
	t_circle circle;

	char *matrix;
	int ret;

	if ((ret = fscanf(file, "%d %d %c\n", &zone.width, &zone.height, &zone.color)) != 3)
	{
		ft_putstr("Error: Operation file corrupted\n");
		fclose(file);
		return (1);
	}
	if (matrix == NULL)
		return (1);
	while ((ret = fscanf(file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color)) != -1)
	{
		if (ret != 5 || !valid_dimension(circle))
		{
			if (!valid_dimension(circle))
				ft_putstr("Error: Operation file corrupted\n");
			else if (ret != 5)
				ft_putstr("Error: Operation file corrupted\n");
			free(matrix);
			matrix = NULL;
			fclose(file);
			return (1);
		}
		set_circle(matrix, zone, circle);
	}
	draw(matrix, zone);
	free(matrix);
	matrix = NULL;
	fclose(file);
	return (0);
}
