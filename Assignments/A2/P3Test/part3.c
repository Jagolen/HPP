#include <stdio.h>
#include <stdlib.h>


//The struct of the linked list, containing index, min, max and a pointer to the next node
typedef struct node {
    int index;
    double min, max;
    struct node *next;
} node_t, *link; //Link is defined as *node_t


//Constructor for new nodes
link new_nodes(int new_index, double new_min, double new_max, link next) {
    link head = (link) malloc(sizeof(node_t)); //Memory is allocated for new nodes
    //We store the variables and the pointer to the next node
    head->index = new_index;
    head->min = new_min;
    head->max = new_max;
    head->next = next;
    return head; //the pointer to the node is returned
}

//Adding an element to the list
void add_element(node_t **head, int new_index, double new_min, double new_max) {
    while (*head != NULL && new_index > (**head).index) { //If the index at the current node is lower than the index in the current node, move to the next node
    head = &((**head).next); 
    }
    *head = new_nodes(new_index, new_min, new_max, *head); //The new node is added in the correct location ordered by index
}

//Removing an element from the list
void remove_node(node_t **head, int new_index) {
    node_t *nth = **&head, *prev_head;

    if (nth != NULL && nth->index == new_index) {//If the first node is the correct node we set the head to point to the node after the current one
        **&head = nth->next;
        free(nth); //The memory of the removed node is free'd
        return;
    }

    while (nth != NULL && nth->index != new_index) { //If the index of the current node is not the one which should be removed, move to the next one
        prev_head = nth;
        nth = nth->next;
    }
    if (nth == NULL) //The list is empty, nothing happens
        return;

    prev_head->next = nth->next; //When the correct node is reached, the pointer to that node is set to point to the node after the correct node

    free(nth); //The memory from the removed node is free'd
}

//Printing the list
void printList(node_t* node) {
    while (node != NULL) {//As long as we havent reached the end of the list, print out the index, min and max variable of the current node
        printf("%2d\t%10lf\t%10lf\n", node->index, node->min, node->max);
        node = node->next; //move to the next node
    }
}

int main(){
    //Defining the variables
    link list = NULL;
    int index;
    double min, max;
    char letter;

    while(0 == 0){//Basically while true statement, while loop will run forever
        printf("Enter command: ");
        scanf("%s", &letter); //Looks at the first input to decide which operation should be used, the different types are handled with a switch

        switch (letter){
            case 'A': //First input is "A", elements should be added to the list
                scanf("%d%lf%lf", &index, &min, &max); //index, min, max are read from the input and saved
                remove_node(&list, index); //Element at index is removed if it already exists
                add_element(&list, index, min, max); //Variables are added to the list with the add_element function
                break;

            case 'D': //First input is "D", elements should be removed from the list
                scanf("%d", &index); //Reads the index to be removed from index
                remove_node(&list, index); //Element at index are removed with the remove_node function
                break;

            case 'P': //First input is "P", linked list should be printed
                printf("day\t min\t         max\n"); //First labels for the columns in the table are printed
                printList(list); //The elements are printed with the print list function
                break;

            case 'Q'://first input is "Q", program should terminate, which is done with exit(0)
                exit(0);

            default://First input is not the other cases and is invalid.
                printf("Invalid letter\n");
                break;
        }     
    }
    return 0;
}