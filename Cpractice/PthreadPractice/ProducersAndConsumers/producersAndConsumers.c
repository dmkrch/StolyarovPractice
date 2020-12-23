#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

#define BUFFER_SIZE 4096

/* buffer of exchange between producers and consumers */
struct buf_str 
{
    int count;
    double values[BUFFER_SIZE];
} buffer;

void init_buffer()
{
    buffer.count = 0;
}

void put_buffer_item(double v)
{
    buffer.values[buffer.count] = v;
    buffer.count++;
}

double get_buffer_item()
{
    buffer.count--;
    return buffer.values[buffer.count];
}


/* semaphores and mutex for working with buffer */
sem_t buf_empty;
sem_t buf_full;
pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;


/* variables for summing and mutex for protection */
double grand_total = 0;
long grand_count = 0;
pthread_mutex_t grand_mutex = PTHREAD_MUTEX_INITIALIZER;


/* semaphore for counting remaining producers */
sem_t producers_count;


/* thread for reading data (producer) */
void* producer_thread(void* v)
{
    /* getting pointer to name of source in variable 'v' */
    double val;
    FILE *f = fopen((char*)v, "r");
    if(!f)
    {
        perror((char*)v);
        sem_wait(&producers_count);
        return NULL;
    }
    
    while(!feof(f))
    {
        if(1 != fscanf(f, "%lf", &val))
            continue;
        
        sem_wait(&buf_empty);   /* producer's algorithm */
        pthread_mutex_lock(&buf_mutex);

        put_buffer_item(val);

        pthread_mutex_unlock(&buf_mutex);
        sem_post(&buf_full);    /* ---------- */
    }

    sem_wait(&producers_count);
    return NULL;
}


/* thread-consumer. It takes values from buffer and makes calculations
 Ignores input paramater value */
 
void *consumer_thread(void* ignored)
{
    double local_total = 0;     /* local addder */
    long local_count = 0;
    for(;;)
    {
        double val;
        sem_wait(&buf_full);          /* checking if there are any items in buffer */
        pthread_mutex_lock(&buf_mutex);

        val = get_buffer_item();

        pthread_mutex_unlock(&buf_mutex);
        sem_post(&buf_empty);         /* raising empty slots of var 'buf_empty' */

        /* now we can get down to computing */
        local_total += log(val); local_count++;

        /* if it's possible - reset data */
        if(0 == pthread_mutex_trylock(&grand_mutex))
        {
            grand_total += local_total;
            grand_count += local_count;
            local_total = 0; local_count = 0;
            pthread_mutex_unlock(&grand_mutex);
        }
    }
}


int main(int argc, char **argv)
{
    pthread_t thr;
    int i;
    /* initializing gloval variables */
    init_buffer();
    sem_init(&buf_empty, 0, BUFFER_SIZE);
    sem_init(&buf_full, 0, 0);
    sem_init(&producers_count, 0, 0);

    /* turning on producers */
    for(i = 1; i < argc; i++)
    {
        sem_post(&producers_count);
        pthread_create(&thr, NULL, producer_thread, argv[i]);
    }

    /* turning on consumers */
    for(i = 0; i < 10; ++i)
        pthread_create(&thr, NULL, consumer_thread, NULL);;

    /* now we print and refresh result every 5 seconds */
    for(;;)
    {
        int p_c;
        sleep(5);
        pthread_mutex_lock(&grand_mutex);

        /* we must ensure that we dont divide by 0 */
        if(grand_count > 0)
        {
            printf("total average: %f (sum = %f; count = %ld)\n",
                    grand_total / ((double)grand_count), 
                    grand_total, grand_count);
        }
        else
        {
            printf("No data yet...\n");
        }

        grand_total = 0; grand_count = 0;
        pthread_mutex_unlock(&grand_mutex);
        sem_getvalue(&producers_count, &p_c);
        if(p_c == 0)
        {
            printf("No more producers\n");
            break;
        }
    }

    return 0;
}