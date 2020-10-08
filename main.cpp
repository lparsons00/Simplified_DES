#include <cstdlib>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;

void keyFunctions(int key[10], int k1[8], int k2[8]){
    int tmpHold;
    int key1[10];
    int key2[10];
    //P10 3,5,2,7,4,10,1,9,8,6
    key1[0] = key[2];
    key1[1] = key[4];
    key1[2] = key[1];
    key1[3] = key[6];
    key1[4] = key[3];
    key1[5] = key[9];
    key1[6] = key[0];
    key1[7] = key[8];
    key1[8] = key[7];
    key1[9] = key[5];
    
    
    
    //LS1
    tmpHold = key1[0];
    key1[0] = key1[1];
    key1[1] = key1[2];
    key1[2] = key1[3];
    key1[3] = key1[4];
    key1[4] = tmpHold;
    tmpHold = key1[5];
    key1[5] = key1[6];
    key1[6] = key1[7];
    key1[7] = key1[8];
    key1[8] = key1[9];
    key1[9] = key1[5];

    for(int i = 0; i < 10; i++){
        key[i] = key1[i];
    }
    
    //P8 6,3,7,4,8,5,10,9
    key1[0] = key[5];
    key1[1] = key[2];
    key1[2] = key[6];
    key1[3] = key[3];
    key1[4] = key[7];
    key1[5] = key[4];
    key1[6] = key[9];
    key1[7] = key[8];
    
    
    for(int i = 0; i < 8; i++){
        k1[i] = key1[i];
    }
    
    //LS2
    key2[0] = key[2];
    key2[1] = key[3];
    key2[2] = key[4];
    key2[3] = key[0];
    key2[4] = key[1];
    key2[5] = key[7];
    key2[6] = key[8];
    key2[7] = key[9];
    key2[8] = key[5];
    key2[9] = key[6];  
    
    //P8 6,3,7,4,8,5,10,9
    key[0] = key2[5];
    key[1] = key2[2];
    key[2] = key2[6];
    key[3] = key2[3];
    key[4] = key2[7];
    key[5] = key2[4];
    key[6] = key2[9];
    key[7] = key2[8];
    
    for(int i = 0; i < 8; i++){
        k2[i] = key[i];
    }
}


int main(int argc, char** argv) {
    int choiceOfProgram = -1;
    int characters[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int key[10];
    int IP[8], EP[8];
    int tempHolder, row, col;
    int k1[8], k2[8];
    int S0[4][4] = {{1,0,3,2}, {3,2,1,0}, {0,2,1,3}, {3,1,3,2}};
    int S1[4][4] = {{0,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3}};
    
    //input choice of either encryption or decryption
    cout << "Input 1 for encryption, 0 for decryption:" << endl;
    cin >> choiceOfProgram;

    //input the plain text to be processed
    cout << "Input characters to be processed:" << endl;
    for(int i = 0; i < 8; i++){
        cout << "Bit number " << i << ": "<< endl;
        cin >> tempHolder;
        characters[i] = tempHolder;
    }
    
    //input the bits for the key
    cout << "Input key bits:" << endl;
    for(int i = 0; i < 10; i++){
        cout << "Bit number " << i << ": "<< endl;
        cin >> tempHolder;
        key[i] = tempHolder;
    }
    
    
    keyFunctions(key, k1, k2);
    
    
    
    if(choiceOfProgram == 1){
        //encryption 
        //plaintext: IP [2,6,3,1,4,8,5,7]
        IP[0] = characters[1];
        IP[1] = characters[5];
        IP[2] = characters[2];
        IP[3] = characters[0];
        IP[4] = characters[3];
        IP[5] = characters[7];
        IP[6] = characters[4];
        IP[7] = characters[6];
        
        for(int i = 0; i < 8; i++){
            characters[i] = IP[i];
        }
        
        //EP [4,1,2,3,2,3,4,1]
        EP[0] = characters[7];
        EP[1] = characters[4];
        EP[2] = characters[5];
        EP[3] = characters[6];
        EP[4] = characters[5];
        EP[5] = characters[6];
        EP[6] = characters[7];
        EP[7] = characters[4];
        
        //XOR
        for(int i = 0; i < 8; i++){
            if(EP[i] == k1[i]){
                EP[i] = 0;
            } else {
                EP[i] = 1;
            }
        }
            
        
        //S0
        //get bit 1 & 4 for row
        if(EP[0] == 0){
            if(EP[3] == 0){
                row = 0;
            } else if(EP[3] == 1){
                row = 1;
            }
        } else if(EP[0] == 1){
            if(EP[3] == 0){
                row = 2;
            } else if(EP[3] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[1] == 0){
            if(EP[2] == 0){
                col = 0;
            } else if(EP[2] == 1){
                col = 1;
            }
        } else if(EP[1] == 0){
            if(EP[2] == 0){
                col = 2;
            } else if(EP[2] == 1){
                col = 3;
            }
        }
        
        tempHolder = S0[row][col];
        if(tempHolder == 0){
            EP[0] = 0;
            EP[1] = 0;
        } else if(tempHolder == 1){
            EP[0] = 0;
            EP[1] = 1;
        } else if(tempHolder == 2){
            EP[0] = 1;
            EP[1] = 0;
        } else {
            EP[0] = 1;
            EP[1] = 1;
        }
        
        
        //S1
        //get bit 1 & 4 for row
        if(EP[4] == 0){
            if(EP[7] == 0){
                row = 0;
            } else if(EP[7] == 1){
                row = 1;
            }
        } else if(EP[4] == 1){
            if(EP[7] == 0){
                row = 2;
            } else if(EP[7] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[5] == 0){
            if(EP[6] == 0){
                col = 0;
            } else if(EP[6] == 1){
                col = 1;
            }
        } else if(EP[5] == 0){
            if(EP[6] == 0){
                col = 2;
            } else if(EP[6] == 1){
                col = 3;
            }
        }
        
        tempHolder = S1[row][col];
        if(tempHolder == 0){
            EP[2] = 0;
            EP[3] = 0;
        } else if(tempHolder == 1){
            EP[2] = 0;
            EP[3] = 1;
        } else if(tempHolder == 2){
            EP[2] = 1;
            EP[3] = 0;
        } else {
            EP[2] = 1;
            EP[3] = 1;
        }
        
        
        //P4 [1,3,2,0]
        tempHolder = EP[0];
        EP[0] = EP[1];
        EP[1] = EP[3];
        EP[3] = tempHolder;
        EP[2] = EP[2];
        
              
        //XOR of IP[0-3] & EP[0-3]
        for(int i = 0; i < 4; i++){
            if(EP[i] == IP[i]){
                IP[i] = 0;
            } else {
                IP[i] = 1;
            }
        }
         
        //swap the two halves
        tempHolder = IP[0];
        IP[0] = IP[4];
        IP[4] = tempHolder;
        tempHolder = IP[1];
        IP[1] = IP[5];
        IP[5] = tempHolder;
        tempHolder = IP[2];
        IP[2] = IP[6];
        IP[6] = tempHolder;
        tempHolder = IP[3];
        IP[3] = IP[7];
        IP[7] = tempHolder;              
        
        //EP [4,1,2,3,2,3,4,1]
        EP[0] = IP[7];
        EP[1] = IP[4];
        EP[2] = IP[5];
        EP[3] = IP[6];
        EP[4] = IP[5];
        EP[5] = IP[6];
        EP[6] = IP[7];
        EP[7] = IP[4];
        
        //XOR
        for(int i = 0; i < 8; i++){
            if(EP[i] == k2[i]){
                EP[i] = 0;
            } else {
                EP[i] = 1;
            }
        }
        
         
        //S0
        //get bit 1 & 4 for row
        if(EP[0] == 0){
            if(EP[3] == 0){
                row = 0;
            } else if(EP[3] == 1){
                row = 1;
            }
        } else if(EP[0] == 1){
            if(EP[3] == 0){
                row = 2;
            } else if(EP[3] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[1] == 0){
            if(EP[2] == 0){
                col = 0;
            } else if(EP[2] == 1){
                col = 1;
            }
        } else if(EP[1] == 0){
            if(EP[2] == 0){
                col = 2;
            } else if(EP[2] == 1){
                col = 3;
            }
        }
        
        tempHolder = S0[row][col];
        if(tempHolder == 0){
            EP[0] = 0;
            EP[1] = 0;
        } else if(tempHolder == 1){
            EP[0] = 0;
            EP[1] = 1;
        } else if(tempHolder == 2){
            EP[0] = 1;
            EP[1] = 0;
        } else {
            EP[0] = 1;
            EP[1] = 1;
        }
        
        //S1
        //get bit 1 & 4 for row
        if(EP[4] == 0){
            if(EP[7] == 0){
                row = 0;
            } else if(EP[7] == 1){
                row = 1;
            }
        } else if(EP[4] == 1){
            if(EP[7] == 0){
                row = 2;
            } else if(EP[7] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[5] == 0){
            if(EP[6] == 0){
                col = 0;
            } else if(EP[6] == 1){
                col = 1;
            }
        } else if(EP[5] == 1){
            if(EP[6] == 0){
                col = 2;
            } else if(EP[6] == 1){
                col = 3;
            }
        }
        
        tempHolder = S1[row][col];
        if(tempHolder == 0){
            EP[2] = 0;
            EP[3] = 0;
        } else if(tempHolder == 1){
            EP[2] = 0;
            EP[3] = 1;
        } else if(tempHolder == 2){
            EP[2] = 1;
            EP[3] = 0;
        } else {
            EP[2] = 1;
            EP[3] = 1;
        }
        
        
        for(int i = 0; i<8;i++){
            cout << EP[i] <<endl;
        }
        //P4 [1,3,2,0]
        tempHolder = EP[0];
        EP[0] = EP[1];
        EP[1] = EP[3];
        EP[3] = tempHolder;
        
        //XOR of IP[0-3] & EP[0-3]
        for(int i = 0; i < 4; i++){
            if(EP[i] == IP[i]){
                IP[i] = 0;
            } else {
                IP[i] = 1;
            }
        }
        
        //inverse IP permutation [3,0,2,4,6,1,7,5]
        tempHolder = IP[1];
        IP[1] = IP[0];
        IP[0] = IP[3];
        IP[3] = IP[4];
        IP[4] = IP[6];
        IP[6] = IP[7];
        IP[7] = IP[5];
        IP[5] = tempHolder;
       
       
        cout << "\n\n CIPHER TEXT:\n";
        for(int i = 0; i < 8; i++){
            cout << IP[i];
        }
    } else if(choiceOfProgram == 0){
        //decryption 
        //plaintext: IP [2,6,3,1,4,8,5,7]
        IP[0] = characters[1];
        IP[1] = characters[5];
        IP[2] = characters[2];
        IP[3] = characters[0];
        IP[4] = characters[3];
        IP[5] = characters[7];
        IP[6] = characters[4];
        IP[7] = characters[6];
        
        for(int i = 0; i < 8; i++){
            characters[i] = IP[i];
        }
        
        //EP [4,1,2,3,2,3,4,1]
        EP[0] = characters[7];
        EP[1] = characters[4];
        EP[2] = characters[5];
        EP[3] = characters[6];
        EP[4] = characters[5];
        EP[5] = characters[6];
        EP[6] = characters[7];
        EP[7] = characters[4];
        
        //XOR
        for(int i = 0; i < 8; i++){
            if(EP[i] == k2[i]){
                EP[i] = 0;
            } else {
                EP[i] = 1;
            }
        }
        
        //S0
        //get bit 1 & 4 for row
        if(EP[0] == 0){
            if(EP[3] == 0){
                row = 0;
            } else if(EP[3] == 1){
                row = 1;
            }
        } else if(EP[0] == 1){
            if(EP[3] == 0){
                row = 2;
            } else if(EP[3] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[1] == 0){
            if(EP[2] == 0){
                col = 0;
            } else if(EP[2] == 1){
                col = 1;
            }
        } else if(EP[1] == 0){
            if(EP[2] == 0){
                col = 2;
            } else if(EP[2] == 1){
                col = 3;
            }
        }
        
        tempHolder = S0[row][col];
        if(tempHolder == 0){
            EP[0] = 0;
            EP[1] = 0;
        } else if(tempHolder == 1){
            EP[0] = 0;
            EP[1] = 1;
        } else if(tempHolder == 2){
            EP[0] = 1;
            EP[1] = 0;
        } else {
            EP[0] = 1;
            EP[1] = 1;
        }
        
        //S1
        //get bit 1 & 4 for row
        if(EP[4] == 0){
            if(EP[7] == 0){
                row = 0;
            } else if(EP[7] == 1){
                row = 1;
            }
        } else if(EP[4] == 1){
            if(EP[7] == 0){
                row = 2;
            } else if(EP[7] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[5] == 0){
            if(EP[6] == 0){
                col = 0;
            } else if(EP[6] == 1){
                col = 1;
            }
        } else if(EP[5] == 1){
            if(EP[6] == 0){
                col = 2;
            } else if(EP[6] == 1){
                col = 3;
            }
        }
        
        tempHolder = S1[row][col];
        if(tempHolder == 0){
            EP[2] = 0;
            EP[3] = 0;
        } else if(tempHolder == 1){
            EP[2] = 0;
            EP[3] = 1;
        } else if(tempHolder == 2){
            EP[2] = 1;
            EP[3] = 0;
        } else {
            EP[2] = 1;
            EP[3] = 1;
        }
        
        
        for(int i = 0; i<8;i++){
            cout << EP[i] <<endl;
        }
        //P4 [1,3,2,0]
        tempHolder = EP[0];
        EP[0] = EP[1];
        EP[1] = EP[3];
        EP[3] = tempHolder;
        
        //XOR of IP[0-3] & EP[0-3]
        for(int i = 0; i < 4; i++){
            if(EP[i] == IP[i]){
                IP[i] = 0;
            } else {
                IP[i] = 1;
            }
        }
        //swap the two halves
        tempHolder = IP[0];
        IP[0] = IP[4];
        IP[4] = tempHolder;
        tempHolder = IP[1];
        IP[1] = IP[5];
        IP[5] = tempHolder;
        tempHolder = IP[2];
        IP[2] = IP[6];
        IP[6] = tempHolder;
        tempHolder = IP[3];
        IP[3] = IP[7];
        IP[7] = tempHolder;              
        
        //EP [4,1,2,3,2,3,4,1]
        EP[0] = IP[7];
        EP[1] = IP[4];
        EP[2] = IP[5];
        EP[3] = IP[6];
        EP[4] = IP[5];
        EP[5] = IP[6];
        EP[6] = IP[7];
        EP[7] = IP[4];
        
        //XOR
        for(int i = 0; i < 8; i++){
            if(EP[i] == k1[i]){
                EP[i] = 0;
            } else {
                EP[i] = 1;
            }
        }
        
         
        //S0
        //get bit 1 & 4 for row
        if(EP[0] == 0){
            if(EP[3] == 0){
                row = 0;
            } else if(EP[3] == 1){
                row = 1;
            }
        } else if(EP[0] == 1){
            if(EP[3] == 0){
                row = 2;
            } else if(EP[3] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[1] == 0){
            if(EP[2] == 0){
                col = 0;
            } else if(EP[2] == 1){
                col = 1;
            }
        } else if(EP[1] == 0){
            if(EP[2] == 0){
                col = 2;
            } else if(EP[2] == 1){
                col = 3;
            }
        }
        
        tempHolder = S0[row][col];
        if(tempHolder == 0){
            EP[0] = 0;
            EP[1] = 0;
        } else if(tempHolder == 1){
            EP[0] = 0;
            EP[1] = 1;
        } else if(tempHolder == 2){
            EP[0] = 1;
            EP[1] = 0;
        } else {
            EP[0] = 1;
            EP[1] = 1;
        }
        
        //S1
        //get bit 1 & 4 for row
        if(EP[4] == 0){
            if(EP[7] == 0){
                row = 0;
            } else if(EP[7] == 1){
                row = 1;
            }
        } else if(EP[4] == 1){
            if(EP[7] == 0){
                row = 2;
            } else if(EP[7] == 1){
                row = 3;
            }
        }
        //get bit 2 & 3 for col
        if(EP[5] == 0){
            if(EP[6] == 0){
                col = 0;
            } else if(EP[6] == 1){
                col = 1;
            }
        } else if(EP[5] == 1){
            if(EP[6] == 0){
                col = 2;
            } else if(EP[6] == 1){
                col = 3;
            }
        }
        
        tempHolder = S1[row][col];
        if(tempHolder == 0){
            EP[2] = 0;
            EP[3] = 0;
        } else if(tempHolder == 1){
            EP[2] = 0;
            EP[3] = 1;
        } else if(tempHolder == 2){
            EP[2] = 1;
            EP[3] = 0;
        } else {
            EP[2] = 1;
            EP[3] = 1;
        }
        
        
        for(int i = 0; i<8;i++){
            cout << EP[i] <<endl;
        }
        //P4 [1,3,2,0]
        tempHolder = EP[0];
        EP[0] = EP[1];
        EP[1] = EP[3];
        EP[3] = tempHolder;
        
        //XOR of IP[0-3] & EP[0-3]
        for(int i = 0; i < 4; i++){
            if(EP[i] == IP[i]){
                IP[i] = 0;
            } else {
                IP[i] = 1;
            }
        }
        
        //inverse IP permutation [3,0,2,4,6,1,7,5]
        tempHolder = IP[1];
        IP[1] = IP[0];
        IP[0] = IP[3];
        IP[3] = IP[4];
        IP[4] = IP[6];
        IP[6] = IP[7];
        IP[7] = IP[5];
        IP[5] = tempHolder;
       
       
        cout << "\n\n ORIGINAL TEXT:\n";
        for(int i = 0; i < 8; i++){
            cout << IP[i];
        }
        
        
    }
    return 0;
}


