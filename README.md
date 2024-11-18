# Philosopher Project

## Overview

The **Philosopher Project** simulates the classic dining philosophers' problem, where philosophers alternate between
eating, thinking, and sleeping. This project focuses on the importance of understanding **threads** and **mutexes** to prevent **data races**
and ensure a synchronized and efficient solution. It is a practical exercise in concurrency and synchronization in C programming.

---

## Features

1. **Thread-Based Implementation**:
   - Each philosopher is represented as a thread.
   - Threads handle simultaneous operations, showcasing the challenges of concurrent programming.

2. **Forks and Mutexes**:
   - Each fork is represented by a mutex, preventing multiple philosophers from using the same fork simultaneously.
   - Proper use of mutexes ensures no **data races** occur.

3. **Simulation Rules**:
   - Philosophers alternate between eating, thinking, and sleeping.
   - A philosopher must hold two forks (left and right) to eat.
   - The simulation stops when a philosopher dies of starvation or when all philosophers have eaten a specified number of times.

4. **Logging**:
   - All philosopher state changes are logged with timestamps for debugging and validation.
   - State messages include:
     - Taking a fork
     - Eating
     - Sleeping
     - Thinking
     - Dying (with a delay of no more than 10 ms from the actual death)

---

## Requirements

### General
- The project must be written in **C** and follow the **Norm**.
- All memory must be freed properly, and no memory leaks are allowed.
- The program must avoid crashes (e.g., segmentation faults, double frees).
- A `Makefile` must compile the project with flags `-Wall -Wextra -Werror` and include rules for `NAME`, `all`, `clean`, `fclean`, and `re`.

## Program Arguments
The program takes the following arguments:

1. `number_of_philosophers`: The number of philosophers and forks at the table.
2. `time_to_die` (in milliseconds): If a philosopher does not start eating within `time_to_die` milliseconds since their last meal or the start of the simulation, they die.
3. `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During this time, they must hold two forks.
4. `time_to_sleep` (in milliseconds): The time a philosopher spends sleeping.
5. `[number_of_times_each_philosopher_must_eat]` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times.
		If not specified, the simulation stops when a philosopher dies.

## Philosopher Behavior
- Philosophers alternate between eating, thinking, and sleeping.
- A philosopher requires two forks (one on the left and one on the right) to eat.
- After eating, they return the forks and begin sleeping.
- Once awake, they resume thinking.
- The simulation stops when a philosopher dies from starvation.

## Simulation Rules
- Each philosopher is represented by a thread.
- Fork states are protected using mutexes to prevent duplication and ensure thread safety.
- Global variables are forbidden.
- Logs must be formatted as follows:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
  - Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.

## Bonus Part
The bonus part introduces the following changes:
- Philosophers are represented as processes instead of threads.
- Forks are managed using a semaphore to represent the number of available forks.
- The main process oversees the philosophers but is not a philosopher itself.

Note: The bonus part will only be evaluated if the mandatory part is completed perfectly.

---

## Thank You!

Thank you for checking out the **Philosopher** project! I hope you found it insightful and helpful for understanding thread management and the importance of mutexes in preventing data races.

If you enjoyed this project or found it useful, please consider leaving a ⭐ on the repository—it means a lot and helps others discover this work.

Happy coding, and may your journey through programming always be fun and rewarding! 😊