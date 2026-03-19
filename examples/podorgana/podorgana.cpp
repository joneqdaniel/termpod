#include <termpod/pod.hpp>

int main(int argc, char** argv)
{
	/* parse none file arguments */
	tr::pod::parse_args(argc, argv);
	/* for every file argument */
	while(optind < argc)
	{
		/* create and initialize pod file structure */
		tr::pod::file src(argv[optind++]);
		/* extract pod file struct */
		if(tr::pod::extract)
			for(size_t i = 0; i < src.entries.size(); i++)
				src[i].extract();
	}
	exit(EXIT_SUCCESS);
}

