#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BITS 12

int main(void)
{
    FILE *fp;
    unsigned int *data, *search, count, sc;
    unsigned int i, j, bit, mask, nv, n1, search_bit;
    unsigned int result = 1;
    char line[16];

    fp = fopen("./diagnostic_report.txt", "r");
    for(count = 0; fgets(line, sizeof(line), fp); count++);
    fseek(fp, 0, SEEK_SET);

    data = calloc(count, sizeof(unsigned int));
    search = calloc(count, sizeof(unsigned int));
    for(i = 0; i < count; data[i++] = strtol(fgets(line, sizeof(line), fp), NULL, 2));
    fclose(fp);

    memcpy(search, data, sizeof(unsigned int) * (sc = count));
    for(bit = mask = 0; bit < INPUT_BITS; bit++) {
        for(i = nv = n1 = 0; i < sc; i++) {
            if(search[i] & (1 << (INPUT_BITS - 1 - bit)))
                n1++;
            nv++;
        }

        search_bit = (nv - n1 <= n1) ? 1 : 0;
        for(i = j = 0; i < sc; i++) {
            if(((search[i] >> (INPUT_BITS - 1 - bit)) & 1) != search_bit)
                continue;
            search[j++] = search[i];
        }

        sc = j;
    }

    printf("O2GEN: %u\n", search[0]);
    result *= search[0];

    memcpy(search, data, sizeof(unsigned int) * (sc = count));
    for(bit = mask = 0; bit < INPUT_BITS; bit++) {
        for(i = nv = n1 = 0; i < sc; i++) {
            if(search[i] & (1 << (INPUT_BITS - 1 - bit)))
                n1++;
            nv++;
        }

        search_bit = (nv - n1 <= n1) ? 0 : 1;
        for(i = j = 0; i < sc; i++) {
            if(((search[i] >> (INPUT_BITS - 1 - bit)) & 1) != search_bit)
                continue;
            search[j++] = search[i];
        }

        sc = j;
    }

    printf("CO2SCRUB: %u\n", search[0]);
    result *= search[0];

    printf("RES: %u\n", result);

    free(search);
    free(data);

    return 0;
}