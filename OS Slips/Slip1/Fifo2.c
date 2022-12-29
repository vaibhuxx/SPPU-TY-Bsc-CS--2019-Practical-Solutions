#include <stdio.h>
int main()
{
    int refS[10], pgFaults = 0, m, n, s, pages, frames;
    printf("\nEnter the number of  pages: \t");
    scanf("%d ", &pages);
    printf("\nEnter the Strings of page references:\n");
    for (m = 0; m < pages; m++)
    {
        printf("Value No [%d]:\t ", m + 1);
        scanf("%d", &refS[m]);
    }
    printf("\nEnter number of frames");
    {
        scanf("%d", &frames);
    }
    int temp[frames];
    for (m = 0; m < frames; m++)
    {
        temp[m] = -1;
    }
    for (m = 0; m < pages; m++)
    {
        s = 0;
        for (n = 0; n < frames; n++)
        {
            if (refS[m] == temp[n])
            {
                s++;
                pgFaults--;
            }
        }
        pgFaults++;
        if ((pgFaults <= frames) && (s == 0))
        {
            temp[m] = refS[m];
        }
        else if (s == 0)
        {
            temp[(pgFaults - 1) % frames] = refS[m];
        }
        printf("\n");
        for (n = 0; n < frames; n++)
        {
            printf("%d\t", temp[n]);
        }
    }
    printf("\n Total number of page faults:\t %d\n ", pgFaults);
    return 0;
}