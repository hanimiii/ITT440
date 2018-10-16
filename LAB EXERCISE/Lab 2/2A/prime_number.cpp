#include<iostream>
#include<stdio.h>
void load_menu(void);
void sum(void);
void rest(void); 

main()
{
   int n, c = 2;
   int choice;
 
   printf("\n");
   printf("Enter a number to check if it is prime\n");
   scanf("%d",&n);
 
   for ( c = 2 ; c <= n - 1 ; c++ )
   {
      if ( n%c == 0 )
      {
      	 printf("\n");
         printf("%d isn't a prime number.\n", n);
    break;
      }
      
   if ( n%c != 0 )
      printf("\n");
      printf("%d is a prime number.\n", n);
      
      do
    {
    	printf("\n");
        printf("Menu\n\n");
        printf("\n");
        printf("1. Sum\n");
        printf("\n");
        printf("2. Quote\n");
        printf("\n");
        printf("3. Exit\n");
        scanf("%d",&choice);
 
        switch(choice)
        {
            case 1: sum();
                break;
            case 2: rest();
                break;
                    
            case 3: 
			printf("\n");
			printf("Quitting program!\n");
                exit(0);
                break;
            default: 
			printf("\n");
			printf("Invalid choice!\n");
                break;
        }
    } while (choice != 3);
}
    
}
 
void sum(void)
{
    int num1, num2;
    int ch;
     
    printf("\n"); 
    printf("Enter number 1 : ");
    scanf("%d",&num1);
    
    printf("\n");
    printf("Enter number 2 : ");
    scanf("%d",&num2);
 
    printf("\n");
    printf("\nThe sum of the numbers was: %d",num1+num2);
 
    /* Flushes input buffer from the newline from scanf() */
    while ( (ch = getchar()) != '\n' && ch != EOF) ;
 
    printf("\n\nPress ENTER to continue.");
    while ( (ch = getchar()) != '\n' && ch != EOF)
        ;
 
    return;
}       
 
void rest(void)
{
    int ch;
    printf("\n");
    printf("There are no secrets to success. It is the result of preparation, hard work and learning from failure \n");
 
    /* Flushes input buffer */
    while ((ch = getchar()) != '\n' && ch != EOF) ;
 
    printf("\n");
    printf("\n\nPress ENTER to continue.");
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
 
    return;
}


