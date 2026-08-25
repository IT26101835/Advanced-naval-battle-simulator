#include <stdlib.h>

int GenerateRandomCoordinate(int d){ // generate random coordinate function 
    return rand() % (d+1);
};

char GenerateRandomEscortType(){ // generate random type function
    int randomtype = rand() % 5; 

    if (randomtype == 0){
        return 'A'; // return value
    }
    else if (randomtype == 1){
        return 'B';
    }
    else if (randomtype == 2){
        return 'C';
    }
    else if (randomtype == 3){
        return 'D';
    }
    else{
        return 'E';
    }
}
