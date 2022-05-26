#include "../include/parsing.h"


const char *separator = ";";






void erase_char(char *string, char x){
    
    int p ,i;
    
    for(i=0; string[i] != '\0';i++)
    {
        if (string[i] == x)
        {
            for(p=i; string[p]!=0; p++)
            {
                string[p]=string[p+1];
            }
            i--;
        }
    }
}


void string_insert(char *src,char *dst ,char x, int loc){
    
    int ti = 0; // index in tmp variable

    while (ti<loc) 
    {
        dst[ti++] = *src++; // copy first part from src
    }    
    dst[ti++] = x++; // append str
    while (*src)
    {
     dst[ti++] = *src++; // append the rest of src
    }
    dst[ti] = 0; // don't forget trailing 0
    //return tmp1;
}


void parse_csv(FILE *src, FILE *dst, TreeNode *tab_tree){

    char row[3000];
    char *id = "";    
    char *geo_point_2d;
    
    int i = 0;
    fgets(row,3000,src); // first line is not relevant
    //fseek(src,0,SEEK_SET);
    while ( fgets(row, 3000, src) != NULL )
    {
        // Extract the first token
        id = strtok(row, separator);
        tab_tree[i].id = atoi(id);
        
        // iterate through the string to extract the last token
        while( id!=NULL )
        {
            geo_point_2d= id;
            id = strtok(NULL, separator);
        }
        
        // separate the two coordinates
        char *token2 = strtok(geo_point_2d,",");
        
        // extract the tokens 
        erase_char(token2,'.');
        char new_x[20];
        string_insert(token2,new_x,'.',8);
        tab_tree[i].x = strtod(new_x,NULL);
        
        token2 = strtok(NULL,",");
        
        erase_char(token2,'.');
        char new_y[20];
        string_insert(token2,new_y,'.',7);
      
        tab_tree[i].y = strtod(new_y,NULL);
      
        fprintf(dst,"\n%d", tab_tree[i].id);
        fprintf(dst,"  %lf",tab_tree[i].x);
        fprintf(dst,"  %lf",tab_tree[i].y);
        i++;
    }
}






//void normalize_x(char * s , char *s_new){
//
//    int len = strlen(s);
//    
//    for (int i = 0; i < len; i++)
//    {
//        s_new[i]=s[i];
//    }
//
//    for(int i=len;i<17;i++){
//        s_new[i] = '0';
//    }
//    s_new[17] = '\0';
//}
//
//void normalize_y(char * s,char *s_new){
//
//    
//    int len = strlen(s);
//    
//    for (int i = 0; i < len; i++)
//    {
//        s_new[i]=s[i];
//    }
//
//    for(int i=len;i<16;i++){
//        s_new[i] = '0';
//    }
//    s_new[16] = '\0';
// 
//}


