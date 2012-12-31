#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE       9
#define MAX_INPUT        80
#define VALID_INPUT_SIZE 2  // account for '\n'

void print_instructions();
void init_board(int b[], int n);
void show_board(int b[]);
int dotc(int d);
size_t get_input(char *line, int max);
int computer_move(int board[]);
int computer_tryagain(int tries[]);
int player_move(int board[], int i);
int check_row(int board[], char p, int c1, int c2, int c3);
int is_winner(int board[], char p);
int is_stalemate(int board[]);
int is_quitting(int c);
int is_input_invalid(char input[], size_t len);
int process_input(int board[]);

void print_instructions()
{
    printf("TIC TAC TOE!\n");
    printf("============\n\n");
    printf("Choose the number of the square you want to put an 'x'\n");
    printf("The computer will choose a square for an 'o'\n");
    printf("Continue placing x's until you get 3-in-a-row for the win!\n\n");
}

void init_board(int b[], int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        b[i] = i;
    }
}

void show_board(int b[])
{
    printf("%c | %c | %c\n", dotc(b[0]), dotc(b[1]), dotc(b[2]));
    printf("----------\n");
    printf("%c | %c | %c\n", dotc(b[3]), dotc(b[4]), dotc(b[5]));
    printf("----------\n");
    printf("%c | %c | %c\n", dotc(b[6]), dotc(b[7]), dotc(b[8]));
}

int dotc(int d)
{
    if (d == 'x' || d == 'o')
    {
        return d;
    }
    else
    {
        return d + '0';
    }

}

size_t get_input(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
    {
        return 0;
    }
    else
    {
        return strlen(line);
    }
}

int computer_move(int board[])
{
    srand(time(NULL));
    int i = 0;
    int tries[BOARD_SIZE] = {0}; 
    int tryagain = 1;

    while (tryagain)
    {
        // it's not very smart. just choose a random open spot
        i = rand() % BOARD_SIZE;
        if (tries[i]) continue;

        if (board[i] != 'x' && board[i] != 'o')
        {
            board[i] = 'o';
            return i;
        }

        tries[i] = 1;
        tryagain = computer_tryagain(tries);
    }

    return 0;
}

int computer_tryagain(int tries[])
{
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (!tries[i])
        {
            return 1;
        }
    }

    return 0;
}

int check_row(int board[], char p, int c1, int c2, int c3)
{
    if (board[c1] == p && board[c2] == p && board[c3] == p)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_winner(int board[], char p)
{
    if (check_row(board, p, 0, 1, 2))
        return 1;
    if (check_row(board, p, 3, 4, 5))
        return 1;
    if (check_row(board, p, 6, 7, 8))
        return 1;
    if (check_row(board, p, 0, 3, 6))
        return 1;
    if (check_row(board, p, 1, 4, 7))
        return 1;
    if (check_row(board, p, 2, 5, 8))
        return 1;
    if (check_row(board, p, 0, 4, 8))
        return 1;
    if (check_row(board, p, 2, 4, 6))
        return 1;

    return 0;
}

int is_stalemate(int board[])
{
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i] != 'x' &&  board[i] != 'o')
        {
            return 0;
        }
    }

    return 1;
}

int is_quitting(int c)
{
    if (c == 'q' || c == 'Q')
    {
        return 1;
    }

    return 0;
}

int player_move(int board[], int i)
{
    if (board[i] != 'x' && board[i] != 'o')
    {
        board[i] = 'x';
        return 1;
    }

    return 0;
}

int is_input_invalid(char input[], size_t len)
{
    if (len < 0 && len > VALID_INPUT_SIZE)
    {
        return 1;
    }

    int i = input[0] - '0';
    if (i >= 0 && i < BOARD_SIZE)
    {
        return 0;
    }

    return 1;
}

int process_input(int board[])
{
    // prompt
    printf("\n>");

    char input[MAX_INPUT] = {0};
    size_t n = get_input(input, MAX_INPUT);

    if (is_input_invalid(input, n) && !is_quitting(input[0]))
    {
        printf("Invalid square. Try again\n\n");               
        return 1;
    }

    if (is_quitting(input[0]))
    {
        printf("Giving up? Lame.\n");
        return 0;
    }

    
   int i =  input[0] - '0';
   if (player_move(board, i))
   {
        if (is_winner(board, 'x'))
        {
            printf("You WIN!\n");
            return 0;
        }

        if (computer_move(board) && is_winner(board, 'o'))
        {
            printf("You lose :(\n");
            return 0;
        }
        else
        {
            if (is_stalemate(board))
            {
                printf("Stalemate\n");
                return 0;
            }
        }
    } 
    else
    {
        printf("That one is already in use. Try again.\n");
    }
    
    return 1;
}

int main()
{
    int board[BOARD_SIZE] = {0};
    init_board(board, BOARD_SIZE);

    print_instructions();

    do
    {
        show_board(board);
    }while(process_input(board));
    

    // show the board one last time before exit
    show_board(board);

    return 0;
}
