# Brainfuck Compiler & Interpreter written in C++

Interpreter reads the brainfuck program and executes it directly against a 30,000-cell tape
Compiler translates the brainfuck file into an equivalent C program


## Building

```sh
g++ brainfuck_INT.cpp -o bf
g++ brainfuck_COMP.cpp -o bfc
```

## Usage

**Interpreter:**
```sh
./bf program.bf
```

**Compiler:**
```sh
./bfc program.bf      # generates out.c
gcc out.c -o out
./out
```
