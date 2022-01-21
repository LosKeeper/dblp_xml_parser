#ifndef COMPARE_H
#define COMPARE_H

/**
 * @brief Compare 2 files and print on stderr
 *
 * @param file1 first file to compare
 * @param file2 second file to compare
 *
 * @return 0 if files are the same and 1 if files are differents
 */
int compareFile(char *file1, char *file2);

#endif