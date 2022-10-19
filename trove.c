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
                if (limitFlag) {
                    printUsage(progName);
                }
                bFlag++;
                limitFlag++;
                break;
            case 'f':
                if (fFlag) {
                    printUsage(progName);
                }
                fFlag++;
                trovePath = optarg;
                break;
            case 'l':
                if (lFlag) {
                    printUsage(progName);
                }
                lFlag++;
                minLength = atoi(optarg);
                break;
            case 'r':
                if (limitFlag) {
                    printUsage(progName);
                }
                rFlag++;
                limitFlag++;
                break;
            case 'u':
                if (limitFlag) {
                    printUsage(progName);
                }
                uFlag++;
                limitFlag++;
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
            if (limitFlag) {
                if (bFlag) {
                    char *pathName = argv[optind];
                    build(pathName);
                } else if (rFlag) {
                    // remove
                } else if (uFlag) {
                    // update
                }
            } else {
                // non option arg is a word
                // search trovefile
            }
            optind++;
        }
    }
    exit(EXIT_SUCCESS);
    return(0);
}