# Time-Delivery

A C-based command-line delivery management system developed as part of a systems programming project.

The application simulates a delivery scheduling process based on recipient coordinates, delivery priorities, daily delivery capacity and available fuel.

## Features

- Add delivery requests with unique IDs, coordinates and priority levels.
- Manage pending delivery requests using singly linked lists.
- Automatically organize delivery requests by coordinates.
- Calculate Euclidean distances between delivery locations.
- Prioritize urgent deliveries based on five priority levels.
- Simulate daily delivery capacity and fuel constraints.
- Select high-priority deliveries based on available capacity and route distance.
- Identify intermediate delivery locations along selected route segments.
- Automatically increase the priority of undelivered requests at the end of each day.
- Sort delivered request IDs in ascending order.
- Dynamically allocate and free memory for delivery records.

## Tech Stack

- **Programming Language:** C
- **Interface:** Command Line Interface (CLI)
- **Data Structures:** Singly Linked Lists, Structures, Pointers
- **Memory Management:** Dynamic Memory Allocation (`malloc`, `free`)
- **Algorithms:** Bubble Sort, Coordinate-Based Sorting, Priority-Based Selection
- **Mathematical Operations:** Euclidean Distance Calculation (`math.h`)
- **Input / Output:** Standard C Input and Output (`scanf`, `printf`)

## Implementation Details

### Delivery Management

Each delivery request contains:

- Unique delivery ID.
- X and Y coordinates.
- Delivery priority.
- Pointer to the next request in the linked list.

New requests are inserted into the linked list according to their coordinates.

### Priority Management

The application supports five delivery priority levels:

- `Very_Low`
- `Low`
- `Medium`
- `High`
- `Very_High`

Undelivered requests automatically increase their priority by one level at the end of each simulated day, until they reach the highest priority.

### Distance Calculation

The application calculates the Euclidean distance between delivery locations using their X and Y coordinates.

\[
d = \sqrt{(x_2-x_1)^2+(y_2-y_1)^2}
\]

These calculations are used to estimate route distances and determine whether selected deliveries can be completed within the available fuel budget.

### Daily Delivery Scheduling

The delivery process is simulated day by day.

- A configurable number of deliveries can be completed per day.
- A fuel allowance is added for each simulated day.
- The application checks the total route distance against the available fuel.
- When all pending deliveries cannot be completed, the system prioritizes requests marked as `Very_High`.
- Additional delivery locations positioned along selected route segments can also be included.
- Completed requests are removed from the linked list and their allocated memory is released.

### Sorting and Memory Management

- Delivery requests are organized by X and Y coordinates.
- Selected delivery requests are sorted by coordinates before processing.
- Delivered request IDs are sorted in ascending order.
- Dynamic memory allocation is used when creating new delivery records.
- Memory is released after successful delivery removal.

## Project Structure

```text
Time-Delivery/
│
├── README.md
└── Source.c
```

## Running Locally

### Requirements

- Windows
- GCC compiler (MinGW) or Visual Studio C compiler
- Command Prompt or terminal

### Compilation

Using GCC:

```bash
gcc Source.c -o Time-Delivery.exe -lm
```

### Execution

Run the compiled application:

```bash
Time-Delivery.exe
```

### Usage

1. Enter the maximum number of deliveries that can be completed per day.

2. Enter the number of new delivery requests for the current day.

3. For each delivery request, provide:
   - X coordinate.
   - Y coordinate.
   - Priority level (0–4).

4. The application processes delivery requests according to their priority, available capacity and fuel constraints.

5. At the end of each simulated day, the application displays:
   - Delivered request IDs.
   - Remaining fuel.
   - Number of completed deliveries.
   - Pending requests, when applicable.

6. Requests that remain pending automatically increase their priority before the next simulated day.

**Note:** The application uses in-memory data structures and does not implement file or database persistence. It is designed for execution in a Windows environment.

## Purpose

This academic project demonstrates practical knowledge of C programming, data structures, dynamic memory management, pointers, sorting algorithms, mathematical distance calculations and priority-based scheduling.

It also explores how resource constraints and delivery priorities can be used to simulate a simplified delivery management workflow.
