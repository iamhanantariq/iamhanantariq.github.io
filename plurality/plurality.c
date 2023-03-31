#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO checks each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++; //adds count
            return true;
        }
    }
    return false; //returns false
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    string name;
    int vote;

// nexted loop bubble stlye, no bueno
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX - 1; j++)
        {
            vote = candidates[i].votes;
            name = candidates[i].name;
            if (vote < candidates[j + 1].votes) //shifting things over
            {
                candidates[i].name = candidates[j + 1].name;
                candidates[i].votes = candidates[j + 1].votes;
                candidates[j + 1].name = name;
                candidates[j + 1].votes = vote;
            }
        }
    }

    printf("%s\n", candidates[0].name); // print first winner

    for (int i = 0; i < MAX - 1; i++)
    {
        if (candidates[0].votes == candidates[i + 1].votes) //check other winners
        {
            printf("%s\n", candidates[i + 1].name);
        }
    }
    return;
}