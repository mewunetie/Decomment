#include <stdio.h>
#include <ctype.h>
enum Statetype {NORMAL, INWORD};
/*----------------------------------------------------------*/
/* Implement the NORMAL state of the DFA. c is the current
DFA character. Write c or its uppercase equivalent to
stdout, as specified by the DFA. Return the next state. */
enum Statetype handleNormalState(int c)
{
enum Statetype state;
if (isalpha(c)) {
putchar(toupper(c));
state = INWORD;
} else {
putchar(c);
state = NORMAL;
}
return state;
}
/*----------------------------------------------------------*/
/* Implement the INWORD state of the DFA. c is the current
DFA character. Write c to stdout, as specified by the DFA.
Return the next state. */
enum Statetype handleInwordState(int c)
{
enum Statetype state;
if (!isalpha(c)) {
putchar(c);
state = NORMAL;
} else {
putchar(c);
state = INWORD;
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
case INWORD:
state = handleInwordState(c);
break;
}
}
return 0; }
