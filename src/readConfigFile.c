/**
 * readConfigFile.c
 * @details Simple program to read file into a config struct
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 25-02-2018
 * 
 * reference: https://www.pacificsimplicity.ca/blog/simple-read-configuration-file-struct-example = link that helps to resolve the problem
 * 
 * compilation command: gcc readConfigFile.c -o reader
 * Execution: ./reader
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/**
 * @brief setting global variables
 */
#define CONFIG_FILE_NAME "../config.conf"

/**
 * @brief method that read a config file
 * @details this method read a config file and save it values into a struct
 * 
 * @param pScheduler parameter where the value of what scheduler is gonna to be used
 * @param pBridgeSize the amount of car that can be on a bridge at the same time
 */
void readConfigFile(int *pScheduler, int *pBridgeSize, int *pAvgSpeed){
    FILE * fp;    

    fp = fopen(CONFIG_FILE_NAME, "r");
    if (fp == NULL){
        fclose(fp); 
        exit(EXIT_FAILURE);
    }
    else{
        char key[256], value[256];
        int iVal;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            if(line[0] == '#' || line[0] == '\n')
                continue;
            else{
                sscanf(line, "%s = %s", key, value);
                if(strcmp(key, "SCHEDULER") == 0){  //Read the SCHEDULER value
                    sscanf(value, "%f", &(*pScheduler));
                if(strcmp(key, "BRIDGE_SIZE") == 0){  //Read the brdige size value
                    sscanf(value, "%f", &(*pBridgeSize));
                if(strcmp(key, "AVARAGE_SPEED") == 0){  //Read the brdige size value
                    sscanf(value, "%f", &(*pBridgeSize));
            }
        }
        fclose(fp);    
    }
    
}