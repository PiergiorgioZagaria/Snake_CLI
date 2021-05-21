#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(){
    char choice;
    system("toilet \"Snake\" -f mono12 -W --filter border --filter gay | sed \'s/^/                                            /\'");    
    while (1){
        printf("\t\t\t\t\t\t\tGo to Settings: S\n");
        printf("\t\t\t\t\t\t\tPrint Leaderboard: L\n");
        printf("\t\t\t\t\t\t\tExit: Q\n");
        printf("\t\t\t\t\t\t\tPlay: P\n");
        scanf("%c",&choice);
        if (choice == 'P'){
            if(main_game()){
                printf("Something went wrong during the game\n");
                return 1;
            }else{
                printf("Going back to main menu\n");
                system("toilet \"Snake\" -f mono12 -W --filter border --filter gay | sed \'s/^/                                            /\'");
            }
        }else if(choice == 'S'){
            printf("Settings not implemented yet\n");
        }else if(choice == 'L'){
            printf("Leaderboard not implemented yet\n");
        }else if(choice == 'Q'){
            printf("Thank you for playing 😄\n");
            break;
        }
    }
    return 0;
}
