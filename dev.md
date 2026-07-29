Programming language: c++
Framework: Qt
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
    >completed. default: false
2. threads
    >threadId
    >threaName
    >taskCount
    >isArchived. default: false
3. settings
    >charachter image
    >themeId
    >pomodoroId
    >language
4. themes
    >theme name
    >themJSON
5. pomodoro
    >work
    >rest

after a thread is completed it should be marked as archived along with all the tasks in it adding such a property to tasks themeselves would be redundant scince they already have a completed column and thread is only archived once all the tasks are complete.
--14/06/2026 23:29
done setting up the database -- 15/06/2026 13:26
Now i need to set up models after that i will setup the main page then all other pages and i will leave styling till the very end.
Models:
1. MainWindow
        >>tasks array
        >>threads array
2. Database
    >it essentially does all the crud operations

public:
        >>static Database& instance();
        >>bool connect(const QString &path = "library.db");
        >>void disconnect();

        >>bool createTables();

        // Tasks methods
        >>int createTask(const QString &name, const QString &description,int threadId);
        >>bool completeTask(int taskId);

        // Settings methods
        >>bool changeCharachterImg(const QString &path);
        >>bool changeTheme(int themeId);
        >>bool changePomodoro(int work, int rest);

        // thread methods
        >>int createThread(const QString &name);
        >>bool updateTaskCount(int threadId);

        >>bool deleteTask(int taskId);
        >>bool deleteThread(int threadId);
        >>bool deleteTheme(int themeId);

        >>QSqlDatabase getDatabase() { return mDb; }

private:
        >>Database();
        >>~Database();
        >>Database(const Database&) = delete;
        >>Database& operator=(const Database&) = delete;

        >>QSqlDatabase mDb
3. Task
        >>taskId
        >>taskName
        >>taskDescription -- description of what is needed to do for this task
        >>threadId -- an identificator of what thread the task in question belongs to
        >>completed. default: false
4. Thread
    >threadId
    >threaName
    >taskCount
    >isArchived. default: false

i need an array for tasks and array for threads each of them will hold an object those should be vectors, what i am thinking is have vector conatin just ids and then fetch all other info as needed based on id
modified the main page -- 20/06/26 20:32

 - [x] Create thread(handled in datanase class and accesible in New)
 - [x] Delete thread(handled in datanase class and accesible in show dialog)
 - [x] Create task(handled in datanase class and accesible in New)
 - [x] Delete task(handled in datanase class and accesible in show dialog)
 - [x] Order tasks within thread(handled with task ids)
 - [x] Mark task complete(handled in datanase class and accesible with a button)
 - [x] Automatically show next task(handled with task completetion in main window)
 - [x] Automatically archive completed thread
 - [x] Thread dropdown on main page(handled mainwindow class)
 - [x] Main page shows current task(handled in mainwindow class)
 i need to show a message if no thread is chosen
 i dont anymore because that is not an option
 anyway i am done with most functionalyty but it is unaccessible in the application due to residing in dialogs i have not added
 dialogs:
- [x] New task
- [x] New thread
- [ ] View tasks and threads - tree view
- [x] new charachter - basically choosing a file
- [x] Start pomodoro
- [x] Adjust pomodoro
- [x] change language
- [x] change theme
oh and gotta rename the actions really quic and i am done for tday -- 21/06/2026 20:44
do i have get charachter method? now i do
i need:
- [x] get work time
- [x] get rest time
i need to write start work and start rest timers for pomodoro dialog
Option 3: Progress bar countdown

For a countdown timer:

const int totalSeconds = 300; // 5 minutes
int remaining = totalSeconds;

connect(timer, &QTimer::timeout, this, [this, totalSeconds]() mutable {
    remaining--;

    ui->progressBar->setMaximum(totalSeconds);
    ui->progressBar->setValue(remaining);

    if (remaining <= 0)
        timer->stop();
});

This visually shows progress toward completion.
--22/06/2026 15:37
okay pomodoro dialog was crashing the whole program when closed but it is fixed now. net step is to shange the work and rest time. i have methods defined in my db class so this should be pretty easy. that was pretty easy.
i am going to do the new task and thread cuz they are basically the same and i think that is it for tday.
i think i will start change charachter dialog and then will be done for the day.
everything is going really well and i am gonna keep going. Now i need to do the rest of settings and then view. I remembered QSettings exist i should have stored times with it but i cant be bothered to figure it out rn. i hit a wall with qsettings and the language thing i will get back at it tomorrow. -- 23/06/2026 19:04
okay only view is left also themes need tuning and new languages are needed cuz the abilyty to choose language is kinda useless if there is only one and that is it for today i think i will be done with this this week -- 24/06/2026 19:33 
if tasks are completed is null for some reason and as the result they are not rendered corectly --25/06/2026 22:44
1. addBindValue is confuding af i shoud use :name instead of ? everywhere [x]
2. i need to actually state that complete is false othervise it is null [x]

okay i am almost done i think i will leave styling for v2 and i still need to implement ui for deleting staff and wiping user data
tasks arent recieved properly also i am swithing from determening currrent task to database to leaving up to the user
i thought loading tasks and threads broke turns out i deleted the database and the simply nothing so that is good to know.
i need to rework the settings and use QSettings instead of the database cuz it is getting anoying to manage.
i Think everything is done now the only thing left is to add some translations and themes before that i need to make sure that everything is translation ready. i will figure everything else out as i go. -- 16:06 22.07.2026
