#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* fuzz target entry point, works without libFuzzer */

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);

int main(int argc, char **argv)
{
    FILE *f;
    char *buf = nullptr;
    long siz_buf;

    if(argc < 2)
    {
        fprintf(stderr, "no input file\n");
        goto err;
    }

    f = fopen(argv[1], "rb");
    if(f == nullptr)
    {
        fprintf(stderr, "error opening input file %s\n", argv[1]);
        goto err;
    }

    fseek(f, 0, SEEK_END);

    siz_buf = ftell(f);
    rewind(f);

    if(siz_buf < 1) goto err;

    buf = (char*)malloc((size_t)siz_buf);
    if(buf == nullptr)
    {
        fprintf(stderr, "malloc() failed\n");
        goto err;
    }

    if(fread(buf, (size_t)siz_buf, 1, f) != 1)
    {
        fprintf(stderr, "fread() failed\n");
        goto err;
    }

    (void)LLVMFuzzerTestOneInput((uint8_t*)buf, (size_t)siz_buf);

err:
    free(buf);

    return 0;
}
