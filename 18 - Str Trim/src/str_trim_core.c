#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// Function to trim leading and trailing whitespace from a string in place
// buf: input string buffer to trim
// returns: length of trimmed string
size_t trim_inplace(char *buf)  {  
    
    // Check for NULL input
    if (!buf) {
        return 0;
    }

    size_t left_index = 0;
    size_t length = strlen(buf);


    // Scan from the start to find first non-whitespace character
    while (left_index < length) {
        if (isspace((unsigned char)buf[left_index])) {
            left_index++;
        } else {
            break; // Found first non-whitespace character
        }

        if (left_index == length) {
            buf[0] = '\0'; // String is all whitespace
            return 0;
        }


    }

    // Now scan from the end to find trailing whitespace
    size_t right_index = length -1; 
    while (right_index > left_index) {
        if (isspace((unsigned char)buf[right_index])) {
            right_index--;
        } else {
            break; // Found last non-whitespace character
        }
    }

    // Calculate new length of trimmed string
    size_t new_length = right_index - left_index + 1;

    if (left_index > 0) {
        memmove(buf, buf + left_index, new_length);
    }

    buf[new_length] = '\0'; // Null-terminate the trimmed string
    return new_length;

}

// Function to calculate the length of the trimmed string without modifying the original
// buf: input string buffer
// returns: length of trimmed string
size_t trimmed_length(const char *buf) {
    if (!buf) {
        return 0;
    }

    size_t left_index = 0;
    size_t length = strlen(buf);

    while(left_index < length) {
        if (isspace((unsigned char)buf[left_index])) {
            left_index++;
        }
        else {
            break;
        }
    }
    if (left_index == length) {
        return 0;
    }
    size_t right_index = length -1;
    while (right_index > left_index) {
        if (isspace((unsigned char)buf[right_index])) {
            right_index--;
        }
        else {
            break;
        }
    }
    size_t trimmed_length = right_index - left_index + 1;
    return trimmed_length;

}


