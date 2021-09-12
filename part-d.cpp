// D: The Sleeping Barbers Problem
// Solution:
// We will create a thread for each barber and one thread for arriving customers.
// For each barber, we will create a mutex that will lock if it is currently serving
// a customer. If its unlock, its ready to accept a new customer. A condition variable
// is used to signal the barbers that a customer has arrived. The barber will wait for
// the condition before it awakes to serve the customer.
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

using namespace std;

#define BARBERS 5

bool running = true;
int customer_index = 0;
pthread_mutex_t barbers[BARBERS];
pthread_cond_t customer_arrived;

// Function prototype for the threads.
void *customer_thread(void *ptr);
void *barber_thread(void *ptr);

// Function to sleep for specified milliseconds.
void msleep(int msec);

// Main entry point of the program
int main()
{
    pthread_t barber_threads[BARBERS], customer_threadt;

    // Initialize cond and mutex variables
    for (int i = 0; i < BARBERS; i++)
        pthread_mutex_init(&barbers[i], NULL);

    pthread_cond_init(&customer_arrived, NULL);

    // Create the threads
    pthread_create(&customer_threadt, NULL, customer_thread, NULL);
    for (int i = 0; i < BARBERS; i++)
    {
        pthread_create(&barber_threads[i], NULL, barber_thread, (void *)(long)i);
    }

    // Run for 10 seconds
    sleep(10);

    // End the simulation
    running = false;

    // Send signals to all threads to stop
    for (int i = 0; i < BARBERS; i++)
        pthread_cond_signal(&customer_arrived);

    // Wait for the child threads to exit before cleaning up
    pthread_join(customer_threadt, NULL);
    for (int i = 0; i < BARBERS; i++)
    {
        pthread_join(barber_threads[i], NULL);
    }

    // Destroy cond and mutex variables
    for (int i = 0; i < BARBERS; i++)
        pthread_mutex_destroy(&barbers[i]);
        
    pthread_cond_destroy(&customer_arrived);

    return 0;
}

// Definition of the threads
void *customer_thread(void *ptr)
{
    while (running)
    {
        // Wait for a customer to arrive
        msleep(rand() % 1000);

        // Pick an empty 
        for (int i = 0; i < BARBERS; i++)
        {
            // This slot is available
            if (pthread_mutex_trylock(&barbers[i]) == 0)
            {
                pthread_mutex_unlock(&barbers[i]);
                customer_index++;
                cout << "Customer " << customer_index << " arrives." << endl;
                pthread_cond_signal(&customer_arrived);
                break;
            }
        }

        // Yield to other process
        pthread_yield();
    }

    return 0;
}

void * barber_thread(void * ptr)
{
    int index = (int)(long)ptr;

    while (running)
    {
        // Wait for a customer to arrive
        pthread_cond_wait(&customer_arrived, &barbers[index]);

        if (!running)
            break;

        // Wake up the barber and serve customer
        cout << "Barber " << index << " is awake and serving customer ";
        cout << customer_index << "." << endl;
        
        // Yield while serving this customer
        msleep(rand() % 3000);

        // The barber sleeps
        cout << "Barber " << index << " is asleep." << endl;
        pthread_mutex_unlock(&barbers[index]);
        pthread_yield();
    }

    return 0;
}

// Definition of msleep function
void msleep(int msec)
{
    struct timespec ts;
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}