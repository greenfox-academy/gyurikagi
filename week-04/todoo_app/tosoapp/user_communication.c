#include "user_comm.h"

void print_usage () {
printf ( "Todo application\n\
====================\n\
Commands:\n\
 -a   Adds a new task\n\
 -wr  Write current todos to file\n\
 -rd  Read todos from a file\n\
 -l   Lists all the tasks\n\
 -e   Empty the list\n\
 -rm   Removes a task\n\
 -c   Completes a task\n\
 -p   Add priority to a task\n\
 -lp  Lists all the tasks by priority)\n\
exit  Exit program\n\
        \n\n");
}

// tasks

/*todootasks add_new_task (char a) {
    a.task  = a;
    return a.task;
}*/

