#include <stdlib.h> // srand rand
#include <stdio.h> // printf
#include <stdbool.h> // bool
#include <assert.h> // assert
#include <math.h> // floor
#include <time.h> // time

/** Minimal value the player should guess (inclusive). */
const int MINIMUM = 1;
/** Maximal value the player should guess (inclusive). */
const int MAXIMUM = 30;
/** How many attempts the player has to guess both values. */
const int MAX_ATTEMPTS = 3;

int randint(int min, int max)
{
    assert(min < max);
    return min + rand() % (max - min + 1);
}

void print_title()
{
    printf(
        "--- Guessing Game ---\n"
        "You have three attempts to guess a random number between one and thirty.\n"
    );
}

void run_game()
{
    bool success = false;
    int attempts = 0;
    int rnd1 = randint(MINIMUM, MAXIMUM);
    int rnd2 = randint(MINIMUM, MAXIMUM);
    // printf("1 -> %i\n2 -> %i\n", rnd1, rnd2);
    while (attempts < MAX_ATTEMPTS && !success)
    {
        printf("---------------------\n%i. Attempt:\n", attempts + 1);
        switch (attempts)
        {
        case 1:
            printf("Hint: Num 1 * Num 2 = %i\n", rnd1 * rnd2);
            break;
        case 2:
            printf("Hint: Num 1 - Num 2 = %i\n", abs(rnd1 - rnd2));
            break;
        }
        int try1, try2;
        printf("Enter num one: ");
        scanf(" %i", &try1);
        printf("Enter num two: ");
        scanf(" %i", &try2);
        success = (try1 == rnd1 && try2 == rnd2) || (try1 == rnd2 && try2 == rnd1);
        attempts++;
    }
    printf("---------------------\n");
    if (success) printf("Congratulations, you guessed correct!\n");
    else printf("Well, maybe next time! %i and %i were correct.\n", rnd1, rnd2);
}

bool ask_another_game()
{
    char input;
    printf("Play another game? (y/n) ");
    scanf(" %c", &input);
    return input == 'y' || input == 'j';
}

int main()
{
    srand(time(NULL));
    print_title();
    while (true)
    {
        run_game();
        if (!ask_another_game()) break;
    }
    return 0;
}