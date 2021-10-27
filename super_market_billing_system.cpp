#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>

class product
{
    int prno;
    char name[20];
    float price,qty,dis,tax;
public:
    void createpr()
    {
	cout<<endl<<"Enter the product number"<<endl;
	cin>>prno;
	cout<<"Enter the product name"<<endl;
	gets(name);
	cout<<"Enter the price of the product"<<endl;
	cin>>price;
	cout<<"Enter the discount percentage"<<endl;
	cin>>dis;

    }
    void showpr()
    {

	cout<<"Product number: "<<prno<<endl;
	cout<<"Product name: "<<name<<endl;
	cout<<"Product price: "<<price<<endl;
	cout<<"Discount percentage: "<<dis<<endl;

    }
    int retprno()
    {
	return prno;
    }
    float retprice()
    {
	return price;
    }
    char *retname()
    {
	return name;
    }
    int retdis()
    {
	return dis;
    }
};
fstream fp;
product pr;
int writepr()
{
    fp.open("pratik.dat",ios::app);
     pr.createpr();
    fp.write((char*)&pr,sizeof(product) );
    fp.close();
    return 0;

}
int disp()
{   clrscr();
    cout<<"Display all the records: "<<endl;
    fp.open("pratik.dat",ios::in);
    while(!fp.eof())
    {
	fp.read((char*)&pr,sizeof(product));
	pr.showpr();
	break;
    }
    fp.close();
    return 0;
}
int findproduct()
{  clrscr();
    int flag=0,n;
    cout<<"Enter the product number: "<<endl;
    cin>>n;
    fp.open("pratik.dat",ios::in|ios::out);
    while(!fp.eof())
    {
	fp.read((char*)&pr,sizeof(product));
	if(pr.retprno()==n)
	{
	    pr.showpr();
	    flag=1;
	    break;
	}
    }
    fp.close();
    if(flag==0)
    {
	cout<<"Record does not exist"<<endl;
    }
    return 0;
}
int modifypr()
{
    int no,found=0;
    long long pos;
    system("cls");
    cout<<"Enter the product number:"<<endl;
    cin>>no;
    fp.open("pratik.dat",ios::app);

    while((!fp.eof())&&found==0)
    {
       fp.read((char*)&pr,sizeof(product));
       if(pr.retprno()==no)
       {
	   pr.showpr();
	   cout<<"Enter the new details of the product:"<<endl;
	   pr.createpr();
	   int long long pos=-1*sizeof(pr);
	   fp.seekp(pos,ios::cur);
	   fp.write((char*)&pr,sizeof(product));
	   cout<<"The details of the product has been modified"<<endl;
	   found=1;
	 }


       }

    fp.close();
    if(found==0)
    {
	cout<<"Record not found"<<endl;
    }
    getch();
    return 0;
}
int deletepr()
{
  int num;
    system("cls");
    cout<<"Enter the product number of the product you want to delete"<<endl;
    cin>>num;
    fp.open("pratik.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temporary.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
    {
	if(pr.retprno()!=num)
	{
	    fp2.write((char*)&pr,sizeof(product));
	}
    }
    fp2.close();
    fp.close();
    remove("pratik.dat");
    rename("Temporary.dat","SMBS.dat");
    cout<<"The record of the product has been deleted"<<endl;
    return 0;
}
int menu()
{
    system("cls");
    fp.open("pratik.dat",ios::in);
    if(!fp)
    {
	cout<<"Error:The file cannot be opened, head over to the Admin menu to create a new file."<<endl;
	exit(0);
    }
    else
    cout<<"Product Menu:"<<endl;
    cout<<"---------------------------------------------"<<endl;
    cout<<"Product number:\t\tName:\t\tPrice:"<<endl;
    cout<<"---------------------------------------------"<<endl;
    while(!fp.eof())
    { fp.read((char*)&pr,sizeof(product));
	cout<<"\t"<<pr.retprno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	break;
    }
    fp.close();
    return 0;
}
int placeorder()
{
    system("cls");
    int order[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';

    menu();


    cout<<"\n\n\n\n---------------------------------------------";
    cout<<"\n-Place your order-"<<endl;
    cout<<"---------------------------------------------"<<endl;
    do
    {
	cout<<"Enter the product number:"<<endl;
	cin>>order[c];
	cout<<"Enter the quantity:"<<endl;
	cin>>quan[c];
	c++;
	cout<<"Do want to order another product? (Y/N):"<<endl;
	cin>>ch;
    }while(ch=='y'||ch=='Y');
    cout<<"Invoice:"<<endl;
    cout<<"Product number\tProduct Name\tQuantity\tPrice\tAmount\tdiscounted price"<<endl;
    for(int x=0;x<=c;x++)
    {
	fp.open("pratik.dat",ios::in);
	fp.read((char*)&pr,sizeof(product));
	while(!fp.eof())
	{
	    if(pr.retprno()==order[x])
	    {
		amt=pr.retprice()*quan[x];
		damt=amt-(amt*pr.retdis()/100);
		cout<<"\n"<<"\t"<<order[x]<<"\t"<<pr.retname()<<"\t\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
		total=total+damt;
	    }
	    fp.read((char*)&pr,sizeof(product));
	    break;
	}
	fp.close();
    }
    cout<<"\n\n\t\t\t\t\tTotal:"<<total;
    return 0;
}
int into()
{
    cout<<"    -----Super Market Billing System -----"<<endl;
   cout<<"\nMade by: pratik kumar"<<endl;

    return 0;
}
int admin()
{
    clrscr();
    char ch2;
    cout<<"Admi nistration menu:"<<endl;
    cout<<"1.Create a product."<<endl;
    cout<<"2.Display all products."<<endl;
    cout<<"3.Display a specific product."<<endl;
    cout<<"4.Modify a product"<<endl;
    cout<<"5.Delete a product."<<endl;
    cout<<"6.View product menu."<<endl;
    cout<<"7.Back to main menu()."<<endl;
    cout<<"Enter your choice:"<<endl;
   cin>>ch2;
    switch(ch2)
    {
    case '1':
	{
	    writepr();
	    break;
	}
    case '2':
	{
	    disp();
	    getch();
	    break;
	}
    case '3':
	{

	    findproduct();
	    getch();
	    break;
	}
    case '4':
	{
	   modifypr();
	   break;
	}
    case '5':
	{
	    deletepr();
	    getch();
	    break;
	}
    case '6':
	{
	    menu();
	    getch();
	}
    case '7':
	{
	 break;
	}
	default: cout<<"\a";admin();
    }
    return 0;
}
int main()
{   clrscr();
    into();
    char ch;

    do
    {
	cout<<"\n\nWelcome to The Super Market Billing System Application"<<endl;
	cout<<"Main Menu:"<<endl;
	cout<<"1.Customer"<<endl;
	cout<<"2.Administrator"<<endl;
	cout<<"3.Exit"<<endl;
	cout<<"Enter your choice:"<<endl;
	cin>>ch;
	switch(ch)
	{
	case '1':
	    {
		placeorder();
		getch();
		break;
	    }
	case '2':
	    {
		admin();
		break;
	    }
	case '3':
	    {
		exit(0);
	    }
	    default:cout<<"\a";
	}
	system("cls");
    }while(ch!=3);
    return 0;
}

