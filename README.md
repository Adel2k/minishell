# Minishell

![42 School](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/1024px-42_Logo.svg.png)

## Table of Contents

1. [About the Project](#about-the-project)
2. [Features](#features)
3. [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
4. [Usage](#usage)
5. [Examples](#examples)
6. [Contributing](#contributing)
7. [License](#license)
8. [Contact](#contact)

## About the Project

Minishell is a simple shell implementation project developed as part of the curriculum at 42 School. The project aims to deepen understanding of the workings of a shell by building one from scratch. This project is a partial implementation of a Unix shell and supports various essential features and commands.

## Features

- Basic shell command execution
- Built-in commands such as `cd`, `echo`, `exit`, etc.
- Redirection of input and output
- Pipe (`|`) support for chaining commands
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Environment variable management

## Getting Started

To get a local copy up and running, follow these steps.

### Prerequisites

You will need to have the following installed:

- GCC (GNU Compiler Collection)
- Make

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Adel2k/minishell.git

2. Build the project: 

    ```bash
    make
    # for linux
    make linux_minishell

3. Usage:

    ```bash
    ./minishell
