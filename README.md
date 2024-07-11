# Redis Clone in C++

This repository contains a C++ implementation of a simple Redis-like key-value store. The implementation focuses on basic features of Redis, including hashtable-based storage, key-value operations, and progressive resizing for better performance.

## Features

- **Hashtable-based storage**: Efficient storage and retrieval using hashtables.
- **Key-value operations**: Support for basic commands like `GET`, `SET`, and `DEL`.
- **Progressive resizing**: Keys are progressively moved to a new hashtable during resizing to maintain low latency.
- **Collision handling**: Open addressing and chaining techniques for resolving collisions.
- **Non-blocking I/O**: Non-blocking socket operations for handling multiple clients simultaneously.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++11 (or later).
- Make (optional, for convenience).
- CMake (optional, for convenience).

### Building the Project

You can build the project using either `make` or `cmake`.

#### Using Make

1. Navigate to the project directory.
2. Run `make` to compile the source code.

```sh
make
```

#### Using CMake

1. Navigate to the project directory.
2. Create a build directory and navigate into it.

```sh
mkdir build
cd build
```

3. Run `cmake` to generate the build files, then compile the project.

```sh
cmake ..
make
```

### Running the Server

After building the project, you can run the server executable.

```sh
./server
```

The server will start and listen for connections on port `1234`.

## Key-Value Operations

The server supports the following basic key-value operations:

- **SET key value**: Set the value for a key.
- **GET key**: Get the value of a key.
- **DEL key**: Delete a key.

### Example Usage

You can interact with the server using a simple TCP client like `telnet`.

1. Start the server.
2. Open a new terminal and use `telnet` to connect to the server.

```sh
telnet localhost 1234
```

3. Use the following commands to interact with the server:

```
SET key1 value1
GET key1
DEL key1
```

## Implementation Details

### Progressive Resizing

The implementation uses a technique called progressive resizing to handle hashtable growth. Instead of moving all keys at once (which can cause significant latency), keys are moved incrementally during normal operations. This ensures that the server remains responsive even during resizing.

### Collision Handling

The hashtable uses open addressing and chaining to resolve collisions. When a collision occurs, the server will either probe for the next available slot (open addressing) or store the colliding keys in a linked list at the slot (chaining).

## Contributing

Contributions are welcome! If you find a bug or have a feature request, please open an issue. Pull requests are also appreciated.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgements

This project is inspired by the original [Redis](https://redis.io/) project.

---

Feel free to customize this README file to better suit your project's specifics and any additional features you may have implemented.
