#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//----------------------------------------------------------------------
char* extract_first_characters(char* pass, char* extract);
char* extract_last_characters(char* pass, char* extract);
void REPLACE_PASS(char* pass2, char* ex, char* replace);
void replaceString(char *str, const char *oldWord, const char *newWord);
char* extract_first_characters_n(char* source, int n);
char* add_first_char(char* s, char mark);
//------------------------------------------------------------------------
char pass1[] = "asasasasto dye his asle as skin, and as the day Charles asent lying on as a branch as of the great asoak tree in as Boscobel   as";    
char pass0[] = "asasasasto dye his  asle as skin, and as the day Charles asent lying on as a nch as of the great oak tree in Boscobel as ";

char pass2[] = "as if as though as ha";
char pass3[] = "asas dye his  asle as skin, and as the day Charles ";   
char pass4[] = "asasasasto dye his asle as skin,and as the day Charles asent lying on as a branch as of the great oak tree in Boscobel  as";     
char pass5[] = "One of as as the joys of Spencers book, a result not least of its use of Charles IIs own narrative as well as those of his supporters, is just how close the reader gets to the action. The day-by-day retelling of the fugitives doings provides delicious details: the cutting of the king’s long hair with agricultural shears, the use of walnut leaves to dye his pale skin, and the day Charles spent lying on a branch of the great oak tree in Boscobel Wood as the Parliamentary soldiers scoured the forest floor below. Spencer draws out both the humour - such as the preposterous refusal of Charless friend Henry Wilmot to adopt disguise on the grounds that it was beneath his dignity - and the emotional tension when the secret of the kings presence was cautiously revealed to his supporters";
int main(){
    REPLACE_PASS("Hello Tommy, I hang out with you, Tommy", "Tommy", "Vinh");
    return 0;
}

// ham con
void REPLACE_PASS(char* pass2, char* ex, char* replace){
    char **msg = (char**)malloc(200*sizeof(char*));
    char **msg1 = (char**)malloc(200*sizeof(char*));
    char **first = (char**)malloc(200*sizeof(char*));
    char **last = (char**)malloc(200*sizeof(char*));
    //char* first; char* last;
    int i=0;
    uint32_t len_msg;
    char* temp;
    temp = (char*)malloc(strlen(pass2)+1); // temporary
    strcpy(temp, pass2);
    while(1){
        temp = strstr(temp, ex);
        if (temp == NULL) break;
        msg[i] = (char*)malloc(strlen(temp)+1);
        if (strlen(replace)>strlen(ex)) msg1[i] = (char*)malloc(strlen(temp)-strlen(ex)+strlen(replace)+1);
        else msg1[i] = (char*)malloc(strlen(temp)+1);

        strcpy(msg[i], temp);
        strcpy(msg1[i], temp);
        printf("msg[%d]-->`%s`\n", i, msg[i]);
        
        temp[0] = 'n';
        i++;
    }

    char **msg2 = (char**)malloc(200*sizeof(char*));
    char **store = (char**)malloc(200*sizeof(char*));
    for (int j = 0; j<i; j++){
        int x;
        if (j != i-1) x = strlen(msg[j]) - strlen(msg[j+1]);
        else x = strlen(msg[j]);
        msg2[j] = (char*)malloc(x+1);
        msg2[j] = extract_first_characters_n(msg[j], x);

        if (strlen(replace)>strlen(ex)) msg1[j] = (char*)malloc(strlen(msg2[j])-strlen(ex)+strlen(replace)+1);
        else msg1[j] = (char*)malloc(strlen(msg2[j])+1);
        strcpy(msg1[j], msg2[j]);

        replaceString(msg1[j], ex, replace);

        printf("`%s`\n", msg2[j]);

        first[j] = (char*)malloc(strlen(ex)+2);
        last[j] = (char*)malloc(strlen(msg2[j])-strlen(ex)+2);
        first[j] = extract_first_characters(msg2[j], ex);
        last[j] = extract_last_characters(msg2[j], ex);

        first[j] = add_first_char(first[j], '|');
        last[j] = add_first_char(last[j], '|');

        // printf("`%s` - `%s`\n", first[j], last[j]);
        store[j] = (char*)malloc(strlen(first[j])+strlen(last[j])+1);
        sprintf(store[j], "%s%s", first[j], last[j]);
        printf("`%s`\n", store[j]);
    }
    len_msg = strlen(pass2)+i*(-strlen(ex)+strlen(replace));
    int len1_msg = strlen(pass2)+i*2;

    char new[len_msg+1];
    char new1[len1_msg+1];

    printf("i = %d\n", i);

    strcpy(new, msg1[0]);
    strcpy(new1, store[0]);
    for (int j = 0; j<i; j++){
        if (j!=0) sprintf(new, "%s%s", new, msg1[j]);
        if (j!=0) sprintf(new1, "%s%s", new1, store[j]);

    }
    printf("------------------%d results------------------------------------------------------------------------------------------------\n", i);
    printf("`%s`\n", new1);
    printf("-------------------%d results are replaced by `%s`---------------------------------------------------------------------\n", i, replace);
    printf("`%s`\n", new);



    
    while(i>0){free(msg[i-1]);free(msg1[i-1]);free(msg2[i-1]);free(first[i-1]);free(last[i-1]);i--;}
    free(msg);free(last);free(first);free(msg2);free(msg1);
    free(temp);
}

char* extract_first_characters(char* pass, char* extract){
    char* msg = (char*)malloc((strlen(extract)+1)*sizeof(char));
    memmove(msg, pass, strlen(extract));
    *(msg+strlen(extract)) = '\0';
    free(extract);
    return msg;
}

char* extract_last_characters(char* pass, char* extract){
    char* msg = (char*)malloc((strlen(pass) - strlen(extract)+1)*sizeof(char));
    memmove(msg, pass-0+strlen(extract), strlen(pass) - strlen(extract));
    *(msg+strlen(pass) - strlen(extract)) = '\0';
    free(extract);
    return msg;
}

void replaceString(char *str, const char *oldWord, const char *newWord) {
    char *pos = strstr(str, oldWord); // Find the position of oldWord in str

    if (pos != NULL) {
        int oldLength = strlen(oldWord);
        int newLength = strlen(newWord);

        // Move characters after the oldWord to make space for newWord
        memmove(pos + newLength, pos + oldLength, strlen(pos + oldLength) + 1);

        // Copy newWord into the position of oldWord
        strncpy(pos, newWord, newLength);
    }
}

char* extract_first_characters_n(char* source, int n) {
    char* destination = malloc((n + 1) * sizeof(char)); // Allocate memory for destination
    strncpy(destination, source, n); // Copy at most n characters
    destination[n] = '\0';
    return destination;
}

char* add_first_char(char* s, char mark){

    char* des = (char*)malloc(strlen(s) + 2);
    memmove(des+1, s,  strlen(s)+1);
    
    des[0] = mark;
    return des;
    free(des);
}
