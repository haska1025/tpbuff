#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void usage()
{
    fprintf(stderr, "Usage: tpp [option] TPP_FILES\n");
    fprintf(stderr, "  --help -h             help information\n");
    fprintf(stderr, "  --cppout=DIR          Generate cplusplus code, The DIR is used to save files.\n");
    fprintf(stderr, "  --javaout=DIR         Generate java code, The DIR is used to save files.\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    // tpp [option] TPP_FILES
    // --cppout <dir> 
    // --javaout <dir>

    int c;
    // 1: cpp, 2: java
    int generate_mode=0;
    char *cpp_dir, *java_dir;

    cpp_dir = java_dir = NULL;
    if (argc < 2){
        usage();
        return 0;
    }

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",  no_argument,       0,  'h' },
            {"cppout",  required_argument, 0,  1 },
            {"javaout", required_argument, 0,  2 },
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "h", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'h':
                usage();
                break;
            case 1:
                cpp_dir = optarg;
                generate_mode = 1;
                break;
            case 2:
                java_dir = optarg;
                generate_mode = 2;
                break;
            default:
                usage();
        }
    }

    if (optind < argc) {
        while (optind < argc){
            if (generate_mode == 1){
                // cpp
                tp_gen_cxx_code(cpp_dir, argv[optind++]);
            }else if (generate_mode == 2){
                // java
            }
        }
    }

    return 0;
}

