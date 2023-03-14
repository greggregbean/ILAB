#include "akinator.h"

int main()
{
    tree tr;

    FILE* textTree = fopen("textTree.txt", "r");
    tr.reader(textTree);
    fclose(textTree);

    tr.textDump();

    while(true)
    {
        tr.akinator();

        printf("Do you want to play again? (y/n) \n");

        char answer[PHRASEMAXLEN];

        scanf("%s", answer);

        while((strcmp(answer,"y") != 0) && (strcmp(answer, "n") != 0))
        {
            printf("Please enter 'y' or 'n'. \n");
            scanf("%s", answer);
        }

        if(answer[0] == 'n')
        {
            printf("Thanks for the game. \n");
            break;
        }

        else if(answer[0] == 'y')
        {
            continue;
        }
    }

    textTree = fopen("textTree.txt", "w");
    tr.fileDump(textTree);

    FILE* graph    = fopen("gpraph.dot"  , "w");
    tr.graphDump(graph);

    fclose(textTree);
    fclose(graph);

    return 0;
}