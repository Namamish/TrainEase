
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


void cancellation(unsigned long);

//Structure for Storing user's account data.

struct accounts
{
char username[40];
char password[21];
}a,acc;

//Class for storing data of trains.

class traindata
{
public:
long trno;
int fcap[5],scap[5],i,dd[5],mm[5],yyyy[5],days;
char stname[10][30],trname[30];
float distance[10],ffare,sfare;

void display();
void input();
}data;


void traindata::input()
{
start:
clrscr();
cout<<"Enter train number:- ";
cin>>trno;
cout<<"Enter train name:- ";  gets(trname);
cout<<"Enter number of stops:- ";  cin>>i;
clrscr();
cout<<"Enter stops from source to destination"<<endl;
for (int j=0;j<i;j++)
{
cout<<"Enter the station number "<<j+1<<": ";
gets(stname[j]);
cout<<"Enter its distance(in kms.) from source distance:- ";
cin>>distance[j];
}
clrscr();
cout<<"Enter Advanced reservation period(in days):- ";
cin>>days;
cout<<"Enter dates of reservation:- ";
for (j=0;j<days;j++)
{
cout<<"\nDate no. "<<j+1<<": ";
cin>>dd[j]>>mm[j]>>yyyy[j];
cout<<"\nEnter capacity in first class for that day:- ";
cin>>fcap[j];
cout<<"\nEnter capacity in second class for that day:- ";
cin>>scap[j];
}
cout<<"Enter price per km.  for first class:- "; cin>>ffare;
cout<<"Enter price per km.  for second class:- "; cin>>sfare;
ofstream fout("Train.dat",ios::app|ios::binary);
fout.write((char*)&data,sizeof(data));
cout<<"Do you want to enter more records(y/n)? ";
char choice;
cin>>choice;
if (choice=='y') goto start;
cout<<"\nPress any key to return to main menu...";
fout.close();
}


void traindata::display()
{
clrscr();
ifstream fin1("Train.dat",ios::in|ios::binary);
while (1)
{
fin1.read((char*)&data,sizeof(data));
if (fin1.eof())
{
cout<<"\nPress any key to return to admin menu";
break;
}
cout<<"\nTrain number:- ";
cout<<trno<<endl;
cout<<"Train name:- ";  puts(trname);
cout<<"\nPress any key to continue..."<<endl;
getch();
cout<<"\nList of stops from source to destination:- ";
for (int j=0;j<i;j++)
{
cout<<"\nStation number "<<j+1<<": ";
puts(stname[j]);
cout<<"    Distance from source station:  "<<distance[j];
}
cout<<"\nPress any key to continue."<<endl;
getch();
clrscr();
cout<<"\nDates applicable for reservation:- "<<endl;
getch();
for (j=0;j<days;j++)
{
cout<<j+1<<". "<<dd[j]<<"/"<<mm[j]<<"/"<<yyyy[j]<<endl;
cout<<"First class capacity on that day: "<<fcap[j]<<" and of Second class is: "<<scap[j]<<endl;
}
cout<<"\nPrice per km. for first class:- "<<ffare<<endl;
cout<<"\nPrice per km. for second class:- "; cout<<sfare<<endl;
cout<<"\nPress any key to continue...";
getch();
clrscr();
}
fin1.close();
}

//Class for storing ticket's data

class reserve
{
public:
unsigned long trno,bookid,pnr;
int dd,mm,yyyy;
char username[40],boarding[30],upto[30],pname[10][30],trname[30];
int i,Class;
float fare;
reserve()     {pnr=0;}         //Constructor
void book(char[]);
void getdata();
void mybookings(char[]);
}res,res2;


void reserve::book(char user_name[])
{    int j,count=0;
fstream fin("Train.dat",ios::in|ios::out|ios::binary);
float idis,fdis,disp;
strcpy(username,user_name);
start:
clrscr();
cout<<"Enter the train number:- ";    cin>>trno;
cout<<"Enter the boarding station:- ";  gets(boarding);
cout<<"Enter destination:- "; gets(upto);

while (1)
{                                //Beginning of while loop
fin.read((char*)&data,sizeof(data));
if(fin.eof())
{
cout<<"Invalid train number.Re-enter details.\n ";
fin.seekg(0);
goto start;
}
if (data.trno==trno)
{                                //Beginning of condition 1
strcpy(trname,data.trname);
again:
clrscr();
cout<<"You can book on following days:-"<<endl;
for(j=0;j<data.days;j++)
{
cout<<j+1<<". "<<data.dd[j]<<"/"<<data.mm[j]<<"/"<<data.yyyy[j]<<endl;
cout<<"Availability-> First Class: "<<data.fcap[j]<<"\tSecond Class: "<<data.scap[j]<<endl;
}
cout<<"Enter the date in which you want to travel:- ";
cout<<"\nEnter Day-> ";  cin>>dd;
cout<<"Enter Month-> ";  cin>>mm;
cout<<"Enter Year-> ";  cin>>yyyy;
cout<<"Enter Class(1 or 2): "; cin>>Class;
cout<<"Enter number of passengers:- "; cin>>i;
for(j=0;j<data.days;j++)
{
if(data.dd[j]==dd && data.mm[j]==mm && data.yyyy[j]==yyyy)
{
if (Class==1 && i<=data.fcap[j])
break;
else if (Class==2 && i<=data.scap[j])
break;
else
{
cout<<"Seat not available,try again."<<endl;
goto again;}
}
else
{
cout<<"Enter another date. Reservation is not available on the entered date."<<endl;
goto again;
}
}
break;
}              //End of condition 1
}		    //End of while loop
while (1)
{                   //Beginning of while loop
fin.seekg(0);
fin.read((char*)&data,sizeof(data));
if(fin.eof())
{
cout<<"Please check your route and enter again.";
fin.seekg(0);
goto start;
}
if (data.trno==trno)           //Beginning of condition 1
{
for (j=0;j<data.i;j++)
{
if (strcmp(data.stname[j],boarding)==0)
{
idis=data.distance[j];
count++;
}
if (strcmp(data.stname[j],upto)==0)
{
fdis=data.distance[j];
count++;
}
}
disp=fdis-idis;
if (disp>0 && count==2)
{
if (Class==1)
{
fare=data.ffare*res.i*disp;
}
else if (Class==2)
{
fare=data.sfare*res.i*disp;
}
break;
}
else
{
clrscr();
cout<<"Wrong route provided, re- enter route.\n";
cout<<"The route for entered train number "<<trno<<" : "<<trname<<" is: "<<endl;
for (j=0;j<data.i;j++)
cout<<j+1<<". "<<data.stname[j]<<endl;
fin.seekg(0);
getch();
goto  start;
}
}
}  //End of while loop
for (j=0;j<i;j++)
{
cout<<"Enter name of passenger "<<j+1<<" :- ";
gets(pname[j]);
}
randomize();
bookid=1000000001+random(10000000000-1000000001);
clrscr();
cout<<"Your ticket request has been made with booking id: "<<bookid<<".\n";
cout<<"Please pay Rs. "<<fare<<" to IRCTC to book ticket.\n";
cout<<"Pay this amount to Account no.- 13552012000075 and IFSC code: ORBC0101355\nThen, email payment receipt to (care@irctc.co.i) and your ticket will be booked. Thanks.";
cout<<"\nPress any key to continue..";
ofstream fout("Booking.dat",ios::app|ios::binary);
fout.write((char*)&res,sizeof(res));
fout.close();
fin.seekg(0);
while(1)
{ //Beginning of while loop
int pos=fin.tellg();
fin.read((char*)&data,sizeof(data));
if (fin.eof())
break;
if (data.trno==trno)
{//Beginning of condition 1
for(j=0;j<data.days;j++)
{
if (data.dd[j]==dd && data.mm[j]==mm && data.yyyy[j]==yyyy)
{
if (Class==1)
{
data.fcap[j]-=i;
break;
}
else if(Class==2)
{
data.scap[j]-=i;
break;
}
}
}
fin.seekp(pos);
fin.write((char*)&data,sizeof(data));
break;
}//Ending of condition 1
}//Ending of while loop
fin.close();
}


void reserve::getdata()
{
fstream fio("Booking.dat",ios::in|ios::out|ios::binary);
while (1)
{
clrscr();
long pos=fio.tellg();
fio.read((char*)&res,sizeof(res));
if(!fio)
{
cout<<"No more data left to be shown.redirecting to admin menu..."<<endl;
getch();
break;
}
cout<<"Username: "<<username<<endl;
cout<<"PNR: "<<pnr<<endl;
cout<<"Booking id: "<<bookid<<endl;
cout<<"Train number and name:-  "<<trno<<'\t'<<trname<<endl;
cout<<"Date of Journey:- "<<dd<<"/"<<mm<<"/"<<yyyy<<endl;
cout<<"Class: "<<Class<<endl;
cout<<"Passenger's details: "<<endl;
for (int j=0;j<i;j++)
cout<<j+1<<". "<<pname[j]<<endl;
cout<<"Press 'y' for confirming above ticket request.\nPress 'n' for cancelling the ticket request.";
cout<<"\nPress 'e' to return to admin menu.\nElse press any key to view next request.";
char choice;
cin>>choice;
if (choice=='y')
{
randomize(); pnr=1000000001+random(10000000000-1000000001);
fio.seekp(pos);
fio.write((char*)&res,sizeof(res));
cout<<"Ticket confirmed. Press any key to view next booking request."<<endl;
getch();
clrscr();
}
else if(choice=='n')
{
fstream finout("Train.dat",ios::in|ios::out|ios::binary);
while(1)
{       //Beg of while1
int pos2=finout.tellg();
finout.read((char*)&data,sizeof(data));
if(finout.eof())
break;
if(data.trno==trno)
{
for(int j=0;j<data.days;j++)
{
if (data.dd[j]==dd && data.mm[j]==mm && data.yyyy[j]==yyyy)
{
if(Class==1)
data.fcap[j]+=i;
else if(Class==2)
data.scap[j]+=i;
}
}
finout.seekp(pos2);
finout.write((char*)&data,sizeof(data));
finout.close();
break;
}
}//End of while1
cancellation(bookid);
cout<<"Ticket has been cancelled. Re directing to admin menu.... Press any key"<<endl;
getch();
break;
}
else if(choice=='e')
break;
}
fio.close();
}


void reserve::mybookings(char user_name[])
{
int count=0;
clrscr();
ifstream fin("Booking.dat",ios::in|ios::binary);
while (1)
{
fin.read((char*)&res,sizeof(res));
if (!fin)
{
if (count==0)
cout<<"No booking has been made with this account.Press any key to continue..."<<endl;
else if(count>0)
cout<<"No more active bookings.Press any key to continue..."<<endl;
getch();
break;
}
if(strcmp(user_name,username)==0)
{ count++;
if (pnr!=0)
{
cout<<"Pnr: "<<pnr<<endl;
cout<<"Booking id: "<<bookid<<endl;
cout<<"Train number and name:-  "<<trno<<'\t'<<trname<<endl;
cout<<"Date of Journey:- "<<dd<<"/"<<mm<<"/"<<yyyy<<endl;
cout<<"Class: "<<Class<<endl;  cout<<"Amount paid: "<<fare<<endl;
cout<<"Passenger's details: "<<endl;
for (int j=0;j<i;j++)
cout<<j+1<<". "<<pname[j]<<endl;
getch();
}
else   cout<<"Your booking with booking id: "<<bookid<<" is due for payment of: "<<fare<<endl;
cout<<"Do you want to cancel the ticket(y/n)? ";
char choice;
cin>>choice;
if (choice=='y')
{
fstream finout("Train.dat",ios::in|ios::out|ios::binary);
while(1)
{       //Beg of while1
int pos2=finout.tellg();
finout.read((char*)&data,sizeof(data));      if(finout.eof())  break;
if(data.trno==trno)
{
for(int j=0;j<data.days;j++)
{
if (data.dd[j]==dd && data.mm[j]==mm && data.yyyy[j]==yyyy)
{
if(Class==1)
data.fcap[j]+=i;
else if(Class==2)
data.scap[j]+=i;
}
}
finout.seekp(pos2);
finout.write((char*)&data,sizeof(data));
finout.close();
break;
}
}//End of while1
cancellation(bookid);
cout<<"Ticket has been cancelled successfully, redirecting to user menu... "<<endl;
getch();
break;
}
}                          //End of username condition
}
fin.close();
}


void inputpassword(char []);

int registration(char []);



void main()
{
int choice1,choice2,choice3;
char ch,password[21],username[40]; int i;
ifstream fin;
do
{
initial:
clrscr();
cout<<"-------WELCOME TO INDIAN RAILWAYS-----------"<<endl;
cout<<"Main menu:"<<endl<<"Type 1 for Admin mode."<<endl<<"Type 2 for User mode."<<endl<<"Or Type any key to exit."<<endl;
cin>>choice1;
switch(choice1)
{
case 1:
fin.open("Accounts.txt");
inputpassword(password);
fin.read((char*)&a,sizeof(a));
if (strcmp(a.password,password)==0)
{ cout<<"\nWelcome to admin mode. Press any key to continue... "<<endl; getch(); clrscr(); fin.close();  goto amenu;}
else
{
cout<<"\nYou are not allowed to enter in this mode,restarting application... "<<endl;
fin.close();
getch();
goto initial;
}
case 2:
cout<<"Do you have an existing account(y/n): ";
char y_n;
cin>>y_n;
if (y_n=='y')
{
cout<<"Enter your username:- ";
gets(username);
login:
inputpassword(password);
fin.open("Accounts.txt");
while (1)
{
fin.read((char*)&a,sizeof(a));
if(fin.eof())
{
cout<<"\nYour username doesn't exist, do you want to register with this username(y/n)?";
char choice2;
cin>>choice2;
fin.close();
if (choice2=='y'){ clrscr(); goto registr;}
else cout<<"\nThanks for visiting, restarting application...\n";
goto initial;
}
if (strcmp(a.username,username)==0 )
{
if (strcmp(a.password,password)==0)
{cout<<"\nWelcome to user mode. Press any key to continue... "<<endl;
fin.close();
getch();
clrscr();
goto umenu;
}
else {cout<<"\nWrong password, restarting application... "<<endl; fin.close(); goto initial;}
}
}   //End of while loop
}
else
{
clrscr();
cout<<"Enter new username:- ";
gets(username);
registr:
int c=registration(username);
if (!c)
goto login;
}
break;
default:
exit(0);
}
}while(1);
do
{
amenu:
clrscr();
cout<<"\nAdmin menu: "<<endl;
cout<<"Type 1 for creating train details. "<<endl;
cout<<"Type 2 for getting all details of train. "<<endl;
cout<<"Type 3 for getting all bookings. "<<endl;
cout<<"Type 4 for returning to main menu."<<endl;
cout<<"Else type any key to exit."<<endl;
cin>>choice2;
switch (choice2)
{
case 1:
data.input();
getch();
break;
case 2:
data.display();
getch();
break;
case 3:
res.getdata();
break;
case 4:
goto initial;
default:
exit(0);
}
}while(1);
if (0)
{
do
{
umenu:
clrscr();
cout<<"\nUser menu:- "<<endl;
cout<<"Press 1 to book a ticket. "<<endl;
cout<<"Press 2 to view your bookings. "<<endl;
cout<<"Press 3 to return to main menu."<<endl;
cout<<"Else press any key to exit. "<<endl;
cin>>choice3;
switch(choice3)
{
case 1:
res.book(username);
getch();
break;
case 2:
res.mybookings(username);
break;
case 3:
goto initial;
default:
exit(0);
}//End of switch
}while(1);
}
getch();
}                  //End of main() function.


void inputpassword(char password[])
{
char ch; int i;
start:
i=0;
cout<<"Enter password:- ";
while (1)
{
ch=getch();
if (ch!='\b'&&ch!='\r')
{
password[i]=ch;
i++;
cout<<'*';
}
if (ch=='\b'&&i>=1)
{
cout<<"\b \b";
i--;
}
if (ch=='\r')
{
if (i<8)
{
cout<<"Password must be 8 characters long.Please re-enter password\n:- ";
goto start;
}
else if(i>=21)
{
cout<<"Password can't be greater than 20 characters.Please re-enter password\n."<<endl;
goto start;
}
else
{
password[i]='\0';
break;
}
}
}
}



int registration(char username[])
{
char ch; int i;
ifstream fin("Accounts.txt",ios::in);
again:
strcpy(acc.username,username);
while (1)
{
fin.read((char*)&a,sizeof(a));  if (fin.eof())  break;
if (strcmp(a.username,acc.username)==0)
{
cout<<"Username already exists, press 1 to login, else press any key to re-enter"<<endl;
int m;
cin>>m;
if (m==1)   return 0;
else
{
cout<<"\nEnter new username:- ";
gets(username);
goto again;
}
}
}
fin.close();
inputpassword(acc.password);
ofstream fout("Accounts.txt",ios::app);
fout.write((char*)&acc,sizeof(acc));
fout.close();
cout<<"\nAccount created successfully. Login with your created account.";
getch();
return 1;
}

void cancellation(unsigned long book_id)
{
ifstream fin2("Booking.dat",ios::in|ios::binary);
ofstream fout("temp.dat",ios::out|ios::binary);
fin2.seekg(0);
while(1)
{
fin2.read((char*)&res2,sizeof(res));
if(fin2.eof())
break;
if(res2.bookid!=book_id)
fout.write((char*)&res2,sizeof(res));
}
fin2.close();
fout.close();
remove("Booking.dat");
rename("temp.dat","Booking.dat");
}
