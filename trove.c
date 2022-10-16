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
    char *progName = argv[0];
    while ((opt = getopt(argc, argv, ":bf:l:ru")) != -1) {
        switch (opt) {
            case 'b':
                // flag: "-b" (build new trovefile from contents in filelist)
                if (bFlag) {
                    printUsage(progName);
                }
                bFlag++;
                rFlag++;
                uFlag++;
                printf("option selected: -b\n");
                break;
            case 'f':
                // flag: "-f trovefile" (name of trovefile to be built or searched)
                if (fFlag) {
                    printUsage(progName);
                }
                fFlag++;
                printf("option selected: -f %s\n", optarg);
                // trovePath = optarg;
                break;
            case 'l':
                // flag: "-l length" (only words with provided length are added to trovefile)
                if (lFlag) {
                    printUsage(progName);
                }
                lFlag++;
                printf("option selected: -l %s\n", optarg);
                // minLength = atoi(optarg);
                break;
            case 'r':
                // flag: "-r" (if any files from filelist appear in the trovefile, remove them)
                if (rFlag) {
                    printUsage(progName);
                }
                rFlag++;
                bFlag++;
                uFlag++;
                printf("option selected: -r\n");
                break;
            case 'u':
                // flag: "-u" (update the trovefile with contents of all files in the filelist)
                if (uFlag) {
                    printUsage(progName);
                }
                uFlag++;
                bFlag++;
                rFlag++;
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
                // non option args are the file list
                char *pathName = argv[optind];
                findfiles(pathName);
            } else {
                // non option arg is a word
            }
            // printf("%s\n", argv[optind++]);
            optind++;
        }
    }
    // printf("Given pathname: %s\n", trovePath);
    // printf("Minimum Length: %d\n", minLength);
    exit(EXIT_SUCCESS);
    return(0);
}