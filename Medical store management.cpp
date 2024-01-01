#include<bits/stdc++.h>
#include<windows.h>
#include<stdlib.h>
static int check=0;
using namespace std;
#define ws " "
void desgin(string );
void menu();
void desgin1();
void stock();
static float profit=0,loss=0;
class medicine
{
    public:
    int med_quan,med_mon,med_year;
    float med_price,actual_price;
    string med_name,med_id,line,search_medicine,per_name,delete_medicine,med_s,consumer_name; 
    float total_cost,due_amount,paid_amount;
    void insert();
    int update(string,int);
    void display();
    void search();
    void del(string);
    void expiry();
};
class customer:public medicine
{
   public:
   void cus_display();
   int cus_info();
};
class sales_repo:public customer
{
    public:
    string consumer_name;
    string sal(string);
    void purchase();
    float sear(string);
    void sal_display();
    void upda(string name,float total,float paid,float due);
    
};
void customer::cus_display()
{
    
    ifstream s("bill.txt");
    cout<<"CUSTOMER NAME"<<"\t"<<"TOTAL COST"<<"\t"<<"PAID AMOUNT"<<ws<<"DUE AMOUNT"<<endl;
    if(s){
        while(getline(s,line)){
            stringstream medi(line);
            medi>>consumer_name>>total_cost>>paid_amount>>due_amount;
            cout<<consumer_name<<"\t\t"<<total_cost<<"\t\t"<<paid_amount<<"\t\t"<<due_amount<<endl;
    }   
    }
    s.close();
}
void sales_repo::sal_display()
{
    system("cls");
    desgin("SELLER DETAILS");
    ifstream medfile("sales.txt");
    cout<<"CONSUMER NAME\t\t\tMEDICINE NAME\t\t\t"<<endl;    
    if(medfile){
        while(getline(medfile,line)){
        stringstream medi(line);
        medi>>consumer_name>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year>>med_s;
        if(med_s=="purchased")
        cout<<consumer_name<<"\t\t"<<med_name<<endl;
    }
    medfile.close();
    }
}
void sales_repo::purchase()
{
    fstream sal("sales.txt",ios::app) ;
    cout<<"Enter the Supplier name: ";
    cin>>consumer_name;
    sal<<consumer_name<<ws;
    sal.close();
    medicine::insert();
} 
string sales_repo::sal(string search_medicine)
{
    string x,y;
    ifstream sal("sales.txt") ;
    if(sal){
        while(getline(sal,line)){
            stringstream medi(line);
            medi>>consumer_name>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year>>med_s;
            cout<<x;
             if(med_name==search_medicine && med_s=="purchased"){
                y=consumer_name;
               sal.close();
               return y;
               Sleep(4000);
             }
        }
           sal.close(); 
} 
return " ";
}
void medicine::insert()
{ 
                                desgin("MEDICINE DATA");
                                fstream medfile("medical_stock.txt",ios::app) ;
                                fstream sal("sales.txt",ios::app) ;
                                if(!medfile&&!sal){
                                    cout<<"unable to insert.:";
                                }
                                else{
                                char op;
                              
                                           cout<<"Medicine Name:";
                                           cin>>med_name;
                                            medfile<<med_name<<ws;
                                            sal<<med_name<<ws;
                                            cout<<"Medicine ID:";
                                            cin>>med_id;
                                            medfile<<med_id<<ws;
                                            sal<<med_id<<ws;
                                            cout<<"Medicine quantity:";
                                            cin>>med_quan;
                                            medfile<<med_quan<<ws;
                                            sal<<med_quan<<ws;
                                            cout<<"Medicine price:";
                                            cin>>med_price;
                                            medfile<<med_price<<ws;
                                            actual_price=med_price*med_quan-med_price*0.5*med_quan;
                                            med_price=med_price*med_quan-med_price*0.5*med_quan;
                                            sal<<med_price<<ws;
                                            cout<<"Expriy month:";
                                            cin>>med_mon;
                                            if(med_mon<0 || med_mon>12)
                                            {
                                                
                                                cout<<"The months are from 1 to 12 you have entered wrong month enter a proper month";
                                                cin>>med_mon;
                                            }
                                            sal<<med_mon<<ws;
                                            medfile<<med_mon<<ws;
                                            cout<<"Expiry Year:";
                                            cin>>med_year;
                                            medfile<<med_year<<ws;
                                            sal<<med_year<<ws;
                                            medfile<<actual_price<<ws;
                                            medfile<<"\n";
                                    medfile.close();
                                    med_s="purchased";
                                    sal<<med_s<<"\n";
                                    sal.close();
                                }
                                        
            
            
}
float sales_repo::sear(string name)
{  
    int x=0;
    check=0;
    ifstream s("bill.txt");
    if(s){
        while(getline(s,line)){
            stringstream medi(line);
            medi>>consumer_name>>total_cost>>paid_amount>>due_amount;
             if(consumer_name==name){
              x++;
              check++;
              s.close();
              return due_amount;
             }
             
        }
        if(x!=0){
            s.close(); 
            return 0;
        }
    }   
    return 0;
}
void sales_repo::upda(string name,float total,float paid,float due)
{
int count=0,l;
ofstream fp1("removing.txt");
ifstream medfile("bill.txt");
string x;
if(medfile){
        while(getline(medfile,line)){
            
            stringstream medi(line);
            medi>>consumer_name>>total_cost>>paid_amount>>due_amount;
            if(consumer_name==name){
            cout<<due<<" ";
            total_cost+=total;
            paid_amount+=paid;
            due_amount=due;
            if(due==0)
            total_cost=paid_amount;
            fp1<<consumer_name<<ws<<total_cost<<ws<<paid_amount<<ws<<floor(due_amount * 100.0) / 100.0<<endl;
            count++;
            }
            else
            {         
                fp1<<consumer_name<<ws<<total_cost<<ws<<paid_amount<<ws<<due_amount<<endl;   

            }
        }
        }
        medfile.close();
        fp1.close();
        if(count)
        {
        ifstream fp1("removing.txt");
        ofstream medfile("bill.txt");
        while(getline(fp1,line))
        {
        medfile<<line<<endl;
        }
        }
        medfile.close();
        fp1.close();
}                
int medicine::update(string a,int q)
{
int count=0,l;
ofstream fp1("removing.txt");
ifstream medfile("medical_stock.txt");
fstream s("sales.txt",ios::app);
sales_repo n;
string x;
if(medfile){
        while(getline(medfile,line)){
            stringstream medi(line);
            medi>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year;
            if(med_name==a){
            
            if(q==0)
            {
                cout<<"Enter the quantity of the medicine"<<endl;
                cin>>med_quan;
                cout<<"Enter the month of expiry"<<endl;
                cin>>med_mon;
                cout<<"Enter the year of expiry"<<endl;
                cin>>med_year;
                med_quan=med_quan+q;
                count+=1;
                fp1<<med_name<<ws<<med_id<<ws<<med_quan<<ws<<med_price<<ws<<med_mon<<ws<<med_year<<endl;
                consumer_name=n.sal(med_name);
                med_s="purchased";
                s<<consumer_name<<ws<<med_name<<ws<<med_id<<ws<<med_quan<<ws<<med_price<<ws<<med_mon<<ws<<med_year<<ws<<med_s<<endl;
            }
            else if(q!=0)
            {
            l=med_quan=med_quan-q;
            count+=1;
            fp1<<med_name<<ws<<med_id<<ws<<med_quan<<ws<<med_price<<ws<<med_mon<<ws<<med_year<<endl;
            }
            }
            else
            {
                fp1<<med_name<<ws<<med_id<<ws<<med_quan<<ws<<med_price<<ws<<med_mon<<ws<<med_year<<endl;
            }
        }
        }
        medfile.close();
        fp1.close();
        if(count)
        {
        ifstream fp1("removing.txt");
        ofstream medfile("medical_stock.txt");
        while(getline(fp1,line))
        {
        medfile<<line<<endl;
        }
        }
        medfile.close();
        fp1.close();
        s.close();
        return l;
}                
void medicine::expiry()
{
 time_t now = time(0);
 tm *ltm = localtime(&now);
 ifstream medfile("medical_stock.txt");
 fstream fp("sales.txt",ios::app);
 sales_repo y;
 if(medfile&&medfile.eof())
 {
    while(getline(medfile,line))
    {
        stringstream medi(line);
        medi>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year;
        if(med_mon<=(1+ltm->tm_mon)&& (med_year<=1900 + ltm->tm_year))
        {
            char t;
            cout<<med_name<<"is expired";
            string x=med_name;
            med_s="Expired";
            consumer_name="NONE";
            fp<<consumer_name<<ws<<med_name<<ws<<med_id<<ws<<med_quan<<ws<<med_price<<ws<<med_mon<<ws<<med_year<<ws<<med_s<<endl;
            del(x);
            display();
            cout<<"The item has been deleted"<<endl;
            cout<<"Do you want to restock the item "<<x<<endl;
            cin>>t;
            fp.close();
            if(t=='y'||t=='Y')
            y.purchase();
        }
    }
 }
 medfile.close();

}
void medicine::search()
{  
    int x=0;
    desgin("SEARCH MEDICINE");
    cout<<"Enter an medicine to search";
    cin>>search_medicine;
    ifstream medfile("medical_stock.txt");
    if(medfile){
        while(getline(medfile,line)){
            stringstream medi(line);
            medi>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year;
             if(med_name==search_medicine){
                x++;
               cout<<"Medicine name:"<<med_name<<endl<<"Medicine id"<<med_id<<endl<<"Medicine quantity:"<<med_quan<<endl<<"Medicine price"<<med_price<<endl<<"Medicine exp"<<"Month"<<med_mon<<"Year"<<med_year<<endl;
             }
        }
            medfile.close(); 
    }
    if(x!=1){
    cout<<"medicine is not found:";
    }    
}
void medicine::display()
{
    system("cls");
    desgin("MEDICINE DATA");
    ifstream medfile("medical_stock.txt");
    cout<<"MEDICINE NAME\t\t\tMEDICINE ID\t\tMEDICINE QUANTITY\t\t\tMEDICINE PRICE\t\t\tMEDICINE EXPIRY\n";
    
    if(medfile){
        while(getline(medfile,line)){
        stringstream medi(line);
        medi>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year;
        cout<<med_name<<"\t\t     "<<med_id<<"\t\t\t\t   "<<med_quan<<"\t\t\t   "<<med_price<<"\t\t\t   "<<med_mon<<"\t\t\t   "<<med_year<<endl;       
    }
    medfile.close();
    }
}

void medicine::del(string name)
{
    if(name==" ")
    {
    cout<<"Input Medicine name which you want to delete:";
    cin>>delete_medicine;
    }
    else
    delete_medicine=name;
    fstream medfile("medical_stock.txt",ios::in);
    fstream temp("temp_stock.txt",ios::out | ios::trunc);
    if(medfile){
        while(getline(medfile,line)){
        stringstream medi(line);
        medi>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year;
        if(med_name==delete_medicine||med_name==name){
            loss=abs(actual_price*med_quan-med_price*med_quan);
            continue;
        }
        else
        {
            temp<<med_name<<ws<<med_id<<ws<<med_quan<<ws<<med_price<<ws<<med_mon<<ws<<med_year<<endl;
        }
        }
    }
    medfile.close();
    temp.close();
medfile.open("medical_stock.txt",ios::out | ios::trunc);
 temp.open("temp_stock.txt",ios::in);
 while(getline(temp,line))
 {
     medfile<<line<<endl;
 }
medfile.close();
temp.close();
}
int customer::cus_info()
{
desgin("MEDICAL BILLING");
int k=1,j=1,quantity[100],z,code,count,m=-1,q,l,t=0,me;
string a[100],dup[100],name,up[50];
char s;
float cost[100],total=0,due=0,paid=0; //total_cost is used for printing total
medicine x;
sales_repo y;
x.display();
cout<<"Enter the name of the customer"<<endl;
cin>>consumer_name;
due=y.sear(consumer_name);

total=0;
fstream bill_s("bill.txt",ios::app);
fstream stockfile("sales.txt",ios::app);

while(1)
{
cout<<"Enter the name of item\n";
cin>>name;
ifstream medfile("medical_stock.txt");

count=0;
if(medfile && stockfile){
        while(getline(medfile,line)){
            stringstream medi(line);
            medi>>med_name>>med_id>>med_quan>>med_price>>med_mon>>med_year;
             if(med_name==name){
              {
                  
                  
                cout<<"MedicalID\t"<<med_id<<"\t\tMedicine Name\t"<<med_name<<"\t\tCost per unit\t"<<med_price;
                count=1;
                a[k]=med_id;
                cout<<"\nEnter quantity :";
                cin>>quantity[k];
                if(quantity[k]<=med_quan)
                {
                    t=1;
                q=quantity[k];
                cost[k]=quantity[k]*med_price;
                med_s="SOLD";
                stockfile<<consumer_name<<ws<<med_name<<ws<<med_id<<ws<<q<<ws<<cost[k]<<ws<<med_mon<<ws<<med_year<<ws<<med_s<<endl;
                cout<<"Cost="<<cost[k]<<endl;

                dup[k]=med_name;
                me=x.update(med_name,q);
                profit+=med_price*q-actual_price*q;
                 if(me==0){
                m+=1;
                up[m]=med_name;
                cout<<up[m];
                }
                total+=cost[k];
                k++;
                }
                else{
                    cout<<med_quan<<"Out of stock\n"<<"Do you want another item";
                    cost[k]=0;
                    k--;
                    }
              }
                }
               
                }
        }
        if(count==0)
        {
            cout<<"The tablet is not available in the store\n";
        }
        cout<<"\nPress 0 if you don't want to add another item or else press 1\n";
        cin>>z;
        stockfile;
        medfile.close();
        stockfile.close();

if(z==0){
    l=total=total+total*0.18;
    cout<<"Due amount"<<due+total;
    total=due+total;
    cout<<"Enter the amount had been paid"<<endl;
    cin>>paid;
    due=total-paid; 
    if(!y.sear(consumer_name)&&check==0)
    bill_s<<consumer_name<<ws<<total<<ws<<paid<<ws<<floor(due * 100.0) / 100.0<<endl;
    else
    y.upda(consumer_name,total,paid,due);  
break;
}
}
if(t!=0)
{
cout<<"\t\t\t";
desgin("RECIEPT");
cout<<"\t\t\t"<<per_name<<endl;
cout<<"\t\t\tITEM NAME\t\t\tQUANTITY\t\t\tCOST\n";
total=0;
while(j<k)
{
cout<<"\t\t\t"<<dup[j]<<"\t\t\t"<<quantity[j]<<"\t\t\t"<<cost[j]<<endl;
total+=cost[j];
j++;
}
desgin1();
cout<<"\t\t\t\tPRICE\t\t\t"<<total<<"\n";
total+=(total*18)/100;
desgin1();
cout<<"\t\t\t\t\tGRAND TOTAL WITH 18%%GST\t"<<total<<"\n";
desgin1();
cout<<"\t\t\t\t\tPAID AMOUNT\t\t"<<paid<<"\n\t\t\t\t\tDUE AMOUNT\t\t"<<due;

cout<<endl;
desgin1();
cout<<"\t\t\t\t\tTHANKYOU!!VISIT AGAIN\n\n\t\t\t";
}
else
cout<<"0 items have taken"<<endl;
Sleep(4000);
bill_s.close();
for(int j=0;j<=m;j++)
{
    cout<<up[j]<<"the quantity is less than the required do you want to update(y/n)"<<endl;
    cin>>s;

    if(s=='y'||s=='Y')
    {

        update(up[j],0);
    }
    else
    del(up[j]);
}
return(0);
}


int main()
{
    while(1)
    {
    Sleep(4000);
    system("cls");
    desgin("MEDICAL STORE MANAGMENT SYSTEM");
    menu();
    }
    return 0;
}
void menu()
{
  int choice;
  medicine a;
  a.expiry();
  cout<<"\t\t\t1->Medical Stock record"<<endl;
  cout<<"\t\t\t2->Customer information and billing system"<<endl;
  cout<<"\t\t\t3->Sale and Supplier Managment"<<endl;
  cout<<"\t\t\t4->EXIT"<<endl;
  cout<<"Enter your choice"<<endl;
  cin>>choice;
  customer b;
  sales_repo x;
  switch(choice)
  {
      case 1:stock(); 
             break;
      case 2:{
            cout<<"1->customer information"<<endl<<"2->Billing\nEnter your choice";
            int a;
            cin>>a;
            if(a==1)
            b.cus_display();
            else if(a==2)
            b.cus_info();
            }
             break;
      case 3:{ cout<<"1->seller details \n2->Insertion of new seller details and medicine name\n"<<endl;
               int a;
               cin>>a;
               if(a==1)
               x.sal_display();
               else if(a==2)
               x.purchase();
            }
                break;
      case 4:{  
                time_t ttime = time(0);
                char* dt = ctime(&ttime);
                fstream r("sales_report.txt",ios::app);
                r<<profit<<ws<<loss<<ws<<dt<<endl;
                r.close();
                exit(0);
            }
  }
}
void stock()
{
    medicine a;
    int choice;
    string s;
    a.expiry();
    system("cls");
             desgin("MEDICAL STOCK RECORD");
             cout<<"\t\t\t\t1->Display Stock\n"<<endl;
             cout<<"\t\t\t\t2->Search Item\n"<<endl;
             cout<<"\t\t\t\t3->Remove a item\n"<<endl;
             cout<<"Press a key to choose"<<endl;
             cin>>choice;
             switch(choice)
             {

                        case 1: a.display();
                                 break;
                        case 2: cout<<"input Medicine name with u want to search:"<<endl;
                                a.search();
                                break;
                        case 3: a.del(" ");
                                break;
                        default: cout<<"Entered wrong choice";
             
             }
}
void desgin(string str)
{
    time_t ttime = time(0);
    char* dt = ctime(&ttime);
    cout<<"\t\t\t_____________________"<<endl<<endl;
    cout<<"\t\t\t\t\t"<<str<<"\t\t\t\t"<<endl;
    cout<<"\t\t\t_____________________"<<endl<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<dt<<endl<<endl;
}
void desgin1()
{
    cout<<"\t\t\t-----------------------------------------------------------"<<endl;
}
