#include "trove.h"

void printUsage(char *progname) {
    fprintf(stderr, "Usage: %s -f <filename> | -l <length> | [ -b | -r | -u ]\n", progname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int opt;
    int bFlag = 0;
    int fFlag = 0;
    int lFlag = 0;
    int rFlag = 0;
    int uFlag = 0;
    int limitFlag = 0;
    char *progName = argv[0];
    while ((opt = getopt(argc, argv, ":bf:l:ru")) != -1) {
        switch (opt) {
            case 'b':
                // flag: "-b" (build new trovefile from contents in filelist)
                if (limitFlag) {
                    printUsage(progName);
                }
                bFlag++;
                limitFlag++;
                printf("option selected: -b\n");
                break;
            case 'f':
                // flag: "-f trovefile" (name of trovefile to be built or searched)
                if (fFlag) {
                    printUsage(progName);
                }
                fFlag++;
                // trovePath = optarg;
                // printf("option selected: -f %s\n", trovePath);
                break;
            case 'l':
                // flag: "-l length" (only words with provided length are added to trovefile)
                if (lFlag) {
                    printUsage(progName);
                }
                lFlag++;
                // minLength = atoi(optarg);
                // printf("option selected: -l %d\n", minLength);
                break;
            case 'r':
                // flag: "-r" (if any files from filelist appear in the trovefile, remove them)
                if (limitFlag) {
                    printUsage(progName);
                }
                rFlag++;
                limitFlag++;
                printf("option selected: -r\n");
                break;
            case 'u':
                // flag: "-u" (update the trovefile with contents of all files in the filelist)
                if (limitFlag) {
                    printUsage(progName);
                }
                uFlag++;
                limitFlag++;
                printf("option selected: -u\n");
                break;
            case '?':
                fprintf(stderr, "%s: unknown option [%c]\n", progName, optopt);
                exit(EXIT_FAILURE);
            case ':':
                fprintf(stderr, "%s: [%c] requires an argument\n", progName, optopt);
                exit(EXIT_FAILURE);
        }
    }
    if (optind < argc) {
        while (optind < argc) {
            if (bFlag) {
                char *pathName = argv[optind];
                findfiles(pathName);
            } else {
                // non option arg is a word
            }
            optind++;
        }
    }
    exit(EXIT_SUCCESS);
    return(0);
}