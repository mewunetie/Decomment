/*------------------------------------------------------------*/
/* decomment.c */
/* Author: Misrach Ewunetie */
/*------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
int newline = 0;

enum Statetype {NORMAL, STARTINGCOMMENT, INCOMMENT, ENDINGCOMMENT, STRING, CHAR, BACKSLASHSTRING, BACKSLASHCHAR}; 
/*----------------------------------------------------------*/
/* Implement the NORMAL state of the DFA. c is the current
    DFA character. Possibly write c, as specified by the DFA.
    Return the next state. */

enum Statetype handleNormalState(int c)
{
    enum Statetype state;
    if (c == '\'') {
        putchar(c);
        state = CHAR;
        
    }   /* how to print if char is '//'? */
        else if (c == '/') {
        state = STARTINGCOMMENT;
    }
        else if (c == '"') {
         putchar(c);
        state = STRING;
    }   else {
        putchar(c);
        state = NORMAL;
    }
    return state;
}

/*----------------------------------------------------------*/
/* Implement the STARTINGCOMMENT state of the DFA. Check whether 
    or not the chars are starting a comment, as specified by the DFA.
    Return the next state. */
enum Statetype handleStartingCommentState(int c)
{
    enum Statetype state;
    if (c == '/') {
        putchar(c);
        state = STARTINGCOMMENT;
    } else if (c == '*') {
        putchar(' ');
        state = INCOMMENT;
    } else {
        putchar(c);
        state = NORMAL;
    }
return state;
}

/*----------------------------------------------------------*/
/* Implement the INCOMMENT state of the DFA. Check whether a
    comment is going to terminate. If comment never terminates,
    print error message. Otherwise, return the next state. */
enum Statetype handleInCommentState(int c)
{
    int EXIT_FAILURE = 1;
    enum Statetype state;
    if (c == '*') {
        state = ENDINGCOMMENT;
    } else if (c == '\n') {
        newline += 1;
        state = INCOMMENT;
    } else if (c == EOF) {
        printf ("Error: line " + newline);
        printf (": unterminated comment\n");
        return EXIT_FAILURE; 
    } else {
        state = INCOMMENT;
    }
return state;
}

/*----------------------------------------------------------*/
/* Implement the ENDINGCOMMENT state of the DFA. c is the current
    DFA character. Possibly write c, as specified by the DFA.
    Return the next state. */
enum Statetype handleEndingCommentState(int c)
{
    enum Statetype state;
    if (c == '/') {
        state = NORMAL;
    } else if (c == '*') {
        state = ENDINGCOMMENT;
    } else {
        state = INCOMMENT;
    }
return state;
}

/*----------------------------------------------------------*/
/* Implement the STRING state of the DFA. c is the current
    DFA character. Possibly write c, as specified by the DFA.
    Return the next state. */
enum Statetype handleStringState(int c)
{
    enum Statetype state;
    if (c == '"') {
        putchar(c);
        state = NORMAL;
    }  else {
        putchar(c);
        state = STRING;
    }
return state;
}

/*----------------------------------------------------------*/
/* Implement the CHAR state of the DFA. c is the current
    DFA character. Possibly write c, as specified by the DFA.
    Return the next state. */
enum Statetype handleCharState(int c) 
{
    enum Statetype state;
    if (c == '\'') {
        putchar(c);
        state = NORMAL;
    } else {
        putchar(c);
        state = CHAR;
    }
return state;
}

/*----------------------------------------------------------*/
/* Implement the BACKSLASHSTRING state of the DFA. c is the current
    DFA character. Possibly write c, as specified by the DFA.
    Return the next state. */
enum Statetype handleBackSlashStringState(int c)
{
    enum Statetype state; 
    if (c == '\\') {
        putchar(c);
        state = BACKSLASHSTRING;
    } else {
        putchar(c);
        state = STRING;
    }
return state;
}

/*----------------------------------------------------------*/
/* Implement the BACKSLASHCAR state of the DFA. c is the current
    DFA character. Possibly write c, as specified by the DFA.
    Return the next state. */
enum Statetype handleBackSlashChartState(int c)
{
    enum Statetype state;
    if (c == '\\') {
        putchar(c);
        state = BACKSLASHCHAR;
    } else {
        putchar(c);
        state = CHAR;
    }
return state;
}

/*----------------------------------------------------------*/
/* Read text from stdin. Convert the first character of each
    "word" to uppercase, where a word is a sequence of
    letters. Write the result to stdout. Return 0. */
int main(void)
{
    int c;
    /* Use a DFA approach. state indicates the DFA state. */
    enum Statetype state = NORMAL;
    while ((c = getchar()) != EOF) {
        switch (state) {
            case NORMAL:
                state = handleNormalState(c);
                break;
            case STARTINGCOMMENT:
                state = handleStartingCommentState(c);
                break;
            case INCOMMENT:
                state = handleInCommentState(c);
                break;
            case ENDINGCOMMENT:
                state = handleEndingCommentState(c);
                break;
             case STRING:
                state = handleStringState(c);
                break;
            case CHAR:
                state = handleCharState(c);
                break;
             case BACKSLASHSTRING:
                state = handleBackSlashStringState(c);
                break;
            case BACKSLASHCHAR:
                state = handleBackSlashCharState(c);
                break;
        }
    }
    return 0;
}