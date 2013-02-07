/*Program to play the Lotto game. The program allows a user to enter their 6 selected main 
numbers & a bonus number and gives them a set of options, each performing a specific 
requirement.  The 6 main numbers are stored in a 1-Dimensional array & the bonus number in a 
separate variable.
Author:  Sam Coffey
Date: 25/02/2012
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MAIN 6
#define RANGE 42


/*Define function prototypes*/
void menu(int *, int *, char *);
void choose(int *, int *, int *, char *, int *);
void display(int *, int *);
void sort(int *);
void compare(int *, int *);
void frequency(int *, int*, int *, int *);
void exit(char *);

main()
{
    int main_nos[MAIN] = {0};
    int bonus;
    char play = 'n';
    int selection;
    int error = 0;
    static int total_nums[RANGE];
    char str[10];
    
    /*Call function menu()
    */
    menu(&error, &selection, str);
    
    /*Error check: Makes sure the user enters option 1 1st
    */
    
    while(play == 'n' && selection != 6)
    {
        if(selection == 1)
        {
            play = 'y';
            /*Call function choose()
            total_nums & selection are passed to choose(), because frequency() is
            called in choose() and it uses this array & variable
            */
            choose(main_nos, &bonus, total_nums, str, &selection);
        }
        else
        {
            /*Error check: Makes sure the user enters option 1 1st
            */
            error = 1;
            /*Call function selection
            */
            menu(&error, &selection, str);
        }
    }
    
    if(selection == 6)
    {
        /*Call function exit
        */
        exit(&play);
    }
    
    while(play == 'y')
    {
        /*Call function menu()
        */
        menu(&error, &selection, str);
        
        //Call functions depending on selection
        
        if(selection == 1)
        {
            /*Call function choose()
            */
            choose(main_nos, &bonus, total_nums, str, &selection);
        }
        else if(selection == 2)
        {
            /*Call function display()
            */
            display(main_nos, &bonus);
        }
        else if(selection == 3)
        {
            /*Call function sort()
            */
            sort(main_nos);
        }
        else if(selection == 4)
        {
            /*Call function compare()
            */
            compare(main_nos, &bonus);
        }
        else if(selection == 5)
        {
            /*Call function frequency()
            */
            frequency(main_nos, &bonus, total_nums, &selection);
        }
        else if(selection == 6)
        {
            /*Call function exit
            */
            exit(&play);
        }
        
    }
    
    getch();
    
} //end main()

/*Implement function menu()
*/

void menu(int *ptr, int *sel, char *str)
{
    system("cls");
    
    /*Error check: Makes sure the user enters Option 1 1st
    */
    
    if(*ptr == 1)
    {
        printf("ERROR: You must select option 1 before selecting options 2, 3, 4 or 5");
    }
    
    //print front screen
    
    printf("                              Welcome to Lotto Game\n");
    printf("********************************************************************************\n\n\n");
    printf("To play please enter 1 to select option 1 first and then pick any of the other 5\noptions.\n\n");
    printf("1. Choose your numbers\n\n");
    printf("2. Display your choice\n\n");
    printf("3. Sort your numbers in ascending order\n\n");
    printf("4. Find out if you're a winner\n\n");
    printf("5. Display the frequency of all numbers chosen since you began playing\n\n");
    printf("6. Exit game\n\n\n");
    
    printf("Enter your selection: ");
    //Reads user entry to the string 'str' in order to avoid infinite loop when a character is entered
    gets(str);
    /*Function atoi() from stdlib.h used to convert a number entered in a string to an integer. Below
    This int value is assigned to the pointer integer variable *sel
    */
    *sel = atoi(str);
    
    while(*sel < 1 || *sel > 6)
    {
        printf("Invalid entry. Please enter a number from the range 1 - 6\n");
        //Reads user entry to the string 'str' in order to avoid infinite loop when a character is entered
        gets(str);
        /*Function atoi() from stdlib.h used to convert a number entered in a string to an integer. Below
        this int value is assigned to the pointer integer variable *sel
        */
        *sel = atoi(str);
    }
    
    *ptr = 0;
    
} //end menu()


/*Implement function choose()
*/

void choose(int *array, int *ptr, int *tot_nums, char *str, int *sel)
{
    system("cls");
    
    int i, j;
    
    //Resets all elements of the array to zero every time the function is called
    for(i = 0; i < MAIN; i++)
    {
        *(array + i) = 0;
    }
    
    /*Read in the 6 main numbers
    */
    
    for(i = 0; i < MAIN; i++)
    {
        printf("Please enter number %d from the range 1 - 42:\n", i + 1);
        //Reads user entry to the string 'str' in order to avoid infinite loop when a character is entered
        gets(str);
        /*Function atoi() from stdlib.h used to convert a number entered in a string to an integer. Below
        this int value is assigned to *(array + i)
        */
        *(array + i) = atoi(str);
        
        /*Error check: Make sure the number has not already been entered and is between the range 1 - 42
        */
        
        for(j = 0; j < MAIN; j++)
        {
            if(i != j) //Don't check a number against itself
            {
                while(*(array + i) == *(array +j) || *(array + i) < 1 || *(array + i) > 42)
                {
                    printf("Invalid choice. Please enter a number you have not already chosen that is \nbetween 1 and 42:\n");
                    //Reads user entry to the string 'str' in order to avoid infinite loop when a character is entered
                    gets(str);
                    /*Function atoi() from stdlib.h used to convert a number entered in a string to an integer. Below
                    this int value is assigned to *(array + i)
                    */
                    *(array + i) = atoi(str);
                } //end while()
            } //end if()
        } //end inner for()
        
    } //end outer for()
    
    /*Read in the bonus number
        */
    
    printf("Please enter the bonus number:\n");
    //Reads user entry to the string 'str' in order to avoid infinite loop when a character is entered
    gets(str);
    /*Function atoi() from stdlib.h used to convert a number entered in a string to an integer. Below
    this int value is assigned to the pointer integer variable *ptr
        */
    *ptr = atoi(str);
    
    /*Error check: Make sure the number has not already been entered and is between the range 1 - 42
    */
    
    for(i = 0; i < MAIN; i++)
    {
        while(*ptr == *(array +i) || *ptr < 1 || *ptr > 42)
        {
            printf("Invalid choice. Please enter a number you have not already chosen that is \nbetween 1 and 42:\n");
            //Reads user entry to the string 'str' in order to avoid infinite loop when a character is entered
            gets(str);
            /*Function atoi() from stdlib.h used to convert a number entered in a string to an integer. Below
            this int value is assigned to the pointer integer variable *ptr
            */
            *ptr = atoi(str);
        } //end while()
    } //end for()
    
    /*Call function frequency(). In order that the frequency of the numbers entered is 
    incremented every time a player chooses a set of numbers, frequency() is called here
    */
    frequency(array, ptr, tot_nums, sel);
    
    
} //end choose()

/*Implement function display()
*/

void display(int *array, int *ptr)
{
    system("cls");
    
    int i;
    
    printf("You have chosen the following numbers: ");
    
    //Print all the elements of the array
    for(i = 0; i < MAIN; i++)
    {
        printf("%d ", *(array +i));
    } //end for()
    
    printf("\nBonus number picked is %d", *ptr);
    
    printf("\n\nPress any key to return to the main menu\n");
    getch();

} //end display()

/*Implement function sort()
*/

void sort(int *array)
{
    system("cls");
    
    int i, j, current;
    
    /*Implementation of insertion sort. Set i = 2nd element in the array as 1st cannot be 
    moved any further towards the start of the array
        */
    for(i = 1; i < MAIN; i++)
    {
        //Assign the value of element i to the variable current
        current = *(array + i);
        /*Assign the value of i to j as all we want to do with i is increment it to run the 
        loop
        */
        j = i;
        
        /*Checks if the value of the element before element j is greater than the value in
        current and that j is greater than 0 before going into the loop. As if it is equal to 0 
        the element before element j will not exist.
        */
        while((*(array + j - 1) > current) && (j > 0))
        {
            //Assigns the value of the element before element j to element j
            *(array + j) = *(array + j - 1);
            /*Decrements j by 1 so we can check if the value in current is less than the
            value of the next element towards the start of the array
            */
            j--;
        } //end while()
        
        /*Assigns the value in current to the place in the array which comes after the 
        element closest to the start of the array that was not larger than current
        */
        *(array + j) = current;
    } //end outer for()
    
    printf("Your numbers have been sorted in ascending order\n\n");
    printf("To view your numbers please select option 2 from the main menu\n\n");
    printf("\n\nPress any key to return to the main menu\n");
    getch();
    
} //end sort

/*Implement function compare()
*/

void compare(int *array, int *ptr)
{
    system("cls");
    
    int draw[6] = {1,3,5,7,9,11};
    int bonus_draw = 42;
    int i, j;
    int win_nums = 0;
    
    //Compare each number in array[] with all numbers in draw[]
    for(i = 0; i < MAIN; i++)
    {
        for(j = 0; j < MAIN; j++)
        {
            if(*(array + i) == *(draw + j))
            {
                win_nums++;
            } //end if()
        } //end inner for()
    } //end outer for()
    
    printf("Numbers drawn: ");
    
    //Print the numbers in draw[]
    for(i = 0; i < MAIN; i++)
    {
        printf("%d ", *(draw + i));
    }
    
    printf("Bonus: %d\n\n", bonus_draw);
    
    //if() statements for losing scenario & every winning scenario 
    if(win_nums == 3 && *ptr != bonus_draw || win_nums < 3)
    {
        printf("Not a winner. Better luck next time.");
    }
    
    if(win_nums == 3 && *ptr == bonus_draw)
    {
        printf("Match 3 + bonus. Free lotto scratch card.");
    }
    
    if(win_nums == 4 && *ptr != bonus_draw)
    {
        printf("Match 4. Full petrol tank.");
    }
    
    if(win_nums == 4 && *ptr == bonus_draw)
    {
        printf("Match 4 + bonus. Night out.");
    }
    
    if(win_nums == 5 && *ptr != bonus_draw)
    {
        printf("Match 5. Holidays paid for.");
    }
    
    if(win_nums == 5 && *ptr == bonus_draw)
    {
        printf("Match 5 + bonus. Almost - Just 1 away.");
    }
    
    if(win_nums == 6)
    {
        printf("Match 6. Jackpot.");
    }
    
    printf("\n\nPress any key to return to the main menu\n");
    getch();
} //end compare()

/*Implement function frequency()
*/

void frequency(int *array, int *ptr, int *tot_nums, int *sel)
{
    int i, j;
    
    /*The if() statement specifies that this section of the function only operates 
    if *sel ==1, i.e. the function has been called in choose()
    */
    if(*sel == 1)
    {
        //Run the loop for every number in the range 1 -42
        for(i = 0; i < RANGE; i++)
        {
            /*Check if the 6 numbers stored in the array are equal to the 
            current value of i generated from the outer loop
            */
            for(j = 0; j < MAIN; j++)
            {
                if(i == *(array + j))
                {
                    /*If one of the numbers is equal to i, element i of 
                    total_nums is incremented by 1.
                    */
                    *(tot_nums + i) = *(tot_nums + i) + 1;
                } //end inner if()
            } //end inner for()
        } //end outer for()
        
        //Run the loop for every number in the range 1 -42
        for(i = 0; i < RANGE; i++)
        {
            /*If the bonus number is equal to i, element i of 
            total_nums is incremented by 1.
            */
            if(i == *ptr)
            {
                *(tot_nums + i) = *(tot_nums + i) + 1;
            } //end inner if()
        } //end for()
    } //end outer if()
    
    /*The if() statement specifies that this section of the function only operates 
    if *sel ==5, i.e. the user has selected to display the frequency of numbers
    entered from the main menu.
    */
    if(*sel == 5)
    {
        system("cls");
        
        int i;
        
        printf("\n\n");
        
        /*For every element in tot_nums that is greater than 0 as implemented 
        above, print the statement in the if() below
        */
        for(i = 0; i < RANGE; i++)
        {
            if(*(tot_nums + i) > 0)
            {
                printf("Number %d has been entered %d times.\n", i, *(tot_nums + i));
            }
        }
        
        printf("\n\nPress any key to return to the main menu\n");
        getch();
    }
    
} //end frequency()

/*Implement function exit()
*/

void exit(char *ptr)
{
    system("cls");
    printf("Goodbye. Thank you for playing Lotto.");
    /*Assigning 'n' to *ptr causes the program to jump out of the last while() in main
    and reach the end of the program
    */
    *ptr = 'n';
} //end exit()