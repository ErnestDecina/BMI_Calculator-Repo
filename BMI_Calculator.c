/*
Program Desc: BMI Calculator with(Encrytion, File Saving, Admin Saving)
Author: Ernest John Decina
Date: 3rd February 2022
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Symbolic Names
#define ROWS 1
#define NAME_SIZE 256
#define LINE_SIZE 256
#define PASSWORD_SIZE 512

// Function Signatures
void File_Input(int);
int Admin_Check(char [], char []);
long long polynomialRollingHash(char *);
void clear_buffer(void);

// Main Function
int main()
{
    // Vars
    int menu_status = 1;
    int admin_menu = 0;
    char admin_name[NAME_SIZE];
    char admin_password[PASSWORD_SIZE];
    int option;
    int num_of_people = 0;
    

    // File Var's
    FILE *ptr_file;
    ptr_file = fopen("Assets/Test.csv", "r");

    // Checking if File exists
    if(ptr_file == NULL)
    {
        printf("\nFile does not exists, Creating new file.");
        ptr_file = fopen("Assets/Test.csv", "w");
        fprintf(ptr_file,"Name,Weight,Height,BMI\n");

    } // End if
    else
    {
        printf("\nFile found");
    } // End else

    fclose(ptr_file);

    // Admin User Password
    do
    {
        printf("\nEnter User Name:");
        fgets(admin_name, NAME_SIZE, stdin);

        printf("\nEnter Password:");
        fgets(admin_password, PASSWORD_SIZE, stdin);

        // Checking if Password and User Name is Correct
        admin_menu = Admin_Check(admin_name, admin_password);
        

    } while (admin_menu == 1);
    


    // Menu
    do
    {
        // Asking User for Menu Option
        printf("\n1.Reading Information.");
        printf("\n2.Writing Information.");
        printf("\n3.Exit Program.");
        printf("\n\nChoose an Option:");
        
        scanf(" %d", &option);

        // Check option
        switch (option)
        {
            case 1:
            {
                // Call Function


                break;
            } // End case

            case 2:
            {
                // Call Function
                printf("\nEnter amount of people:");
                scanf("%d", &num_of_people);

                File_Input(num_of_people);
                
                break;
            } // End case

            case 3:
            {
                // Call Function

                // End Program
                menu_status = 0;

                break;
            } // End case
        
            default:
            {
                printf("\nInvalid Input, please try again:");
                scanf("%c", &option);
                break;

            } // End default

        } // End Switch


    } while (menu_status == 1);
    


    // End main
    return 0;

} // End main

// Functions
//
// start int File_Input(void)
void File_Input(int num)
{
    // Vars
    FILE *ptr_Input;
    ptr_Input = fopen("Assets/Test.csv", "a+");
    char input_name[NAME_SIZE];
    float input_weight = 0;
    float input_height = 0;
    float bmi_calculation;

    // test
    printf("\nEntered Function");
    
    
    // Allocating Memory
    //input_name = malloc(num);

    // Memory Checking
    /*
    while(input_name == NULL)
    {
        printf("\nFailed to allocate Memory, Retrying...");
        input_name = malloc(num);

    } // End if
    */

    // Entering Data into CSV File
    for(register int j = 0; j < num; j++)
    {   
        printf("\nEnter Name:"); 
        clear_buffer();
        scanf("%[^\n]s", input_name);
        //fgets(input_name, NAME_SIZE - 1, stdin);
        
        printf("\nEnter Weight in KG:");
        clear_buffer();
        scanf("%f", &input_weight);

        printf("\nEnter Height in Meters:");
        clear_buffer();
        scanf("%f", &input_height);

        // BMI Calculation
        bmi_calculation = input_height / (input_height * input_height);

        fprintf(ptr_Input, "%s,%f,%f,%f\n",  input_name, input_weight, input_height, bmi_calculation);
    } // End For

    // Clearing Memory
    fclose(ptr_Input);

} // End File_Input()

// Check if Admin Pass is correct
int Admin_Check(char adminCheck[], char passwordCheck[])
{
    long long Admin_hash = 542792750;
    long long Password_hash = 921174685;
    
    if((Admin_hash == polynomialRollingHash(adminCheck)) && (Password_hash == polynomialRollingHash(passwordCheck)))
    {
        return 0;
    } // End if
    else
    {
        return 1;
    } // End else


} // End Admin_Check([], [])

// Hashing Function
// Replacing, Place holder only
long long polynomialRollingHash(char *str)
{
    // P and M
    int p = 31;
    int m = 1e9 + 9;
    long long power_of_p = 1;
    long long hash_val = 0;
 
    // Loop to calculate the hash value
    // by iterating over the elements of string
    for (int i = 0; i < strlen(str); i++) 
    {
        hash_val
            = (hash_val
               + (str[i] - 'a' + 1) * power_of_p)
              % m;
        power_of_p
            = (power_of_p * p) % m;
    }
   
    //return positive remainder only
    return (hash_val%m + m) % m;
} // End polynomialRollingHash(char *)

// Start void clear_buffer(void)
void clear_buffer(void)
{
    while (getchar() != '\n');
} // End void clear_buffer(void)