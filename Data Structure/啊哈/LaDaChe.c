#include <stdio.h>

struct queue{
    int data[1000];
    int head;
    int tail;
};

struct stack{
    int data[10];
    int top;
};

int main(){
    struct queue q1, q2;
    struct stack s;
    int book[10]; // Record cards on table
    int t; // Temporary variable

    // Initializing stack and queue
    s.top = 0;
    q1.head = 1; q1.tail = 1;
    q2.head = 1; q2.tail = 1;

    // Initializing book array
    for(int i = 1 ; i <= 9 ; i++){
        book[i] = 0;
    }

    // Each player has 6 cards
    for(int i = 1 ; i <= 6 ; i++){
        scanf("%d", &q1.data[q1.tail]);
        q1.tail++;
    }

    for(int i = 1 ; i <= 6 ; i++){
        scanf("%d", &q2.data[q2.tail]);
        q2.tail++;
    }

    // When game is not over, i.e. each player's hand is not empty
    while(q1.head < q1.tail && q2.head < q2.tail){
        t = q1.data[q1.head]; // Player1 plays a card
        // Judge whether Player1 can win the round
        if (book[t] == 0){ // Doesn't win
            q1.head++;
            s.top++;
            s.data[s.top] = t;
            book[t] = 1;
        }
        else{
            q1.head++;
            q1.data[q1.tail] = t;
            q1.tail++;
            while(s.data[s.top] != t){
                book[s.data[s.top]] = 0;
                q1.data[q1.tail] = s.data[s.top];
                q1.tail++;
                s.top--;
            }
            book[s.data[s.top]] = 0; // Take t card previously on table back
            q1.data[q1.tail] = s.data[s.top];
            q1.tail++;
            s.top--;
        }
        if (q1.head == q1.tail)  break; // If player1's hand is empty, game over

        t = q2.data[q2.head]; // Player2 plays a card
        if (book[t] == 0){ 
            q2.head++;
            s.top++;
            s.data[s.top] = t;
            book[t] = 1;
        }
        else{
            q2.head++;
            q2.data[q2.tail] = t;
            q2.tail++;
            while(s.data[s.top] != t){
                book[s.data[s.top]] = 0;
                q2.data[q2.tail] = s.data[s.top];
                q2.tail++;
                s.top--;
            }
            book[s.data[s.top]] = 0; // Take t card previously on table back
            q2.data[q2.tail] = s.data[s.top];
            q2.tail++;
            s.top--;
        }
    }

    if (q2.head == q2.tail) {
        printf("Player1 wins.\n");
        printf("The cards in player1's hand are:");
        for (int i=q1.head ; i<=q1.tail-1 ; i++)
            printf(" %d", q1.data[i]);
        if(s.top > 0){
            printf("\nThe cards on the table are:");
            for(int i=1 ; i<=s.top ; i++)
                printf(" %d", s.data[i]);
        } else {
            printf("\nNo cards on table.");
        }
    } else {
        printf("Player2 wins.\n");
        printf("The cards in player2's hand are:");
        for (int i=q2.head ; i<=q2.tail-1 ; i++)
            printf(" %d", q2.data[i]);
        if(s.top > 0){
            printf("\nThe cards on the table are:");
            for(int i=1 ; i<=s.top ; i++)
                printf(" %d", s.data[i]);
        } else {
            printf("\nNo cards on table.");
        }
    }

    getchar();getchar();
    return 0;
}