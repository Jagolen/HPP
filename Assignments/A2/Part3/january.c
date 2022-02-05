#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    double min, max;
    struct node *next;
} node_t;

void add_element(node_t *head, int index, double min, double max, int *first_index, int *last_index){
    if (head == NULL){//Empty list, we have to create it
            head = (node_t*) malloc(sizeof(node_t));
            head -> index = index;
            head -> min = min;
            head -> max = max;
            head -> next = NULL;
            *first_index = head->index;
            *last_index = head->index;
    }
    else{
        if(index < *first_index){//item should be put first in the list
            node_t *new_first;
            new_first = (node_t*)malloc(sizeof(node_t));
            new_first->index = index;
            new_first->min = min;
            new_first->max = max;
            *first_index = new_first->index;
            new_first->next = *&head;
            *&head = new_first;
        }
        else if(index > *last_index){//item should be put last in the list
            node_t *current = head;
            while(current->next != NULL) current = current->next;
            current->next = (node_t*) malloc(sizeof(node_t));
            current = current->next;
            current->index = index;
            current->min = min;
            current->max = max;
            current->next = NULL;
            *last_index = current->index;
        }
        else{//Item should be put somewhere inside the list

        }
    }
}

int main(){
    int index, first_index, last_index;
    double min, max;
    char letter;

    node_t * head = NULL;

    while(0 == 0){
        printf("Enter command: ");
        scanf("%s", &letter);

        switch (letter){
            case 'A':
            break;


            case 'D':
            break;


            case 'P':
            break;


            case 'Q':
            exit(0);


            default:
            printf("Invalid letter\n");
            break;
        }     
    }


    return 0;
}