/*
    CoronaSafe Engineering Fellowship
    Programming Task
*/

/*
    Implementation of a Command-Line Program
    To manage todo list
*/

#include<bits/stdc++.h>
#include<fstream>
#include<ctime>

using namespace std;

/*---------Functions Definitions----------------------------------------------*/

void help();                              /*  Prints the CLI usage    */

void pending();                           /*  Lists all pending todos in reverse order    */

void add(vector<string> tasks);           /*  Add new todos   */

void remove(vector<string> vec);          /*  Deletes a todo    */

void done(vector<string> vec);            /*  Marks a todo as done    */

void report();                            /*  Prints current status with date   */

string day();                             /*  Returns date in yyyy-mm-dd format   */

int int_converted(string str);            /*  Converts a string to integer    */

/*----------------------------------------------------------------------------*/



/*------------------main function---------------------------------------------*/

int main(int argc, char* argv[])
{
  /*  When no arguments passed  */

  if(argc==1)			/*	./todo   */
    help();

  /* When some argument is passed */

  else
  {
    if(strcmp(argv[1], "help")==0)    /*  ./todo help   */
      help();

    else if(strcmp(argv[1], "ls")==0)     /*  ./todo ls   */
      pending();

    else if(strcmp(argv[1], "add")==0)    /*  ./todo add "tasks"    */
    {
      /*  When no task passed as argument   */

      if(argc==2)
				cout<<"Error: Missing todo string. Nothing added!\n";

      /*  When one or more tasks are passed as argument   */

      else
			{
				vector<string> str;     /*    Stores all tasks    */
				for(int i=2; i<argc; i++)
					str.push_back(argv[i]);
				add(str);
			}
    }

    else if(strcmp(argv[1], "del")==0)    /*   ./todo del "positions"    */
    {
      /*  When position of todo to be deleted is not passed as argument   */

      if(argc==2)
				cout<<"Error: Missing NUMBER for deleting todo.\n";

      /*  When one or more positions of todos to be deleted is passed as argument */

      else
			{
				vector<string> vec;     /*  Stores all positions  */
				for(int i=2; i<argc; i++)
				{
					vec.push_back(argv[i]);
				}
				remove(vec);
			}
    }

    else if(strcmp(argv[1], "done")==0)   /*  ./todo done "positions"   */
    {
      /*  When position of todo to be marked done is not passed as argument   */

      if(argc==2)
				cout<<"Error: Missing NUMBER for marking todo as done.\n";

      /*  When one or more positions of todos to be marked done is passed as argument */

      else
			{
        vector<string> vec;   /*  Stores all positions  */
				for(int i=2; i<argc; i++)
				{
					vec.push_back(argv[i]);
				}
				done(vec);
			}
    }

    else if(strcmp(argv[1], "report")==0)   /*  ./todo report   */
      report();

    else
      cout<<"Error: Invalid arguments.\n";    /*  Argument doesn't match any available functions  */
  }

  return 0;
}


/*----------------------------------------------------------------------------*/



/*-------------------Function Definitions-------------------------------------*/


/*  Prints all the available functions  */

void help()
{
  cout<<"Usage :-\n";
  cout<<"$ ./todo add \"todo item\"  # Add a new todo\n";
  cout<<"$ ./todo ls               # Show remaining todos\n";
  cout<<"$ ./todo del NUMBER       # Delete a todo\n";
  cout<<"$ ./todo done NUMBER      # Complete a todo\n";
  cout<<"$ ./todo help             # Show usage\n";
  cout<<"$ ./todo report           # Statistics\n";
}



/*  Prints all the pending todos in reverse order */

void pending()
{
  ifstream file("todo.txt");
  if(file.is_open())
  {
    string str;
    vector<string> tasks;
    while(getline(file, str))
      tasks.push_back(str);
    file.close();
    int n = tasks.size();
		if(n==0)
			cout<<"There are no pending todos!\n";

		else
		{
			for(int i=n; i>0; i--)
	    {
	      cout<<'['<<i<<"] "<<tasks[i-1]<<endl;
	    }
		}
  }

  else    /*  File not opened because it is deleted and nothing is added  */
		cout<<"There are no pending todos!\n";
}




/*  Adds multiple tasks sequentially to the todo list */

void add(vector<string> tasks)
{
  ofstream file("todo.txt", ios::app);

  if(file.is_open())
  {
		for(auto str:tasks)
		{
			file<<str<<"\n";
      cout<<"Added todo: \""<<str<<"\"\n";
		}
    file.close();
  }

  else
    cout<<"Unable to open file.\n";
}



/*  Deletes a todo at multiple positions. */

void remove(vector<string> vec)
{
  /*  Store positions in integer format */

	vector<int> positions;
	for(long unsigned int i=0; i<vec.size(); i++)
		positions.push_back(int_converted(vec[i]));

  ifstream infile("todo.txt");
  if(infile.is_open())
  {
    string str;
    vector<string> tasks;     /*  Stores all todos  */
    while(getline(infile, str))
    {
      tasks.push_back(str);
    }
    infile.close();
		int n = tasks.size();     /*  Total number of pending todos */

		for(long unsigned int i=0; i<positions.size(); i++)
		{
			if(positions[i]<1 || positions[i]>n)
				cout<<"Error: todo "<<"#"<<vec[i]<<" does not exist. Nothing deleted.\n";
			else
			{
				tasks[positions[i]-1] = "No task here.";

        /*  Printing acknowledgement before deleting
        to maintain the order of output in which input is provided.  */

				cout<<"Deleted todo #"<<vec[i]<<"\n";
			}
		}
		ofstream outfile("todo.txt", ios::trunc);   /*  Deletes all todos from todo.txt */
		for(int i=0; i<n; i++)
		{
			if(tasks[i] == "No task here.")
				continue;
			outfile<<tasks[i]<<"\n";
		}
		outfile.close();
  }


  /*  When no todos are present  */

  else
	{
		for(long unsigned int i=0; i<vec.size(); i++)
			cout<<"Error: todo "<<"#"<<vec[i]<<" does not exist. Nothing deleted.\n";
	}
}




/*  Mark multiple todos as done */
/*  Shifts the todo item from todo.txt to done.txt  */

void done(vector<string> vec)
{
  /*  Store positions in integer format */

	vector<int> positions;
	for(long unsigned int i=0; i<vec.size(); i++)
		positions.push_back(int_converted(vec[i]));

  ifstream infile("todo.txt");
  if(infile.is_open())
  {
    string str;
    vector<string> tasks;     /*  Store all pending todos */
    while(getline(infile, str))
    {
      tasks.push_back(str);
    }
    infile.close();

		int n = tasks.size();			/*	n = number of pending tasks  */

		ofstream outfile("done.txt", ios::app);   /*  Append in done.txt  */
		for(long unsigned int i=0; i<vec.size(); i++)
		{
			if(positions[i]<1 || positions[i]>n)
				cout<<"Error: todo #"<<vec[i]<<" does not exist.\n";
			else
			{
				outfile<<"x "<<day()<<" "<<tasks[positions[i]-1]<<"\n";
				tasks[positions[i]-1] = "No task here";
				cout<<"Marked todo #"<<vec[i]<<" as done.\n";
			}
		}
		outfile.close();

    /*  Store only remaining todos in todo.txt  */
		outfile.open("todo.txt", ios::trunc);
		for(int i=0; i<n; i++)
		{
			if(tasks[i] == "No task here")
				continue;
			outfile<<tasks[i]<<"\n";
		}
		outfile.close();
  }


  /*  When no todos are present  */

  else
	{
		for(long unsigned int i=0; i<vec.size(); i++)
			cout<<"Error: todo #"<<vec[i]<<" does not exist.\n";
	}
}




/*  Reports the current status of pending and completed todos */

void report()
{
  int pending = 0, completed = 0;
	string str;

  ifstream file("todo.txt");
  while(getline(file, str))     /*  Count Pending todos */
    pending++;
  file.close();

  file.open("done.txt");
  while(getline(file, str))    /*  Count Completed todos */
    completed++;
  file.close();

  cout<<day();
  cout<<" Pending : "<<pending<<" Completed : "<<completed<<endl;
}




/*  Returns present date in yyyy-mm-dd format */

string day()
{
  time_t t = time(NULL);
	string s = ctime(&t);    /*  Day Month Date hh:mm:ss Year  */

	string year = s.substr(s.size()-5, 4);

	string month = s.substr(4, 3);
	if(month=="Jan")
		month = "01";
	else if(month=="Feb")
		month = "02";
	else if(month=="Mar")
		month = "03";
	else if(month=="Apr")
		month = "04";
	else if(month=="May")
		month = "05";
	else if(month=="Jun")
		month = "06";
	else if(month=="Jul")
		month = "07";
	else if(month=="Aug")
		month = "08";
	else if(month=="Sep")
		month = "09";
	else if(month=="Oct")
		month = "10";
	else if(month=="Nov")
		month = "11";
	else if(month=="Dec")
		month = "12";

	string day="";
	if(s[8] != ' ')
		day+=s[8];
	if(s[9] != ' ')
		day+=s[9];
	if(day.size()==1)
		day='0'+day;

	s = year;
	s+='-';
	s+=month;
	s+='-';
	s+=day;

	return s;    /*  s is now in yyyy-mm-dd format */
}




/*  Converts a string into integer format */
/*  for eg:- "09" is converted to 9 and "11" to 11  */

int int_converted(string str)
{
	int val=0;
	for(long unsigned int i=0; i<str.size(); i++)
	{
    if(str[i]>=48 && str[i]<=57)
		  val=val*10+str[i]-48;
	}
	return val;
}




/*----------------------------------------------------------------------------*/

/*------------------------THANK YOU-------------------------------------------*/
