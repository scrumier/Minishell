# Minishell

A minimal Unix shell written in C.

## What it does

Minishell is a simplified shell that can execute commands, handle pipes and redirections, manage environment variables, and respond to signals. It mimics the core behavior of bash.

## Features

- Execute commands from `PATH` or with absolute/relative paths
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variables: `$VAR`, `$?`
- Single and double quotes
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\`
- Command history

### Built-in commands

`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Usage

```sh
make
./minishell
```

The shell starts an interactive prompt. Type commands as you would in bash.

## Implementation

The shell is built in three stages: lexing (tokenizing the input), parsing (building a command tree), and execution (forking processes, setting up pipes and redirections).

This project was done in collaboration as a two-person team project at School 42.

## Project context

This is a School 42 project. The goal is to understand how a shell works internally, including process management with `fork` and `execve`, file descriptor manipulation, and parsing.