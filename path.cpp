#include <iostream>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

//test for reading file
    // for(int k=0;k<row;k++){
    //     for (int l=0;l<col;l++){
    //         std::cout << grid[row*k+l];
    //     }
    //     std::cout<< " " <<std::endl;
    // }
void getArray (int *grid,char *fname, int r, int c){

    /*opens file and creates reader*/
    std::ifstream infile;
    infile.open(fname);

    //counters to help adding to grid
    int i=0;
    int j=0;

    /*To read from a file element by element, it is helpful to have somewhere to hold the value read before you assign it to anything*/
    int val;

    // While there is still something to read, stores it in val and prints it
    // (If you did this at the start, you could process the entire file this way, start to finish)
    while(infile.good()) {
        infile >> val;

        //add to grid
        grid[c * i + j] = val;

        //increment counter and reset if row is filled
        j++;
        if (j == c){
            j= 0;
            i++;
        }
    }
    infile.close();

}

bool ingrid(int x, int y,int r,int c){
    if (x < 0 || x == r || y <0 || y == c){
        return false;
    }
    return true;
}

bool find(int* grid,int r, int c,int lx,int ly ,int hx,int hy,int* Tgrid){

    //if the path is found return true
    if(lx ==hx && ly == hy){
        return true;
    }

    //if off grid return false
    if(!ingrid(lx,ly,r,c)){
        return false;
    }


        //mark as traversed
        Tgrid[c*lx+ly] = 1;

        //replace last with current num
        //*last = grid[c*lx+ly];

        if (Tgrid[c*lx+(ly-1)] ==0 && grid[c*lx+(ly-1)] >= grid[c*lx+ly] ){
            //check left
            if (find(grid,r,c,lx,ly-1,hx,hy,Tgrid)){
                return true;
            }
        }

        if (Tgrid[c*(lx-1)+ly] ==0 && grid[c*(lx-1)+ly] >= grid[c*lx+ly]){
            //check up
            if (find(grid,r,c,lx-1,ly,hx,hy,Tgrid)){
                return true;
            }
        }

        if (Tgrid[c*lx+(ly+1)] ==0 && grid[c*lx+(ly+1)] >= grid[c*lx+ly]){
            //check right
            if (find(grid,r,c,lx,ly+1,hx,hy,Tgrid)){
                return true;
            }
        }

        if (Tgrid[c*(lx+1)+ly] == 0 && grid[c*(lx+1)+ly] >= grid[c*lx+ly]){
            //check down
            if (find(grid,r,c,lx+1,ly,hx,hy,Tgrid) == true){
                return true;
            }
        }
    //}
    return false;
}


int main(int argc, char *argv[]) {
    //get rows from arguements
    int r = atoi(argv[2]);
    int c = atoi(argv[3]);

    //initialize grid
    int *grid = new int[r*c];

    //initialize tracking grid
    int *Tgrid = new int[r*c];

    //add to grid
    getArray(grid,argv[1],r,c);

    //initialize max,min, and their indexes
    int min = grid[0];
    int max = grid[0];
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    //get min and max indexes
    for(int k=0;k<r;k++){
        for (int l=0;l<c;l++){
            if(grid[c*k+l] > max){
                max = grid[r*k+l];
                maxX = k;
                maxY = l;
            }
            if(grid[c*k+l] < min){
                min = grid[r*k+l];
                minX = k;
                minY = l;
            }
        }
    }
    //stores last value
    int last = grid[c*minX+minY];

    //function call
    bool found = find(grid,r,c,minX,minY,maxX,maxY,Tgrid);

    //if path found print coordinates and yes
    if (found == 1){
        std::cout << minX+1 << " ";
        std::cout << minY+1 << " ";

        std::cout << maxX+1 << " ";
        std::cout << maxY+1 << " ";
        std::cout << "yes" << std::endl;
    }

    //if path not found print coordinates and no
    else{
        std::cout << minX+1 << " ";
        std::cout << minY+1 << " ";

        std::cout << maxX+1 << " ";
        std::cout << maxY+1 << " ";
        std::cout << "no" << std::endl;
    }

    delete [] grid;
    delete [] Tgrid;
    return 0;
}
