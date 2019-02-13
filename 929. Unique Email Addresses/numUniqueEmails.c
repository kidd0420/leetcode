#include "stdio.h"
#include <stdlib.h>

int numUniqueEmails(char** emails, int emailsSize) {
    int count = 0;
    int idx = 0;
    int loc_idx = 0;
    int dot_count = 0;
    char tmp_mail[100 + 1];
    char **email_store = calloc(emailsSize, sizeof(char*));
    int issame = 0;

    for (idx = 0; idx < emailsSize; idx++) {
        char *mouse;
    	int mouse_idx;

    	mouse = strchr(emails[idx], '@');
    	mouse_idx = (int)(mouse - emails[idx]);

    	memset(tmp_mail, 0x0, 100);
        dot_count = 0;
        issame = 0;

    	for (loc_idx = 0; loc_idx < mouse_idx; loc_idx++) {
    		if (emails[idx][loc_idx] == '+') {
    			memcpy(&tmp_mail[loc_idx - dot_count], &emails[idx][mouse_idx], strlen(emails[idx]) - mouse_idx);
                printf("tmp_mail: %s\n", tmp_mail);
                break;
    		} else if (emails[idx][loc_idx] == '.') {
                dot_count++;
            } else {
                tmp_mail[loc_idx - dot_count] = emails[idx][loc_idx];
            }
    	}

        for (loc_idx = 0; loc_idx < count; loc_idx++) {
            if (strcmp(email_store[loc_idx], tmp_mail) == 0) {
                issame = 1;
                break;
            }
        }

        if (issame == 0) {
            email_store[count] = calloc(100 + 1, sizeof(char));
            memcpy(email_store[count], tmp_mail, 100);
            count++;
        }
    }

    for (loc_idx = 0; loc_idx < count; loc_idx++)
        free(email_store[loc_idx]);

    free(email_store);

    return count;
}

int main (void)
{
    int count;
    char **email = calloc (5,sizeof(char*));

    email[0] = "test.email+alex@leetcode.com";
    email[1] = "test.e.mail+bob.cathy@leetcode.com";
    email[2] = "testemail+david@.com";
    email[3] = "testemail+david@.com";
    email[4] = "testemail+david@.com";

    count = numUniqueEmails(email, 5);

    printf("count: %d\n", count);

    free(email);

    return 0;
}