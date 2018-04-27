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
    int myThread;
    int bridge_to_print;
    int hardware_available;
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
                else if(strcmp(key, "BRIDGE_SIZE") == 0){  //Read the brdige size value
                    sscanf(value, "%d", &(conf_Info->bridgeSize));
                }
                else if(strcmp(key, "AVARAGE_SPEED") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->avgSpeed));
                }
                else if(strcmp(key, "DEBBUGER") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->debbuger));
                }
                else if(strcmp(key, "DIST") == 0){  //Read the avarage speed value
                    sscanf(value, "%lf", &(conf_Info->distribution));
                }
                else if(strcmp(key, "TRAFFIC_CONTROL_B1") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->traffic_control_B1));
                }
                else if(strcmp(key, "TRAFFIC_CONTROL_B2") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->traffic_control_B2));
                }
                else if(strcmp(key, "TRAFFIC_CONTROL_B3") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->traffic_control_B3));
                }
                else if(strcmp(key, "SEM_TIME_L") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->sem_time_L));
                }
                else if(strcmp(key, "SEM_TIME_R") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->sem_time_R));
                }
                else if(strcmp(key, "RIGHT_OFFICER") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->right_officer));
                }
                else if(strcmp(key, "LEFT_OFFICER") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->leftt_officer));
                }
                else if(strcmp(key, "A_P") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->ambulance_percentage));
                }
                else if(strcmp(key, "R_P") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->radioactive_percentage));
                }
                else if(strcmp(key, "MY_PTHREAD") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->myThread));
                }
                else if(strcmp(key, "BRIDGE_TO_PRINT") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->bridge_to_print));
                } 
                else if(strcmp(key, "HARDWARE_AVAILABLE") == 0){  //Read the avarage speed value
                    sscanf(value, "%d", &(conf_Info->hardware_available));
                }                
            }
        }
        fclose(fp);   
    }
    
}