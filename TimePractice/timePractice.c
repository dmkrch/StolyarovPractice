#include <time.h>
#include <stdio.h>

int main(void)
{
    struct tm *local, *gm;
    time_t t;
    t = time(NULL);             // in t - amount of second from 1970

    local = localtime(&t);      // initialises struct local with pc time
    printf("Local time and date: %s", asctime(local));
    printf("%d   %d   %d   %d   %d   %d", local->tm_wday, local->tm_year,
            local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);

    gm = gmtime(&t);            // initialises gm with time accord. Grinvich
    printf("Greenwich mean time and date: %s", asctime(gm));

    return 0;
}
