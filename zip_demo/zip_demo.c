#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "minizip/zip.h"
#include "minizip/unzip.h"

#define BLOCK_SIZE 256

void compress_files(const char *zip_file, const char *files[], int file_count);
void decompress_files(const char *zip_file, const char *output_dir);

int main()
{
    const char *zip_file ="compress.zip";
    const char *output_dir = "/home/xukk/clang/zip_demo/output_dir";

    char *files[] = {"scotty.txt",
                     "article.md",
                     "decompress.txt"};
    int file_count = 3; // 手动计数

    compress_files(zip_file, files, file_count);
    printf("files compressed successfully!\n");

    decompress_files(zip_file, output_dir);
    printf("zip file decompressed successfully!\n");
    return 0;
}

void compress_files(const char *zip_file, const char *files[], int file_count)
{
    zipFile zf = zipOpen(zip_file, APPEND_STATUS_CREATE);
    if (!zf) {
        fprintf(stderr, "error creating zip file.\n");
        exit(1);
    }

    for (int i = 0; i < file_count; i++) {
        zip_fileinfo zfi = {0};

        if (zipOpenNewFileInZip(zf, files[i], &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION) != ZIP_OK) {
            fprintf(stderr, "error adding file to zip:  %s.\n", files[i]);
            exit(1);
        }

        FILE *fp = fopen(files[i], "rb");
        if (!fp) {
            fprintf(stderr, "error opening file for reading: %s.\n", files[i]);
            exit(1);
        }

        char buffer[BLOCK_SIZE];
        int bytes_read;

        while ((bytes_read = fread(buffer, 1, BLOCK_SIZE, fp)) > 0) {
            if (zipWriteInFileInZip(zf, buffer, bytes_read) != ZIP_OK) {
                fprintf(stderr, "error writing data to zip: %s.\n", files[i]);
                exit(1);
            }
        }
        fclose(fp);

        if (zipCloseFileInZip(zf) != ZIP_OK) {
            fprintf(stderr, "error closing file in zip: %s.\n", files[i]);
            exit(1);
        }
    }
    zipClose(zf, NULL);
}

void decompress_files(const char *zip_file, const char *output_dir)
{
    unzFile uf = unzOpen(zip_file);
    if (!uf) {
        fprintf(stderr, "error opening zip file for decompression: %s.\n", zip_file);
        exit(1);
    }

    if (unzGoToFirstFile(uf) != UNZ_OK) {
        fprintf(stderr, "error going to first file in zip: %s.\n", zip_file);
        exit(1);
    }

    char output_file[BLOCK_SIZE];
    char buffer[BLOCK_SIZE];
    int err = UNZ_OK;
    unz_file_info file_info;

    do {
        if (unzGetCurrentFileInfo(uf, &file_info, output_file, sizeof(output_file), NULL, 0, NULL, 0) != UNZ_OK) {
            fprintf(stderr, "Error getting current file info.\n");
            exit(1);
        }
        char full_output_path[BLOCK_SIZE];
        snprintf(full_output_path, sizeof(full_output_path), "%s/%s", output_dir, output_file);

        if (unzOpenCurrentFile(uf) != UNZ_OK) {
            fprintf(stderr, "error opening current file for extraction: %s.\n", zip_file);
            exit(1);
        }

        FILE *fp = fopen(full_output_path, "wb");
        if (!fp) {
            fprintf(stderr, "error opening output_file for writing: %s.\n", full_output_path);
            exit(1);
        }

        int bytes_read;
        while ((bytes_read = unzReadCurrentFile(uf, buffer, BLOCK_SIZE)) > 0) {
            fwrite(buffer, 1, bytes_read, fp);
        }

        fclose(fp);

        if (unzCloseCurrentFile(uf) != UNZ_OK) {
            fprintf(stderr, "error closing current file after extraction: %s.\n", output_file);
            exit(1);
        }

        err = unzGoToNextFile(uf);
    } while (err == UNZ_OK);

    if (err != UNZ_END_OF_LIST_OF_FILE) {
        fprintf(stderr, "error going to next file in zip: %s.\n", zip_file);
        exit(1);
    }

    unzClose(uf);
}