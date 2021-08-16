// #include<stdio.h>
// #include<stdlib.h>

// void main(){
//     char dev[20] = "";
//     int int_no = 310;
//     int nbits = 4;
//     int temp, a,b;
//     dev[0] = '0';
//     dev[1] = 'X';
//     for(int i=0;i<nbits;i++){
//         b = int_no%16;
//         temp = int_no/16;
//         int_no = temp;
//         printf("%d\n",b);
//         if(b>=10 && b<=15){
//             a = 65-(10-b);
//             printf("a = %d\n",a);
//             dev[i+2] = a;
//         }
//         else{
//             a = b;
//             dev[i+2] = a+'0';
//         }
//     }
//     printf("%s\n",dev);

// }


//// Fread nu example che ek vakat jova mate.

#include <stdio.h>
#include <string.h>

int main () {
   FILE *fp;
   char c[] = "this is tutorialspoint\n nla bla bla";
   char buffer[100];

   /* Open file for both reading and writing */
   fp = fopen("file.txt", "w+");

   /* Write data to the file */
   fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
   fseek(fp, 0, SEEK_SET);

   /* Read and display data */
   fread(buffer, strlen(c)+1, 1, fp);
   printf("%s\n", buffer);
   fclose(fp);
   
   return(0);
}