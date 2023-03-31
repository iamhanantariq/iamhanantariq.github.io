#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int margin;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }
            else
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
                if (preferences[i][j] != preferences[j][i])
                {
                    if (preferences[i][j] > preferences[j][i])
                    {
                        pairs[pair_count].winner = i;
                        pairs[pair_count].loser = j;
                        pair_count++;
                    }
                    else
                    {
                        pairs[pair_count].winner = j;
                        pairs[pair_count].loser = i;
                        pair_count++;
                    }
                }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    if (pair_count < 2)
    {
        return;
    }

    int m, wn, ln;

    //Calc margin
    for (int n = 0; n < pair_count; n++)
    {
        pairs[n].margin = preferences[pairs[n].winner][pairs[n].loser] - preferences[pairs[n].loser][pairs[n].winner];
        printf("%i ", pairs[n].margin);
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count - 1; j++)
        {
            m = pairs[i].margin;
            wn = pairs[i].winner;
            ln = pairs[i].loser;
            if (m <= pairs[j].margin)
            {
                pairs[i].margin = pairs[j].margin;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].margin = m;
                pairs[j].winner = wn;
                pairs[j].loser = ln;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int cycle[candidate_count];

    for (int k = 0; k < pair_count; k++)
    {
          locked[pairs[k].winner][pairs[k].loser] = true;
    }

    int badboi[3];
    for (int i = 0; i < candidate_count; i++)
    {
        int cf = 0;
        int ct = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true || locked[j][i] == false)
            {
                cf++;
                if (locked [j][i] == true)
                {
                ct++;
                badboi[0] = j;
                badboi[1] = i;
                }
            }
        }
        if (cf == candidate_count - 1 && ct == 1)
        {
            locked[badboi[0]][badboi[1]] = false;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                counter++;
                if (counter == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}