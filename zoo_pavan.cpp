#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <ctime>
#include <stdio.h>
using namespace std;
void delete_record_animals()
{
  ifstream file;
  ofstream temp;
  string line;
  int i = 0, flag = 0;
  file.open("animals.txt");
  temp.open("temp.txt");
  file.seekg(0, ios::beg);
  while (getline(file, line))
  {
    for (i = 0; i < line.length(); i++)
    {
      if (line[i] == '$')
        flag = 1;
    }
    if (flag == 1)
    {
      flag = 0;
      continue;
    }
    i = 0;
    while (line[i] != '$' && line[i] != '#')
    {
      temp << line[i];
      i++;
    }
    temp << '#';

    temp << endl;
  }
  file.close();
  temp.close();
  remove("animals.txt");
  rename("temp.txt", "animals.txt");
}



void delete_record_visitors()
{
  ifstream file;
  ofstream temp;
  string line;
  int i = 0, flag = 0;
  file.open("visitor.txt");
  temp.open("temp.txt");
  file.seekg(0, ios::beg);
  while (getline(file, line))
  {
    for (i = 0; i < line.length(); i++)
    {
      if (line[i] == '$')
        flag = 1;
    }
    if (flag == 1)
    {
      flag = 0;
      continue;
    }
    i = 0;
    while (line[i] != '$' && line[i] != '#')
    {
      temp << line[i];
      i++;
    }
    temp << '#';

    temp << endl;
  }
  file.close();
  temp.close();
  remove("visitor.txt");
  rename("temp.txt", "visitor.txt");
}
class Animals
{
  char animal_id[20];
  char animal_name[20];
  char age[20];
  char status[20];
  char animal_type[20];
  char buffer[200];
  

public:
  void input();
  void output();
  void pack();
  void unpack();
  void Write();
  void search();
   void modify(int mode);
};
class visitors
{
  char visitor_id[20];
  char visitor_name[20];
  char visitor_address[25];
  char entry_time[10];
  char exit_time[10];
  char buffer[200];

public:
  void input();
  void output();
  void pack();
  void unpack();
  void Delete();
  void Write();
  void search();
  void modify(int mode);
};
void Animals::input()
{
  cout<<"enter the animal id"<<endl;
  cin>>animal_id;
  cout<<"enter the animal name"<<endl;
  cin>>animal_name;
  cout<<"enter the animal age"<<endl;
  cin>>age;
  cout<<"enter the animal status"<<endl;
  cin>>status;
  cout<<"enter the animal type"<<endl;
  cin>>animal_type;

}
void Animals::output()
{
  system("CLS");
  fstream file;
  string line;
  int i =0;
  file.open("animals.txt",ios::out|ios::in);
  file.seekg(0, ios::beg);
  while( getline(file,line)  )
  {
    for(i=0;i<line.length();i++)
    {
      buffer[i] = line[i];
    }
    unpack();
    cout<<"---------------------------------"<<endl;
  cout<<"animal id:"<<animal_id<<endl;
  cout<<"animal name:"<<animal_name<<endl;
  cout<<"animal age:"<<age<<endl;
  cout<<"animal status:"<<status<<endl;
  cout<<"animal type:"<<animal_type<<endl;
  cout<<"-----------------------------------"<<endl;
  }
}

void Animals::pack()
{

  strcpy(buffer, animal_id);
  strcat(buffer, "|");
  strcat(buffer, animal_name);
  strcat(buffer, "|");
  strcat(buffer, age);
  strcat(buffer, "|");
  strcat(buffer, status);
  strcat(buffer, "|");
  strcat(buffer, animal_type);
  strcat(buffer, "|");
  strcat(buffer, "#");
}
void Animals ::unpack()
{

  char *ptr = buffer;
  while (*ptr != '#')
  {
    if (*ptr == '|')
      *ptr = '\0';
    ptr++;
  }
  ptr = buffer;
  strcpy(animal_id, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(animal_name, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(age, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(status, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(animal_type, ptr);
}
void Animals ::Write()
{
  fstream os("animals.txt", ios::out | ios::app);
  os.write(buffer, strlen(buffer));
  os << endl;
  os.close();
}
void Animals ::search()
{
     int found=0;
     char key[30];
     fstream is("animals.txt",ios::in);
     cout<<"enter the id of animal to be searched"<<endl;
     cin>>key;
      
      while(!is.eof()&& !found)
      {
          is.read(buffer,sizeof(buffer));
          unpack();
          if(strcmp(animal_id,key)==0)
          {   
              cout<<"record found!!!"<<endl;
              output();
              found=1;
          }
      }
      if(!found)
      cout<<"not found"<<endl;
      is.close();
 

}
void Animals ::modify(int mode = 0)
{
    char key[30];
     char del='$';
    cout<<"enter the animal id :"<<endl;
    cin>>key;
    int found=0;
    fstream is;
    is.open("animals.txt",ios::in|ios::out);
    while(!is.eof())
    {
        is.getline(buffer,sizeof(buffer));
        unpack();
        int len = strlen(buffer);
        if(strcmp(animal_id,key)==0)
        {
            int pos=is.tellg();
            pos=pos-len-2;
            is.seekg(pos,ios::beg);
            is<<del;
            if(mode == 0)
            {
            cout<<"enter 1:animal_name/n2:animal_age/n3:animal_status/n4:animal_type"<<endl;
            cout<<"what to modify?"<<endl;
            int ch;
            cin>>ch;
            switch (ch)
            {
            case 1:cout<<"animal_name:";
                   cin>>animal_name;
                            break;
            case 2:cout<<"animal_age:";
                   cin>>age;
                            break;
            case 3:cout<<"animal_status:";
                   cin>>status;
                            break;
            case 4:cout<<"animal_type:";
                   cin>>animal_type;
                            break;
                            
                default:
                cout<<"wrong choice!!!";
                exit(0);
                
            }
            }
            else{
               {
          cout << "Animal Details Deleted !!!" << endl;
          animal_id[0] = '$';
        }
            }
            found=1;
            pack();
            Write();
            
            break;
        }
    }
    if(!found)
    cout<<"animal id cannot matchs "<<endl;
    
    is.close();
    delete_record_animals();
}

void Animals_menu()
{
  int choice = 1;
  Animals ob;
  system("CLS");
  while (choice < 6 && choice > 0)
  {
    char key[30];

    cout << "1> Insert an Animal Info " << endl;
    cout << "2> Display all Animal Info " << endl;
    cout << "3> Search for a Animal: " << endl;
    cout << "4> Modify an Animal Details: " << endl;
    cout << "5> Delete an Animal Details" << endl;
    cout << "6> Back to Previous Section " << endl;
    cout << "Enter the Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ob.input();
      ob.pack();
      ob.Write();
      break;
    case 2:

      ob.output();
      break;
    case 3:

     
      ob.search();
      break;
    case 4:
        ob.modify();
        break;
    case 5:
        ob.modify(1);
        break;
        
    }
  }
}

/* :::::::::::::::::::::VISITOR CLASS METHODS ::::::::::::::::::::::::*/
void visitors::input()
{
  
  cout<<"enter the visitor id"<<endl;
  cin>>visitor_id;
  cout<<"enter the visitor name"<<endl;
  cin>>visitor_name;
  cout<<"enter the visitor address"<<endl;
  cin>>visitor_address;
  cout<<"enter the visitor entry time"<<endl;
  cin>>entry_time;
  cout<<"enter the visitor exit time"<<endl;
  cin>>exit_time;

}
void visitors::output()
{
  system("CLS");
  fstream file;
  string line;
  int i =0;
  file.open("visitor.txt",ios::out|ios::in);
  file.seekg(0, ios::beg);
  while( getline(file,line)  )
  {
    for(i=0;i<line.length();i++)
    {
      buffer[i] = line[i];
    }
    unpack();
    cout<<"---------------------------------"<<endl;
  cout<<"visitor id:"<<visitor_id<<endl;
  cout<<"visitor name:"<<visitor_name<<endl;
  cout<<"visitor address:"<<visitor_address<<endl;
  cout<<"visitor entry time:"<<entry_time<<endl;
  cout<<"visitor exit time:"<<exit_time<<endl;
  cout<<"-----------------------------------"<<endl;
  }
}
void visitors ::Write()
{
  fstream os("visitor.txt", ios::out | ios::app);
  os.write(buffer, strlen(buffer));
  os << endl;
  os.close();
}
void visitors::pack()
{

  strcpy(buffer, visitor_id);
  strcat(buffer, "|");
  strcat(buffer, visitor_name);
  strcat(buffer, "|");
  strcat(buffer, visitor_address);
  strcat(buffer, "|");
  strcat(buffer, entry_time);
  strcat(buffer, "|");
  strcat(buffer, exit_time);
  strcat(buffer, "|");
  strcat(buffer, "#");
}
void visitors ::unpack()
{

  char *ptr = buffer;
  while (*ptr != '#')
  {
    if (*ptr == '|')
      *ptr = '\0';
    ptr++;
  }
  ptr = buffer;
  strcpy(visitor_id, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(visitor_name, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(visitor_address, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(entry_time, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(exit_time, ptr);

}
void visitors ::search()
{
     int found=0;
     char key[30];
     fstream is("visitor.txt",ios::in);
     cout<<"enter the id of the visitor to be searched"<<endl;
     cin>>key;
      
      while(!is.eof()&& !found)
      {
          is.getline(buffer,sizeof(buffer));
          unpack();
          if(strcmp(visitor_id,key)==0)
          {
              cout<<"record found!!!"<<endl;
              output();
              found=1;
          }
      }
      if(!found)
      cout<<"not found"<<endl;
      is.close();
 

}
void visitors ::modify(int mode=0)
{
    char key[30];
     char del='$';
    cout<<"enter the visitor id to be modified"<<endl;
    cin>>key;
    int found=0;
    fstream is;
    is.open("visitor.txt",ios::in|ios::out);
    while(!is.eof())
    {
        is.getline(buffer,sizeof(buffer));
        unpack();
        int len =strlen(buffer);
        if(strcmp(visitor_id,key)==0)
        {
            int pos=is.tellg();
            pos=pos-len-2;
            is.seekg(pos,ios::beg);
             is<<del;
             if(mode== 0)
             {
            cout<<"enter 1:visitor_name/n2:visitor_address/n3:visitor entry_time/n 4:visitor exit_time"<<endl;
            cout<<"what to modify?"<<endl;
            int ch;
            cin>>ch;
            switch (ch)
            {
            case 1:cout<<"visitor_name:";
                   cin>>visitor_name;
                            break;
            case 2:cout<<"visitor_address:";
                   cin>>visitor_address;
                            break;
            case 3:cout<<"visitor_entry_time:";
                   cin>>entry_time;
                            break;
            case 4:cout<<"visitor exit_time:";
                   cin>>exit_time;
                            break;
           
                default:
                cout<<"wrong choice!!!";
                exit(0);
            }
             }
        else{

        
        cout<<"visitor details deleted!!"<<endl;
        visitor_id[0]='$';
        }
    

            found=1;
            
           if(found==1) {
             pack();
            Write();
            break;
           }
        }
       }
    
    if(!found)
    cout<<"visitor  id cannot matchs "<<endl;
    is.close();
    delete_record_visitors();
}
/*:::::::::::::::::::Visitor menu:::::::::::::::::::*/
void visitors_menu()
{
  char key[30];
  int choice = 1;
  int flag = 0;
  visitors vizitor;
  system("CLS");
  while (choice < 6 && choice > 0)
  {
    cout << "1> Insert A visitor Info " << endl;
    cout << "2> Display all visitor Info " << endl;
    cout << "3> Search a visitor " << endl;
    cout << "4> Modify a visitor Details " << endl;
    cout << "5>Delete a visitor Details " << endl;
    cout << "6> Back to Previous Section " << endl;
    cout << "Enter the choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      vizitor.input();
      if (flag == 0)
      {
        vizitor.pack();
        vizitor.Write();
      }
      break;
    case 2:
      vizitor.output();
      break;
    case 3:
      vizitor.search();
      break;
    case 4:
      vizitor.modify(0);
      break;
      case 5:
      vizitor.modify(1);
      break;
    }
  }
}
      main()
{
  int choice = 1;
  cout << "::::::::::::::::::::::::::::::::::ZOO MANAGEMENT SYSTEM::::::::::::::::::::::::::::::::" << endl;
  while (choice < 3 && choice > 0)
  {
    cout << "1> Query Related to Animals" << endl;
    cout << "2>Query Related to visitors" << endl;
    cout << "3>Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      Animals_menu();
      break;
    case 2:
      visitors_menu();
      break;
    }
    
  }
  system("CLS");
  cout << "############## END of the Animals Management System! Press any key to exit..... ############" << endl;
  getch();
  return 0;
}