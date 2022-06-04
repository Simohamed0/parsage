#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io-utils.h"

#define NBR_NODE 205756


typedef struct TreeNode{
    
    int id;
    double x;
    double y;
}TreeNode;


/**
 * @brief erase the fisrt char c from the string
 * 
 * @param string 
 * @param x 
 */
void erase_char(char *string, char c);


/**
 * @brief insert a char c into the string at the position loc 
 * 
 * @param src string before changing
 * @param dst string after inserting
 * @param c   char to insert
 * @param loc position to insert
 */
void string_insert(char *src,char *dst ,char x, int loc);


/**
 * @brief parse a csv file line and save the information in a data structure
 * 
 * @param fscript file to parse
 * @param fout file to write the information 
 * @param tree_struct data structure to save the information
 */
int parse_csv(FILE *src, FILE *dst , TreeNode *tab_tree); 

#endif 