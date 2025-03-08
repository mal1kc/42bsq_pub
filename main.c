#include <bsq.h>

int main(int argc,char *argv[])
{
	char *read_file_name;
	int arg_counter;
	bsq_map_d bsq_data;

	arg_counter = 0;
	if(argc == 1)
	{
		*read_file_name = "STDIN";
	}

	while(arg_counter < argc)
	{
		clear_map_struct(&bsq_map_d);
		*read_file_name = argv[arg_counter];
		bsq_map_d.file_name = read_file_name;
		read_map_data(&bsq_map_d);
		process_map(&bsq_map_d);
	}
	return 0;
}
