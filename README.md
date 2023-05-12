# Philosopher's Dinner

This repository contains an implementation of the Dining Philosophers problem in C. The Dining Philosophers problem is a classic synchronization problem in computer science, where a group of philosophers sit around a table and alternate between thinking and eating. However, there are only a limited number of forks available for them to use, and they must avoid deadlock and starvation.

## Implementation

The main program is `philosophers_dinner.c`, which implements the solution to the Dining Philosophers problem. It uses a monitor-based approach with mutex locks and condition variables to ensure safe resource sharing and prevent deadlocks.

## Usage

To compile and run the program, follow these steps:

1. Make sure you have a C compiler installed on your system (e.g., GCC).

2. Clone this repository to your local machine.

3. Navigate to the cloned repository's directory.

4. Open a terminal and run the following command to compile the program:

   ```bash
   make exec
   ```

## Customization
You can customize the program by modifying the constants defined at the top of `philosophers_dinner.c`. For example, you can change the number of philosophers (`NUM_FILOSOFOS`) or adjust the sleep intervals for thinking and eating.

## License
This project is licensed under the MIT License. Feel free to use and modify it according to your needs.