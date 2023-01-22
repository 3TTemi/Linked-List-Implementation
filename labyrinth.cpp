#include "labyrinth.h"
#include "demo/MazeGenerator.h"
#include "testing/SimpleTest.h"
using namespace std;


const string kYourName = "Temi Adebowale";

const string kPathOutOfNormalMaze = "EESSSEWWNWNSESENNEN";


bool isPathToFreedom(MazeCell* start, string moves, Set<string> needs) {
    Set<string> found;
    MazeCell* current = start;

    if(needs.contains(start->contents))
    {
        found.add(start->contents);
    }

    for(int i = 0; i < moves.length(); i++)
    {
        if (moves[i] != 'N' && moves[i] != 'S' && moves[i] != 'E' && moves[i] != 'W')
        {
            error("Invalid character found");
        }
        if (moves[i] == 'N')
        {
            if(current->north == nullptr)
            {
                return false;
            }
            else
            {
                current = current->north;
                if (needs.contains(current->contents))
                {
                    found.add(current->contents);
                }
            }
        }
        else if(moves[i] == 'S')
        {
            if(current->south == nullptr)
            {
                return false;
            }
            else
            {
                current = current->south;
                if (needs.contains(current->contents))
                {
                    found.add(current->contents);
                }
            }
        }
        else if(moves[i] == 'E')
        {
            if(current->east == nullptr)
            {
                return false;
            }
            else
            {
                current = current->east;
                if (needs.contains(current->contents))
                {
                    found.add(current->contents);
                }
            }
        }
        else if(moves[i] == 'W')
        {
            if(current->west == nullptr)
            {
                return false;
            }
            else
            {
                current = current->west;
                if (needs.contains(current->contents))
                {
                    found.add(current->contents);
                }
            }
        }
        if(found.equals(needs))
        {
            return true;
        }
    }

    return false;
}


/* * * * * * Test Cases Below This Point * * * * * */

TEST("Check paths in the sample from writeup") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES", allThree));

    /* This path works to pick up just potion */
    EXPECT(isPathToFreedom(maze[2][2], "ESNW", {"Potion"}));

    /* This path doesn't work, since doesn't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW", allThree));

    /* This path doesn't work, cannot walk through walls. */
    EXPECT(!isPathToFreedom(maze[2][2], "NNWWSSSEEE", allThree));
}

TEST("Works when start on an item") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "E", {"Potion"}));
    EXPECT(isPathToFreedom(maze[0][1], "W", {"Potion", "Spellbook"}));
}

TEST("Reports errors if given illegal characters") {
    auto maze = toMaze({"P-S-W"});

    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Q", {"Wand"}));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Ee", {"Wand"}));
}

TEST("Escape from your personal labyrinth!") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    /* A maze for you to escape from. This maze will be personalized
     * based on the constant kYourName.
     */
    EXPECT(kYourName != "TODO");
    MazeCell* startLocation = mazeFor(kYourName);

    /* Set a breakpoint here. As a reminder, the labyrinth you
     * get will be personalized to you, so don't start exploring the labyrinth
     * unless you've edited the constant kYourName to include your name(s)!
     * Otherwise, you'll be escaping the wrong labyrinth.
     */
    EXPECT(kPathOutOfNormalMaze != "TODO");
    EXPECT(isPathToFreedom(startLocation, kPathOutOfNormalMaze, allThree));
}

