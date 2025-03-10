/* Yapılması gerekenler:
1- Dosyanın açılması lazım
	- Dosya açılmama durumunda ve diğer hata durumlarında hata mesajı
	- Diğer bütün ana fonksiyonların yönetimi
2- İlk satır bilgilerinin alınması lazım
	- Eğer iki tane karakter aynıysa hata!
	- Eğer karakter sayısı eksikse hata
	- Karakterler basılabilir karakter mi kontrolü
	- Eğer haritada sorun varsa map error ve sonraki harita
3- İçeriklerin okunup, sayılar yazılması, bigest bulunması lazım
	- Dosyanın tekrardan açılması lazım
	- satır uzunluklarının eşitliğinin kontrolü
	- haritanın sadece .ox'lerden oluştuğunun kontrolü
	- Eğer haritada sorun varsa map error ve sonraki harita
4- Sonuç ekrana yazdırılması lazım

Dosyalar:
main.c:
	main(),
	ft_open_file(),
	ft_soliton()
ft_extra_func.c:
	ft_reset_map_info(), 
	ft_reset_biggest_info(), 
	ft_puterr_and_return();
ft_reading_first_line.c:
debug.c:
	ft_print_biggest_info()

*/

#include "ft.h"

int	ft_open_file(t_bsq_map_data *map_info)
{
	int	fd;
	int is_stdin;
	char *file_name;

	is_stdin = map_info->is_stdin;
	file_name = map_info->file_name;
	if (is_stdin)
		fd = STDIN_FILENO;
	else
		fd = open(file_name, O_RDONLY);

	return (fd);
}

void	ft_soliton(t_bsq_map_data *map_info, t_biggest_sq *biggest_info,
	char *file_name, t_bool is_stdin)
{
	int fd;

	map_info->map_data = NULL;
	ft_reset_map_info(map_info);
	ft_reset_biggest_info(biggest_info);
	map_info->file_name = file_name;
	map_info->is_stdin = is_stdin;
	fd = ft_open_file(map_info);
	if (fd == -1)
	{
		ft_puterr_and_return(MAP_ERROR_TEXT);
		return ;
	}
	else
	{
		if (ft_read_first_line(map_info, fd))
			ft_read_map(map_info, biggest_info);
		// if (ft_read_first_line(map_info, fd))
		// 	if (ft_read_map(map_info, biggest_info))
		// 		if (ft_print_sol(map_info, biggest_info))
					// ; // Hiçbir şey yapma

		ft_print_map_info(map_info, biggest_info);
		close(fd);
	}

}

int main(int argc, char **argv) {
	t_bsq_map_data	map_info;
	t_biggest_sq		biggest_info;
    int				i;

	if (argc == 1)
	{
		ft_soliton(&map_info, &biggest_info, "STDIN", true);
    }
	else
	{
        i = 1;
        while (i < argc)
        {
			ft_soliton(&map_info, &biggest_info, argv[i], false);
            i++;
        }
    }
    return (0);
}