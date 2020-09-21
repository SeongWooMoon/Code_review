/*
Date: 2020-09-17 ~ 2020-09-18
Writer: Seongwoo Moon
Purpose of this code or program : HW3_P2

Main idea
1. Set original siteSpin 1D pointer array
2. Set a 2D array((xdim+2)*(ydim+2) surrounding siteSpin
ex)
x x x x x
x 1 2 3 x -> 1D pointer array size = 3 * 3 
x 4 5 6 x -> 2D pointer array size = (3+2) * (3+2) = 25
x x x x X
3. Fill the elements of the shell (3 times way)
4. Declear neigh array in print_neigh function 
5. Set neigh array about csite and print them
*/
#include<stdio.h>
#include<stdlib.h>

void print_neigh(int **,int,int, int,int); // Declear neigh function : print neigh and cite

int main(){

    //decleard variable
    int xdim, ydim, nsp, ex_nsp, ex_xdim, ex_ydim, csite; 
    int *siteSpin,**ex_siteSpin; //decleard  1D, 2D pointer
    int ct = 1;

    printf("Enter the xdim : ");
    scanf("%d",&xdim);
    printf("Enter the ydim : ");
    scanf("%d",&ydim); 
    //Set the xdim and ydim

    nsp = xdim*ydim; // calculate total size of 1D pointer
    ex_xdim = xdim+2; // set extended xdim size
    ex_ydim = ydim+2; // set extended ydim size
    ex_nsp = ex_xdim*ex_ydim; // calculate total size of 2D pointer

    siteSpin =  (int *)malloc((nsp+1)*sizeof(int)); // 1D pointer dynamic allocation
    ex_siteSpin = (int **)malloc((ex_ydim+1)*sizeof(int*)); // Double pointer dynamic allocation

    for(int j = 0; j < ex_ydim; j++)
    ex_siteSpin[j] = (int *)malloc((ex_xdim+1)*sizeof(int)); // ex_siteSpin[j] dynamic allocation

    for(int i = 1 ; i <= nsp; i++) // Store sequential numbers to the siteSpin array
    siteSpin[i] = i; 

    //initicalize ex_siteSpin array to 0
    for(int i= 0; i<ex_ydim ; i++){
        for(int j = 0; j < ex_xdim ; ++j){
            ex_siteSpin[i][j] = 0;
        }
    }
   
    // 
    for(int i= 1; i<ex_ydim-1 ; i++){ //Fill in the siteSpin value inside the ex_siteSpin
        for(int j = 1; j < ex_xdim-1 ; j++){
            ex_siteSpin[i][j] = siteSpin[ct];
            ct++;
        }
    }

    for(int i = 1; i < ex_xdim-1; i++){ //Fill in the top and bottom value inside the ex_siteSpin
        ex_siteSpin[0][i] = siteSpin[xdim*(ydim-1)+i];
        ex_siteSpin[ex_ydim-1][i] = siteSpin[i];
    }   

    for(int j = 1;j < ex_ydim-1; j++){ //Fill in the left and right value inside the ex_siteSpin
        ex_siteSpin[j][0] = siteSpin[xdim*j];
        ex_siteSpin[j][ex_xdim-1] = siteSpin[xdim*(j-1)+1];
    }   

    //Fill in the edge value inside the ex_siteSpin
    ex_siteSpin[0][0] = siteSpin[nsp];
    ex_siteSpin[0][ex_xdim-1] = siteSpin[xdim*(ydim-1)+1];
    ex_siteSpin[ex_ydim-1][0] = siteSpin[xdim];
    ex_siteSpin[ex_ydim-1][ex_xdim-1] = siteSpin[1];

    csite = 1; //set the csite value
    for(int yc= 1; yc<ex_ydim-1 ; yc++){ // Looping as much as the size of siteSpin.
        for(int xc= 1; xc < ex_xdim-1 ; xc++){
            print_neigh(ex_siteSpin,nsp,xc,yc,csite); 
            csite++;
        }
    }
    


    for(int i = 0 ; i < ydim ; i++) //release 2D pointer dynamic allocation
    free(ex_siteSpin[i]); 
    
    free(siteSpin); // release 1D pointer dynamic allocation

    return 0;
}   

void print_neigh(int **ex_siteSpin,int nsp, int x, int y,int csite){

    int x_dic[8]={1,1,0,-1,-1,-1,0,1}; //Set next x_direction 
    int y_dic[8]={0,-1,-1,-1,0,1,1,1}; //Set next y_direction
    

    int neigh[8]; //Set neigh array

    printf("\n%s %d %s\n","Selected site:",csite,"(csite)");

    for(int j = 0; j<8 ; j++){ //It searches 8 directions sequentially and puts them into the neigh array.
        neigh[j] = ex_siteSpin[y+y_dic[j]][x+x_dic[j]];  
    }

    //print neigh value
    printf("neigh[4] neigh[3] neigh[2]\n");
    printf("  %d       %d       %d\n",neigh[3],neigh[2],neigh[1]);
    printf("neigh[5] csite neigh[1]\n");
    printf("  %d       %d       %d\n",neigh[4],csite,neigh[0]);
    printf("neigh[6] neigh[7] neigh[8]\n");
    printf("  %d       %d       %d\n",neigh[5],neigh[6],neigh[7]);

    }

