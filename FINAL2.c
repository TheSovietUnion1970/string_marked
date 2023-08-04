#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char* combine_str(char* str1, char* str2){
    char* str = (char*)malloc(300);
    sprintf(str, "%s%s", str1, str2);
    return str;
}

char* extract1(char source[], int n) {
    char* destination = malloc((n + 1) * sizeof(char)); // Allocate memory for destination

    strncpy(destination, source, n); // Copy at most n characters
    destination[n] = '\0'; // Null-terminate the destination string

    return destination; // Return the dynamically allocated destination string
}

char* copy(char* msg){
    char* copied = (char*)malloc(strlen(msg)*sizeof(char));
    strcpy(copied, msg);
    return copied;
}

char* extract2(char source[], int n) {
    char* destination = malloc((200) * sizeof(char)); // Allocate memory for destination

    for (int i = n; i<strlen(source); i++){
        *(destination+i-n) = source[i];
    }

    *(destination + strlen(source) - n) = '\0';
    return destination; 
}

char* add(char* str, char newChar, int n){

    char* extracted1 = extract1(str, n);
    char* extracted2 = extract2(str, n);

    memmove(extracted1 + 1, extracted1, strlen(extracted1) + 1);
    memmove(extracted2 + 1, extracted2, strlen(extracted2) + 1);

    extracted1[0] = newChar;
    extracted2[0] = newChar;

    char *combine = (char*)malloc(strlen(extracted1)+strlen(extracted2)*sizeof(char));

    sprintf(combine,"%s%s", extracted1,  extracted2);

    return combine;
}

void show(char *pass, char *found){
    char *temp = (char*)malloc(strlen(pass) + 1);
    char *temp1 = (char*)malloc(strlen(pass) + 1);
    char **store2 = (char**)malloc((200)*sizeof(char*));
    int* list = (int*)malloc(200*sizeof(int));

    int num = 0, i = 0;
    strcpy(temp,pass);
    int j=0;
    while(1){
        int len1 = strlen(temp);
        

        temp1 = strstr(temp, found);
        if (temp1 == NULL) break;
        
        int len2 = strlen(temp1);
        store2[i] = (char*)malloc((len2-len1+2)*sizeof(char));
        list[i] = (int)malloc(100*4);

        if (i == 0) store2[i] = extract2(pass, len1 - len2);
        else store2[i] = extract2(temp, len1 - len2);

        if (i!=0) {
            *(list+j) = len1 - len2;
            j++;
            
        }

        num = len1 - len2 + num;
        temp1[0] = '/';
        strcpy(temp, temp1);
        i++;
    }


    for (int k =0; k<i; k++){
        store2[k] = extract1(store2[k], list[k]);
        
        store2[k] = add(store2[k], '|', strlen(found));
        printf("store2[%d] = `%s`\n", k, store2[k]);

    }

    char *tempf;
    strcpy(tempf,store2[0]);
    if (i != 0){
        for (int k =0; k<i; k++){
            tempf = combine_str(tempf, store2[k+1]);
        }
    }

    printf("`%s`",  tempf);
    free(tempf);
    
    free(tempf);

    free(temp);
    free(list);
    free(temp1);
    free(store2);

}



char pass1[] = " to dye his pale skin, and as the day Charles spent lying on a branch of the great oak tree in Boscobel Wood as the Parliamentary soldiers scoured the forest floor below. Spencer draws out both the humour - such as the preposterous refusal of Charles’s friend Henry Wilmot to adopt disguise on the grounds that it was beneath his dignity - and the emotional tension when the secret of the king’s presence was cautiously revealed to his supporters";        
char pass4[] = "Vinh oi, hello Vin, toi ten la Vinh";


char pass3[] = "Vi jskj Vifhdhd     VidjVij hhhViViVi             Vi ghfg Vi";
char pass2[] = "he jskj hefhdhd he   helloo he heggggg   hev hevccd                            he                                        he helloo he heggggg   hev hevccd ";


int main(){
    show(pass2, "hev");
    return 0;
}