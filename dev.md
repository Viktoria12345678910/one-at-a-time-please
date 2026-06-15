my idea for this program is pretty simple it is a todo list but to do page is secondary on main page you have 2 things:
1. the task at hand
2. a charachter of your choice
the task can be marked as done and then the next task in the thread gets displayed. the can be multiple threads and they are like folders for your task for example a to do page can look something like this:
-thread 1
    - task 1
    - task 2
    - task 3
    ...
    - task n

-thread 2
    - task 1
    - task 2
    - task 3
    ...
    - task n

-thread 3
    - task 1
    - task 2
    - task 3
    ...
    - task n

...

-thread n
    - task 1
    - task 2
    - task 3
    ...
    - task n
---------------------------------------------------------
pages:
>main page
    >>current thread -- випадаючий список
    >>task
    >>optional tomodoro timer
    >>chrachter
    >>task can be marked done
    >>charachter can say encouraging staff
>todo page
    >>has all the threads
    >>has a button to add a task and the task must be added to a thread
    >>tasks can also be deleted
>threads page
    >>has all the threads on it
    >>threads can be added and deleted on here
    >>all thread managment is going on here
>settings page
    >>charachter can be added as a png
    >>color schemes
    >>language
    >>pomodoro timer: 25/5 50/10 custom: work____ break____

database
sql
tables:
1. tasks
    >taskId
    >taskName
    >taskDescription -- description of what is needed to do for this task
    >threadId -- an identificator of what thread the task in question belongs to
    >estimated time
    >completed. default: false
2. threads
    >threadId
    >threaName
    >taskCount
    >isArchived. default: false
3. settings
    >charachter image
    >color scheeme
    >pomodor settings

after a thread is completed it should be marke as archive along with all the tasks in it adding such a property to tasks themeselves would be redundant scince they already have a completed column and thread is only archived once all the tasks are complete.
--14/06/2026 23:29
