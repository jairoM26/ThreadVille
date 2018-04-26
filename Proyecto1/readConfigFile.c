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
#define CONFIG_FILE_NAME "config.conf"
/**
 * @brief 
 * 
 */
typedef struct conf_info {
    int scheduler;
    int bridgeSize;
    int avgSpeed;
    int debbuger;
    double distribution;
    int right_officer;
    int leftt_officer;
    int traffic_control_B1;
    int traffic_control_B2;
    int traffic_control_B3;
    int sem_time_L;
    int sem_time_R;
    int ambulance_percentage;
    int radioactive_percentage;

} info;

/**
 * @brief method that read a config file
 * @details this method read a config file and save it values into a struct
 * 
 * @param struct in
 */
void readConfigFile(info *conf_Info){
    FILE * fp;    
    fp = fopen(CONFIG_FILE_NAME,"r");  
    if (fp == NULL){
        fclose(fp); 
        exit(EXIT_FAILURE);
    }       
    else{
        char key[256], value[256];
        char * line = NULL;
        size_t len = 0;
        size_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            if(line[0] == '#' || line[0] == '\n')
                continue;
            else{
                sscanf(line, "%s = %s", key, value);
                if(strcmp(key, "SCHEDULER") == 0){  //Read the SCHEDULER value
                    sscanf(value, "%d", &(conf_Info->scheduler));
                }
                if(strcmp(key, "BRIDGE_SIZE") == 0){  //Read the brdige size value
                    sscanf(value, "%d", &(conf_Info->bridgeSize));
                }
                if(strcmp(key, "AVARAGE_SPEED") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->avgSpeed));
                }
                if(strcmp(key, "DEBBUGER") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->debbuger));
                }
                if(strcmp(key, "DIST") == 0){  //Read the avarage speed value
                    sscanf(value, "%lf", &(conf_Info->distribution));
                }
                if(strcmp(key, "TRAFFIC_CONTROL_B1") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->traffic_control_B1));
                }
                if(strcmp(key, "TRAFFIC_CONTROL_B2") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->traffic_control_B2));
                }
                if(strcmp(key, "TRAFFIC_CONTROL_B3") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->traffic_control_B3));
                }
                if(strcmp(key, "SEM_TIME_L") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->sem_time_L));
                }
                if(strcmp(key, "SEM_TIME_R") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->sem_time_R));
                }
                if(strcmp(key, "RIGHT_OFFICER") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->right_officer));
                }
                if(strcmp(key, "LEFT_OFFICER") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->leftt_officer));
                }
                if(strcmp(key, "A_P") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->ambulance_percentage));
                }
                if(strcmp(key, "R_P") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->radioactive_percentage));
                }              
            }
        }
        fclose(fp);   
    }
    
}