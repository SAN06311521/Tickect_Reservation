#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
class TravelBus
{
	int busid;
	char destination[200];
	char time[50];
	int max;
	int booked;
		public:
			TravelBus()
			{
				busid=0;
				max=50;
				booked=0;
				strcpy(time,"7:30am");
				strcpy(destination,"");
			}
		void input();
		void display_bus_info();
		void show_bus();
		int getid()
		{
		return busid;
		}
		void book()
		{
		booked++;
		}
		char* getDestination()
		{
		return destination;
		}
		char* getTime()
		{
		return time;
		}
		int Booking()
		{
		return booked;
		}
		int getMax()
		{
		return max;
		}
};
class ticket_book
{
	char name[50];
	TravelBus bus;
	public:
		void generate_ticket(char cname[],TravelBus tb)
		{
			strcpy(name,cname);
			bus=tb;
		}
		void display()
		{
		cout<<"the name of the customer is: "<<name<<endl;
		cout<<"Details of the bus: "<<endl;
		bus.display_bus_info();
		}
};
void TravelBus::input()
{
cout<<"Enter the bus id: ";
cin>>busid;
cout<<"Enter your destination: ";
cin>>destination;
cout<<"Enter the time of the bus: ";
cin>>time;
}
void TravelBus:: show_bus()
{
cout<<"bus id: "<<busid<<endl;
cout<<"destination: "<<destination<<endl;
cout<<"time: "<<time<<endl;
cout<<"maximum seats: "<<max<<endl;
cout<<"booked seats: "<<booked<<endl;
}
void TravelBus::display_bus_info()
{
	cout<<"Bus id: "<<busid<<endl;
	cout<<"Destination: "<<destination<<endl;
	cout<<"time: "<<time<<endl;
	cout<<"number of seats remaining: "<<max-booked<<endl;
}
void main()
{
clrscr();
int i;
fstream f;
fstream g;
TravelBus b;
	do
	{
	cout<<"Press 1 - Add a new bus "<<endl;
	cout<<"Press 2 - Search a bus "<<endl;
	cout<<"Press 3 - Display all buses "<<endl;
	cout<<"Press 4 - Delete a bus "<<endl;
	cout<<"Press 5 - Book a ticket"<<endl;
	cout<<"Press 6 - Display the booked tickets "<<endl;
	cout<<"Press 7 - To take a EXIT";
	cout<<"\nYour choice is : ";
	cin>>i;
		switch(i)
		{
		case 1:
			f.open("travel.txt",ios::app | ios::binary);
			b.input();
			f.write((char*)&b, sizeof(b));
			f.close();
			cout<<"Bus is added."<<endl;
			getch();
			clrscr();
			break;
		case 2:
			int id,check=0;
			cout<<"Enter the bus id of the bus to be searched: ";
			cin>>id;
			f.open("travel.txt",ios::in | ios::binary);
			if(f.fail())
				cout<<"The file cannot be opened.";
			else
			{
				while(f.read((char*)&b,sizeof(b)))
				{
					if(b.getid()==id)
					{
						b.display_bus_info();
						check=1;
						break;
					}
				}
				if(check==0)
					cout<<"the bus is not found"<<endl;
			}
			f.close();
			break;
		case 3:
			f.open("travel.txt",ios::in | ios::binary);
			if(f.fail())
				cout<<"Can't open the file."<<endl;
			else
			{
				while(f.read((char*)&b,sizeof(b)))
					b.display_bus_info();
			}
			f.close();
			cout<<"Press a key and continue.";
			getch();
			clrscr();
			break;
		case 4:
			check=0;
			cout<<"Enter the bus to be deleted: ";
			cin>>id;
			f.open("travel.txt",ios::in | ios::binary);
			g.open("temp.txt",ios::out | ios::binary);
			if(f.fail())
				cout<<"file cannot be opened "<<endl;
			else
			{
				while(f.read((char*)&b,sizeof(b)))
				{
					if(b.getid()!=id)
					{
						g.write((char*)&b,sizeof(b));
					}
					else
					{
						b.display_bus_info();
						check=1;
					}

				}
				if(check==0)
					cout<<"the bus is not found."<<endl;
				else
					cout<<"the bus is deleted "<<endl;
			}
			f.close();
			g.close();
			remove("travel.txt");
			rename("temp.txt","travel.txt");
			break;
		case 5:
			char dest[70],cname[50];
			int bid;
			ticket_book t;
			cout<<"Enter the destination: ";
			gets(dest);
			f.open("travel.txt",ios::in | ios::out | ios::binary);
			if(f.fail())
				cout<<"the file cannot be opened."<<endl;
			else
			{
				while(f.read((char*)&b,sizeof(b)))
				{
					if(strcmp(b.getDestination(),dest)==0)
					{
						b.display_bus_info();
						check=1;
						cout<<"Enter the name of the customer: ";
						gets(cname);
						b.book();
						t.generate_ticket(cname,b);
						g.open("ticket.txt",ios::app);
						g.write((char*)&t,sizeof(t));
						g.close();
					f.seekp(f.tellg()-sizeof(b),ios::beg);
					f.write((char*)&b,sizeof(b));
					cout<<"the ticket is booked."<<endl;
					getch();
					break;
					}
				}
				if(check==0)
					cout<<"No such bus exists."<<endl;
			}
			f.close();
			break;
		case 6:
			cout<<"The booked tickets are: "<<endl;
			g.open("ticket.txt",ios::in | ios::binary);
			if(g.fail())
				cout<<"The file cannot be opened."<<endl;
			else
			{
				while(g.read((char*)&t,sizeof(t)))
				t.display();
			}
			g.close();
			cout<<"Press a key and continue - ";
			getch();
		}
	}while(i!=7);
}