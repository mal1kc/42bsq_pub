#include "bsq.h"
#include <unistd.h>
#include <fcntl.h>

void ft_reset_mapData(bsq_map_d *mapData)
{
	int i;

	if (mapData->map_data != NULL)
	{
		i = 0;
		while (i < mapData->line_len)
			free(mapData->map_data[i++]);
		free(mapData->map_data);
		mapData->map_data = NULL;		
	}
	
	mapData->col_len = -1;
	mapData->line_len = -1;
	mapData->file_name = "";
	mapData->space = '\0';
	mapData->obstacle = '\0';
	mapData->full = '\0';
	mapData->map_data = NULL;		
}

int	ft_check_first_line(bsq_map_d *mapData, char *first_line)
{
	/* Kontrol edilmesi gerekenler:
	--- karakter eksikse
	--- iki karakter birbiriyle aynıysa
	--- sıkıntı yoksa mapData içerisine bilgiler yazılmalı
	*/

	int	i;
	int	j;
	int line_len;

	line_len = 0;
	while (*first_line >= '0' && *first_line <= '9')
	{
		line_len *= 10;
		line_len += *first_line - '0';
		first_line++;
	}
	if (line_len <= 0)
		return (0);

	i = 0;
	while (first_line[i])
	{
		j = 0;
		while (first_line[j])
		{
			if (first_line[i] == first_line[j] && i != j)
				return (0);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (0);

	mapData->line_len = line_len;
	mapData->space = first_line[0];
	mapData->obstacle = first_line[1];
	mapData->full = first_line[2];

	return (1);
}

int	ft_read_map(bsq_map_d *mapData, int fd)
{
	/* Yapılması gerekenler:
	--- ilk 4 karakterde hata olup olmadığına bakmak ve onları mapData'ya 
	eklemek
	--- col sayısını bulmak
	--- mapData içindeki map_data içerisine malloc ile dizileri oluşturup 
	bilgileri içerisine girmek gerekiyor
	*/
	int bytes_read;
	char buffer[100];
	int i;
	int line_size;

	bytes_read = read(fd, buffer, 4);
	buffer[bytes_read] = '\0';
	if (ft_check_first_line(mapData, buffer) == 0)
		return (0);

	line_size = -1;
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';

	}
}

int	main(int argc, char **argv)
{
	/* Genel aşamalar:
	--- Harita bilgileri mapData içerisine kaydedilmesi lazım
		--- Haritadaki .ox karakterlerin sayı olması engellenmesi gerekiyor 
	--- Haritadaki boş yerler 0,1 gibi sayılarla doldurulması lazım
	--- Haritadaki en büyük karenin konumu bulunması lazım
	--- Haritadaki en büyük karenin oluduğu kısım full ile geri kalan
	kısımlardaki sayılar space ile engeller ise opstacle ile doldurulması lazım
	--- Oluşturulan sonuç ekrana yazdırılması lazım
	*/
	bsq_map_d mapData;
	int	fd;
	int i;

	i = 1;
	while (i < argc)
	{
		ft_reset_mapData(&mapData);
		if (argc > 1)
		{
			// dosya okuma işlemleri
			mapData.file_name = argv[1];
			fd = open(argv[1], O_RDONLY);
			if (fd == -1)
			{
				// Dosya açılamadı
				ft_puterr("map error\n");
				i++;
				continue ;
			}
		} else
		{
			// standart çıktı okuma işlemleri
			mapData.file_name = "STDIN";
			fd = STDIN_FILENO;
		}
		if (ft_read_map(&mapData, fd) == 0)
		{
			ft_puterr("map error\n");
			i++;
			continue ;
		}
		i++;
	}
	return 0;
}