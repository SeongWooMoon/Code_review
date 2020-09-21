/*
Date: 2020-09-17 ~ 2020-09-21
Writer: Seongwoo Moon
Purpose of this code or program : HW3_P2

Main idea
1. Set original siteSpin 1D pointer array
2. Set a 1D array ex_siteSpin((xdim+2)*(ydim+2)) surrounding siteSpin
ex)
x x x x x
x 1 2 3 x -> 1D pointer array size = 3 * 3 
x 4 5 6 x -> 1D pointer extended array size = (3+2) * (3+2) = 25
x x x x X
3. Fill the elements of the shell (3 times way)
4. Declear neigh array in print_neigh function 
5. Set neigh array about csite and print them
*/
#include<stdio.h>
#include<stdlib.h>

void print_neigh(int *,int,int,int); // Declear neigh function : print neigh and cite

int main(){

    //decleard variable
    int xdim, ydim, nsp, ex_nsp, ex_xdim, ex_ydim, csite; 
    int *siteSpin,*ex_siteSpin; //decleard  1D pointer
    int ct,ex_ct=0;


    printf("Enter the xdim : ");
    scanf("%d",&xdim);
    printf("Enter the ydim : ");
    scanf("%d",&ydim); 
    //Set the xdim and ydim

    nsp = xdim*ydim; // calculate total size of 1D pointer
    ex_xdim = xdim+2; // set extended xdim size
    ex_ydim = ydim+2; // set extended ydim size
    ex_nsp = ex_xdim*ex_ydim; // calculate total size of 2D pointer

    //1. Set original siteSpin 1D pointer array

    siteSpin =  (int *)malloc((nsp+1)*sizeof(int)); // 1D pointer dynamic allocation
    ex_siteSpin = (int *)malloc((ex_nsp+1)*sizeof(int)); // 1D pointer dynamic allocation

    for(int i = 1 ; i <= nsp; i++) // Store sequential numbers to the siteSpin array
    siteSpin[i] = i; 
    
    for(int i = 1 ; i <= ex_nsp; i++) //initicalize ex_siteSpin array to 0
    ex_siteSpin[i] = 0; 
   
    //2. Set a 1D array((xdim+2)*(ydim+2) surrounding siteSpin
    ct = 1;
    for(int i= 0; i<ex_ydim-2; i++){ //Fill in the siteSpin value inside the ex_siteSpin
        for(int j = 0; j < ex_xdim-2 ; j++){
            ex_ct = ex_xdim*i+j+(ex_xdim+2); // Search the ID in the shell sequentially
            ex_siteSpin[ex_ct] = siteSpin[ct];
            ct++;
        }
    }

    //3. Fill the elements of the shell (3 times way)
    // 1) Fill in the top and bottom value inside the ex_siteSpin
    for(int i = 2; i < ex_xdim; i++){ 
        ex_siteSpin[i] = siteSpin[xdim*(ydim-1)+i-1];
        ex_siteSpin[ex_xdim*(ex_ydim-1)+i] = siteSpin[i-1];
    }   
    // 2) Fill in the left and right value inside the ex_siteSpin
    for(int j = 1;j < ex_ydim-1; j++){ 
        ex_siteSpin[ex_xdim*j+1] = siteSpin[xdim*j];
        ex_siteSpin[ex_xdim*(j+1)] = siteSpin[xdim*(j-1)+1];
    }   

    // 3) Fill in the edge value inside the ex_siteSpin
    ex_siteSpin[1] = siteSpin[nsp];
    ex_siteSpin[ex_xdim] = siteSpin[xdim*(ydim-1)+1];
    ex_siteSpin[ex_xdim*(ex_ydim-1)+1] = siteSpin[xdim];
    ex_siteSpin[ex_nsp] = siteSpin[1];


    csite = 1; //set the csite value
    // 4. Use neigh array in print_neigh function 
    // Looping as much as the size of siteSpin. 
    for(int yc = 0 ; yc <ex_ydim-2; yc++){
        for(int xc = 0 ; xc < ex_xdim-2; xc++){
            ex_ct = ex_xdim*yc+xc+(ex_xdim+2); // Order of siteSpin in ex_sitespin
            print_neigh(ex_siteSpin,ex_ct,ex_xdim,csite); 
            csite++;
        }
    }

    free(siteSpin); // release siteSpin dynamic allocation
    free(ex_siteSpin); //release ex_siteSpin dynamic allocation
    return 0;
}   

void print_neigh(int *ex_siteSpin,int cur_dic, int ex_xdim, int csite){

    int mov_dic[8]={1,-ex_xdim+1,-ex_xdim,-ex_xdim-1,-1,ex_xdim-1,ex_xdim,ex_xdim+1}; 
    //Set next moving_direction 

    /*
    n-x_dim-1 <- n-x_dim	<-  n-x_dim+1
    v   n-1	       n(start)	->     n+1  ^
    n+x_dim-1 -> n+x_dim    ->   n+x_dim+1
    */

    int neigh[8]; //Set neigh array

    printf("\n%s %d %s\n","Selected site:",csite,"(csite)");

    for(int j = 0; j<8 ; j++){ //It searches 8 directions sequentially and puts them into the neigh array.
        neigh[j] = ex_siteSpin[cur_dic+mov_dic[j]];  
    }

    //print neigh value
    printf("neigh[4] neigh[3] neigh[2]\n");
    printf("  %d        %d       %d\n",neigh[3],neigh[2],neigh[1]);
    printf("neigh[5] csite    neigh[1]\n");
    printf("  %d        %d       %d\n",neigh[4],csite,neigh[0]);
    printf("neigh[6] neigh[7] neigh[8]\n");
    printf("  %d        %d       %d\n",neigh[5],neigh[6],neigh[7]);

    }

