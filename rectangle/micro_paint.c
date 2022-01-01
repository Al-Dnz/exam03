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

typedef struct rectangle
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char color;
} t_rec;

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

int valid_dimension(t_rec rec)
{
	return(rec.width > 0 && rec.width < 300 && rec.height > 0 && rec.height < 300 && (rec.type == 'r' || rec.type == 'R'));
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	set_rectangle(char *matrix, t_zone zone, t_rec rec)
{
	int i;
	int j;

	int Xbr = rec.x + rec.width -1;
	int Ybr = rec.y + rec.height -1;

	int Xbr_bis = Xbr - 1;
	int Ybr_bis = Ybr -1;
       i = 0;
       while ( i < zone.height)
       {
       	j = 0;
       	while (j < zone.width)
       	{
       		if (rec.x <= j && j <= ft_min(Xbr, zone.width -1) && rec.y <= i && i  <= ft_min(Ybr, zone.height -1))
       			matrix[i * zone.width + j] = rec.color;

       		if (rec.type == 'r' && rec.x + 1 <= j && j <= ft_min(Xbr_bis, zone.width -1) && rec.y + 1 <= i && i  <= ft_min(Ybr_bis, zone.height -1))
       			matrix[i * zone.width + j] = zone.color;

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
	t_rec rec;

	char *matrix;
	int ret;

	if ((ret = fscanf(file, "%d %d %c\n", &zone.width, &zone.height, &zone.color)) != 3)
	{
		printf("probleme dimnesion zone\n");
		return (1);
		fclose(file);
	}
	printf("scanf_ret = %d\n", ret);
	matrix = matrix_generator(zone.width, zone.height, zone.color);
	if (matrix == NULL)
		return (1);
//	rec = (t_rec){0, -1, -1, -1, -1, 0};
	while ((ret = fscanf(file, "%c %f %f %f %f %c \n", &rec.type, &rec.x, &rec.y, &rec.width, &rec.height, &rec.color)) > 0)
	{
		if (ret != 6 || !valid_dimension(rec))
		{
			printf("probleme dimnesion rectangle\n");
			free(matrix);
			matrix = NULL;
			fclose(file);
			return (1);
		}
		set_rectangle(matrix, zone, rec);

	
	}

	draw(matrix, zone);
	free(matrix);
	return (0);
	// printf("zone\nw=%d, h=%d col=%c\n", zone.width, zone.height, zone.color);
	// printf("scanf_ret = %d\n", ret);
	// printf("rec\ntype=%c x=%f y=%f w=%f h=%f col=%c\n", rec.type, rec.x, rec.y, rec.width, rec.height, rec.color);
	// printf("scanf_ret = %d\n", ret);
}
