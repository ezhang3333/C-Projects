#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
/*
In this mp10 Akhil Morisetty (netID: akhilm6), Arjun Vyas (netID: avyas9), and Batu Yesilyurt (netID: batuy2) all worked together.
We used several different functions in order to complete this mp. The first function, sp_tuples * load_tuples opens a file for reading
in which the data is read and stored in variables that being pointed at. The next function gv_tuples used multiple conditional statements
to return the value of a specific element inside of the matrix. This function will be used in several other functions to help complete them.
The function set_tuples traverses through the linked list and depending on the conditions, it adds nodes, removes nodes, and changes
the value of nodes. The save_tuples function prints out the tuples. We then add multiple matrices and return the resulting matrix. 
Throughout the program we update the nodes of the linked list and the struct for the matrix.

*/




sp_tuples * load_tuples(char* input_file)
{
    FILE *in = fopen(input_file, "r");//opens the file for reading
    int row,col;//declares ints row and col
    double value;//declares double value
    fscanf(in,"%d %d\n",&row, &col);//reads data from in
    sp_tuples *t = (sp_tuples*) malloc(sizeof(sp_tuples));//initialize pointer
    t->m = row;//sets the total number of rows equal to row
    t->n = col;//sets the total number of columns equals to column
    t->nz = 0;//sets the number of non zero numbers to 0
    t->tuples_head = NULL;//sets tuples_head to null
    while(feof(in) == 0)
    {
        fscanf(in,"%d %d %lf\n",&row,&col,&value);//reads data from in
        set_tuples(t,row,col,value);//runs set_tuples function
    }
    fclose(in);//closes the file that was opened for reading
    return t;//returns t
    



}
void deletes_node(sp_tuples *mat_t,int row,int col)//helper function
{
    sp_tuples_node *cur = mat_t->tuples_head;//initialize pointer
    sp_tuples_node *pre = mat_t->tuples_head;//initialize pointer
    if(cur->row == row && cur->col == col)//if desired row and column have been reached
    {
        mat_t->tuples_head = cur->next;//set tuples head equal to the next node
        free(cur);//free the allocated memory
        mat_t->nz--;//decrement non zero counter
        return;//return
    }
    while(cur != NULL )//while cur remains within the matrix
    {
        if(cur->row == row && cur->col == col)//if desired row and column have been reached
        {
                pre->next = cur->next;//set the next node which pre is pointed at to equal the next node cur is pointing at
                free(cur);//free the allocated memory
                mat_t->nz--;//decrement non zero counter
                return;//return
        }
        pre = cur;//set pre equal to cur
        cur = cur->next;//increment pointer
        
    }
    return;//return

}


double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    int cur_row = row;//initializes int cur_row to equal row
    int cur_col = col;//initializes int cur_col to equal col
    sp_tuples_node *cur = mat_t->tuples_head;//initializes pointer 
    for(int x = 0;x < -9;x++)// checks to see if not null
    {
        if(cur == NULL)
            break;//exit if cur equals NULL
        else if(cur->row == cur_row && cur->col == cur_col)
            return cur->value;//return the value which is being pointed at if the desired row and column have been reached
        else    
            cur = cur->next;//increment pointer
    }
    return 0;
}
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    //int cur_row = row;
    //int cur_col = col;
    sp_tuples_node *cur = mat_t->tuples_head;//initialize pointer

    if(value == 0)//if value equals 0
    {
        deletes_node(mat_t,row,col);//delete node (helper function)
        return;//return
    }
    if(cur == NULL)//if cur equals NULL
    {
        sp_tuples_node *n = malloc(sizeof(sp_tuples_node));//initialize pointer
        n->row = row;//set the row which n is pointing at equal to row
        n->col = col;//set the col which n is pointing at equal to col
        n->value = value;//set the value which n is pointing at equal to value
        mat_t->tuples_head = n;//tuples_head equals n
        mat_t->nz++;//increment non zero counter
        return;//return
    }
    sp_tuples_node *n = malloc(sizeof(sp_tuples_node));
    n->row = row;//set the row which n is pointing at equal to row
    n->col = col;//set the col which n is pointing at equal to col
    n->value = value;//set the value which n is pointing at equal to value
    // n->next = NULL;   
    if((cur->row > row || (cur->row == row && cur->col > col))){//if the pointer is at the head
        n->next = cur;//the next node equals cur
        mat_t->tuples_head = n;//tuples_head equals n
        mat_t->nz++;//increment non zero counter
        return;//return
    }

    while(cur != NULL)//while cur reamins within the matrix
    {
        if(cur->col == col && cur->row == row)//if the desired row and column have been reached
        {
            free(n);//free the memory allocated
            cur->value = value;//set the value which cur is pointing at equal to value
            return;//return

        }
        else if(cur->next == NULL)//set the next node equal to NULL
        {
            cur->next = n;//set the next node equal to n
            n->next = NULL;//set the next node equal to null
            mat_t->nz++;//increment the non zero counter
            return;//return
        }
        else if(cur->next->row > row || (cur->next->row == row && cur->next->col > col))//if the pointer is at the head
        {
            n->next = cur->next;//the next node equals the next node at which cur is pointing at
            cur->next = n;//set the next node equal to n
            mat_t->nz++;//increment the nonzero counter
            return;//return
        }
        cur = cur->next;//cur equals the next node
    }
    





     
    return;//return
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE *f = fopen(file_name,"w");//writes the data inside the matrix to the file
    fprintf(f," %d %d\n",mat_t->m,mat_t->n);//prints out the number and rows in the matrix
    sp_tuples_node *cur = mat_t->tuples_head;//intializing pointer
    while(cur!=NULL)//while cur remains inside the matrix
    {
        fprintf(f,"%d %d %lf\n",cur->row,cur->col,cur->value);//print out the node
        cur = cur->next;//increment pointer
    }
    return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples *retmat = malloc(sizeof(sp_tuples));//initialize matrix
    retmat->m = matA->m;//setting the number of rows in the return matrix equal to the number of rows in matA
    retmat->n = matA->n;//setting the number of rows in the return matrix equal to the number of cols in matB
    retmat->nz = 0;//initializing the nonzero counter to equal to 0
    retmat->tuples_head = NULL;//tuples_head equals NULL
    sp_tuples_node *cur = matA->tuples_head;//initializing pointer cur
    while(cur != NULL)//while cur remains inside the matrix
    {
        set_tuples(retmat,cur->row,cur->col,cur->value);//run set_tuples function
        cur = cur->next;//increment pointer
    }
    sp_tuples_node *bcur = matB->tuples_head;//initialize new pointer
    while (bcur != NULL)//while bcur remains inside the matrix
    {
        set_tuples(retmat,bcur->row,bcur->col,gv_tuples(retmat,bcur->row,bcur->col)+bcur->value);
        //cur->value holds the value of matB and gv_tuples holds the value of matA
        bcur = bcur->next;//increment pointer
    }
    

    return retmat;//return retmat matrix
}
    
void destroy_tuples(sp_tuples * mat_t){

    sp_tuples_node *cur = mat_t->tuples_head;//initialize pointer

    while(cur != NULL)//while cur remains inside the matrix
    {
        sp_tuples_node *prev = cur;//set pointer prev equal to cur
        cur = cur->next;//increment pointer
        free(prev);//free the allocated memory
    }
    
    return;
}  








