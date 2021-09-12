PROBLEM DESCRIPTION

B: The Readers and Writers Problem
Consider a single resource which has multiple threads which need to read from or write to that resource. We can only
allow a single writer to write data to that resource. However, it is fine to have multiple readers reading at the same
time, but no writer is allowed to write while there are readers reading.
Have a single resource (an integer is fine) with 5 reader threads and 5 writer threads. The rules for access to the
resource must be as outlined above. Provide sufficient output so it is clear the decisions that are made by your
program. As with other implementations, kill it off after ten seconds and your program should exit gracefully with no
race conditions or deadlocks.

D: The Sleeping Barbers Problem
In this problem, have an array of 5 slots. Have a barber thread that is the one that will be servicing the other threads.
Use a condition variable to send the barber to sleep until a customer arrives.
At random time intervals (in milliseconds), a customer will enter. If there is a seat available, they will take up that seat
and if there is no space, it will leave. When a customer arrives, and the barber is asleep it should be woken up (via the
condition variable).
Once the barber is awake, it will serve each customer, in order. Serving a customer in this case can be simulated by
sleeping for a random number of milliseconds. Once a customer has been serviced, they should be removed from the
array to make space for another customer and the barber will move on to the next customer available. When there are
no customers left to be served, the barber should go back to sleep until a new customer arrives.
CR: Have more than 1 seat (say, 4 seats) in the waiting room).
DI: Have more than 1 barber, customers check for full waiting rooms.
HD: Make it fair. Ensure all barbers get an equal amount of work for a given (large) set of customers

Building:
Run 'make part-b' to build part B of the problem.
Run 'make part-d' to build part D of the problem. 
Both options provide a simulation executable. You need to rebuild if you want to run the other part.

Running:
Run './simulation' to execute each part.

Testing:
out-b.txt and out-d.txt are sample outputs of the program.