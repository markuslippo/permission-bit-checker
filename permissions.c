#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    if(argc >= 6)
    {
        

        /* Check that the requested operation does not contain anything else than r w or x*/
        for(int i = 0; i < strlen(argv[4]); i++){
            if(argv[4][i] != 'r' && argv[4][i] != 'w' && argv[4][i] != 'x' ) {
                return 2;
            }
        }

        /* Check that permission bits were properly given */

        if(strlen(argv[1]) != 3) {
            return 2;
        }
        
        char *permission = argv[1];
        char *end;
        long permissionbits = strtol(permission, &end, 8);

        if(end == permission || *end != '\0') // end == permission here means that a conversion did not happen, *end != '\0' means that the permissionbit did include some illegal character
        {
            return 2;
        } 


        int mask = 0; //operation bits
        int mode = permissionbits; //permission bits
        if(strchr(argv[4], 'r') != NULL) mask = mask | 4;
        if(strchr(argv[4], 'w') != NULL) mask = mask | 2;
        if(strchr(argv[4], 'x') != NULL) mask = mask | 1;


        /* Are we the owner? */
        if(strcmp(argv[2], argv[5]) == 0) 
        {
            mode >>= 6;
            return (mask & ~mode) ? 1 : 0;
        }


        /* If the group and global permissions are the same then we do not need to check groups */
        if((mode >> 3) & 7 == mode & 7) {
            return (mask & ~mode) ? 1 : 0;
        }


        /* Do we belong in the file's group? */
        if(argc > 6) 
        {
            for(int i = 6; i < argc; i++) 
            {
                if(strcmp(argv[3], argv[i]) == 0) 
                {
                    mode >>= 3;
                    return (mask & ~mode) ? 1 : 0;
                }
            }
        }


        /* We are not the owner or in the group, can we do the operation with global permissions? */
        return (mask & ~mode) ? 1 : 0;
    }
    else 
    {
        return 2;
    }   
}