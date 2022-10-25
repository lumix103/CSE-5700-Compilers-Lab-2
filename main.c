// =================================================
//  Name:    Fabs
//  Class:   CSE-5700 01
//  Project: Lab 3
//  Project Description: A recursive decent parser that
//  parses the given grammar.
//       Terminals:
//          a, b, c, d
//      Given grammar:
//          S -> aAB
//          A -> Abc | b
//          B -> d
//      Grammar w/o left recursion:
//          S  -> aAB
//          A  -> bA'
//          A' -> bcA'
//              | epsilon
//          B  -> d
//      NOTE: In the code A' is referred to as C
// =================================================

#include <stdio.h>
#include <string.h>

typedef struct
{
    char *input;
    int size; // Does not include the null character
    int curr;
} Parser;

Parser new_parser(char *, int);
int next(Parser *);
void print(const Parser *);

void parse(Parser *);
void S(Parser *);
void A(Parser *);
void B(Parser *);
void C(Parser *);

int main(int argc, char **argv)
{
    char input[50];
    printf("> ");
    scanf("%50s", input); // Do not insert an input of length greater than 50
    Parser p = new_parser(input, strlen(input));
    parse(&p);
    return 0;
}

Parser new_parser(char *input, int size)
{
    Parser p = {input : input, size : size, curr : 0};
    return p;
}

int next(Parser *p)
{
    char c = p->curr;

    if (p->curr == -1 || p->curr + 1 >= p->size)
    {
        p->curr = -1;
    }
    else
    {
        p->curr++;
    }

    return c;
}

int peek(Parser *p)
{
    return p->curr;
}

void print(const Parser *p)
{
    char curr = p->curr != -1 ? p->input[p->curr] : '$';
    printf("input: %s current: %c curr index: %d\n", p->input, curr, p->curr);
}

void parse(Parser *p)
{
    if (p == NULL || p->size == 0)
        return;

    int curr = next(p);
    if (curr != -1)
    {
        if (p->input[curr] == 'a')
        {
            S(p);
        }
        else
        {
            printf("Error expected 'a' got %c\n", curr != -1 ? p->input[curr] : '$');
        }
    }
    printf("\n");
}

void S(Parser *p)
{
    printf("(S a");
    int c = next(p); // Consume the 'a' and get next terminal
    if (c == -1 || p->input[c] != 'b')
    {
        printf("Error expected 'b' got %c\n", c != -1 ? p->input[c] : '$');
        return;
    }
    else
    {
        A(p);
        int c = next(p);
        if (c == -1 || p->input[c] != 'd')
        {
            printf("\nError expected 'd' got %c\n", c != -1 ? p->input[c] : '$');
            return;
        }
        else
        {
            B(p);
        }
    }
    printf(")");
}

void A(Parser *p)
{

    int c = peek(p); // Check if the next terminal is a 'b'
    if (c == -1)
    {
        printf("Error in A, got end of string ...\n");
    }
    printf("(A b");
    if (p->input[c] == 'b')
    {
        next(p); // Consume the 'b'
        C(p);
    }
    printf(")");
}

void C(Parser *p)
{
    int c = next(p); // Consume the 'b' and get next terminal
    printf("(A' bc");
    int lookahead = peek(p);
    if (lookahead == -1 || p->input[lookahead] != 'b')
    {
        printf(")");
        return;
    }
    next(p); // consume 'c'

    C(p);
}

void B(Parser *p)
{
    int c = next(p); // Consume the 'd' and get next terminal
    printf("(B d)");
}