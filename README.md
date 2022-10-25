# CSE 5700(Compilers) Lab 2

A recursive decent parser that parses the given grammar in C.

### Terminals:

    a, b, c, d

### Given grammar:

    S -> aAB
    A -> Abc | b
    B -> d

### Grammar w/o left recursion:

    S -> aAB
    A -> bA'
    A' -> bcA'
        | ε
    B -> d

## Installation

Using the GNU compiler execute the following commands.

```bash
g++ main.c -o main
make main
```

## Usage

After creating your main exectuable, simply run the program with the following command.

```bash
./main
```

You can now parse any word in the language.

```
> abd
(S a(A b)(B d))
> abbcd
(S a(A b(A' bc))(B d))
```

Any word that is not valid will yield an error message.
