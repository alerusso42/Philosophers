intra: alerusso
github: alerusso42

# Philosophers
Part of the 42 common core curriculum, this C project teaches how concurrency works, both with threads (using mutex) and processes (using semapthores).

## Description

The goal is to simulate a system where multiple threads/processes (philosophers) must share limited resources (forks) without encountering deadlocks or data races.

### Libraries
 - pthread (POSIX Threads)
 - sys/time.h
 - stdio.h
 - stdlib.h
 - unistd.h
 
### The problem 

 N Philosophers sit at a round table with a bowl of spaghetti in the center. A single fork is placed between each pair of adjacent philosophers.
 
                _____________________
                |        🍴🧔🏼        |
                |🍴 🧔🏼        🍴 🧔🏼  |
                |        🍴 🧔🏼       |
                ______________________

To eat, a philosopher must pick up two forks (the one on their left and the one on their right).After eating, they put down both forks and start sleeping.Once they finish sleeping, they start thinking until they become hungry again.

If a philosopher does not start eating within ${time_to_die} milliseconds since the beginning of their last meal (or the start of the simulation), they die, and the simulation ends.
 
 ### synchronization issues

 #### deadlocks

 Deadlocks happens when two or more philosophers take their left fork
 simultaneously, waiting for a right fork that will never be released.

                 _____________________
                |        🍴🧔🏼        |
                |                    |
                |        🍴🧔🏼        |
                ______________________

In this picture, the two philosopher will hang forever.

#### data races

Data races happens when two or more philosophers access the same resource
simultaneously. This can lead to undefined behaviour.

                 _____________________
                |        🍴🧔🏼 🍴      |
                |                     |
                |        🍴🧔🏼 🍴      |
                _______________________

Consider a variable x, that stores the integer 42.
🧔🏼0 writes to x: it increases it by 8.
🧔🏼1 reads to x, and prints its value to the terminal.

There are two outcomes:
1) 🧔🏼0 comes first: "50" is displayed on the terminal.
2) 🧔🏼1 comes first: "42" is displayed on the terminal.

In computer system, this is randomness is unaccetable.
This is why mutexes are used: they lock a resource while
another thread is using it.
These mutexes are represented by the forks.

#### semaphores

In a multiprocess system, mutex cannot prevents data races: they work
in the process context.
semaphores are system abstraction, given by the semaphore.h library.
they prevents data races like mutexes, but they work both with threads and
processes.


## How to run

⚠️ time is in milliseconds!

### thread simulation with mutex and threads

cd philo
make
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

### thread simulation with semaphores and processes

cd philo_bonus
make
./philo_bonus [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]