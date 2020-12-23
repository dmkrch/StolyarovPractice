#include <stdio.h>

void string50(FILE *f1, FILE *f2)
{
    char buf[51];
    while (fgets(buf, sizeof(buf), f1))
    {
        int i;
        int nlpos = -1;
        for (i = 0; i < sizeof(buf) && buf[i]; i++)
            if (buf[i] == '\n')
            {
                nlpos = i;
                break;
            }
        if (nlpos == -1)
        {
            int c;
            fputc('\n', f2);
            while((c = fgetc(f1)) != EOF && c != '\n');
        }
        else
        {
            buf[nlpos] = '\0';
            fprintf(f2, "[%s]\n", buf);
        }
    }
}

int main()
{
    FILE* file1;
    FILE* file2;

    file1 = fopen("first.txt", "r");
    file2 = fopen("second.txt", "w");

    string50(file1, file2);

    return 0;
}
