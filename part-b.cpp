// B: The Readers and Writers Problem
// Solution:
// Create a mutex for the resource to lock the resource for the using thread.
// The reading threads will try to lock the resoure to prevent to lock out
// the writer threads but the reader threads will not wait for the resource
// to be unlocked to reader. The writer thread shall wait for the resource
// to be unlocked before writing a random value in it.
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define COUNT 5

// Global variables
pthread_mutex_t mutex;
int resource = 0;
bool running = true;

// Function prototypes for the threads
void *reader_thread(void *ptr);
void *writer_thread(void *ptr);

// Main entry point of the program
int main()
{
    // Initial the variables
    pthread_mutex_init(&mutex, NULL);
    pthread_t readers[COUNT], writers[COUNT];

    // Make the threads
    for (int i = 0; i < COUNT; i++)
    {
        pthread_create(&writers[i], NULL, writer_thread, (void *)(long)i);
        pthread_create(&readers[i], NULL, reader_thread, (void *)(long)i);
    }

    // Run for 10 seconds
    sleep(10);

    // End the simulation
    running = false;

    // Wait for the child threads to exit before cleaning up
    for (int i = 0; i < COUNT; i++)
    {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

// Definition of the threads
void *reader_thread(void *ptr)
{
    int index = (int)(long)ptr;
    stringstream ss;

    while (running)
    {
        // Try to lock the mutex to prevent writing
        int res = pthread_mutex_trylock(&mutex);

        ss.str("");
        ss << "Reader " << index << " reads the value as " << resource << "." << endl;
        cout << ss.str();

        if (res == 0)
            pthread_mutex_unlock(&mutex);

        // Allow other threads to run
        pthread_yield();
    }

    return 0;
}

void *writer_thread(void *ptr)
{
    int index = (int)(long)ptr;
    stringstream ss;

    while (running)
    {
        // Try to lock the mutex to prevent writing
        if (pthread_mutex_trylock(&mutex) == 0)
        {
            resource = rand();
            ss.str("");
            ss << "Writer " << index << " writes the value of " << resource << "." << endl;
            cout << ss.str();
            pthread_mutex_unlock(&mutex);
        }

        // Allow other threads to run
        pthread_yield();
    }

    return 0;
}