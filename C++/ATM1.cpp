#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

struct accholder
{
    int wdamount, atmpin, dpamount, amount, yyy, ddd, mmm;
    string name, type;
} r;

class Bank
{
public:
    int otp, legit;
    string dta[10];

public:

    void datetime()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        cout << "DATE & TIME: " << dt;
    }

    void pinchange(string usr)
    {
        int cpin, newpin;
        cout << "Enter pin:";
        cin >> cpin;
        if (cpin == r.atmpin)
        {
            cout << "Enter the new pin:";
            cin >> newpin;
            r.atmpin = newpin;
            write_file(usr);
        }
    }

    void write_file(string id)
    {
        string fln = id + ".txt";
        ofstream o;
        o.open(fln);
        o << r.atmpin << "\t"
          << r.name << "\t"
          << r.yyy << "/" << r.mmm << "/" << r.ddd << "\t"
          << r.type << "\t"
          << r.amount;
        o.close();
    }

    void read_usrfl(string uname)
    {  
        int j=0;
        string users;
        ifstream i;
        i.open("usrfl.txt");
        getline(i,users);
        split(users);
        for( string dat : dta)
        {
            if(uname.compare(dat)==0)
            {
                legit = 1;
            }
            j++;
        }
    }

    void read_file(string id)
    {
        string fln = id + ".txt", data;
        ifstream p;
        p.open(fln);
        getline(p, data);
        p.close();
        split(data);
        r.atmpin = stoi(dta[0]);
        r.name = dta[1];
        r.type = dta[3];
        r.amount = stoi(dta[4]);
    }

    void split(string str)
    {
        int a = 0;
        for (int i = 0; i < str.length(); i++)
        {
            string b = "";
            while (str[i] != '\t' && i < str.length())
            {
                b += str[i];
                i++;
            }
            dta[a] = b;
            a++;
        }
    }

    void deposit(string fln)
    {
        int dpamount;
        cout << "Enter the Deposit amount:";
        cin >> dpamount;
        r.amount = r.amount + dpamount;
        write_file(fln);
        cout << "Deposit successful.";
    }

    void rcpt(int amnt)
    {
        cout << "              Transaction Receipt\n";
        cout << "                 Macrowyre Bank\n";
        datetime();
        cout << "\n";
        cout << "Withdrawl Amount: " << amnt << "\n";
        cout << "Transaction Charge: 0.00"
             << "\n";
        cout << "Remaining balance:" << r.amount << "\n";
        cout << "           Thank you for using our ATM\n";
        exit(0);
    }

    void display()
    {
        string uname;
        int key;
        cout << "Enter the User ID:";
        cin.ignore();
        getline(cin, uname);
        read_file(uname);
        cout << "Enter PIN:";
        cin >> key;

        if (r.atmpin == key)
        {
            cout << "User ID"
                 << "\t\t"
                 << "Name"
                 << "\t\t"
                 << "\t\t"
                 << "Type"
                 << "\t\t"
                 << "Balance" << endl;
            cout << "\t\t" << r.name << "\t\t"
                 << "\t\t" << r.type << "\t\t" << r.amount << endl;
        }
        exit(0);
    }

    void setpin()
    {
        int abc, newpin;
        cout << "OTP has been sent to the file 'APP' \n";

        cout << "Enter the  OTP:";
    take:
        cin >> abc;
        if (abc == otp)
        {
            cout << "Set a new pin:";
            cin >> newpin;
            r.atmpin = newpin;
            cout << "Your new pin has been successfully changed.\n";
        }
        else
        {
            int A = 1;
            if (A > 3)
            {
                cout << "You have entered wrong OTP 3 times !!!\n";
                cout << "Further process Terminated due to security reason\n";
                exit(0);
            }
            cout << "Incorrect OTP!!!\n";
            cout << "Re-enter the OTP\n";
            A++;
            goto take;
        }
    }

    void userdetail()
    {
        char a;
        do
        {
            cout << "Enter the following data:" << endl;
            cout << "Full Name:";
            cin.ignore();
            getline(cin, r.name);
            cout << "Date of birth (yyyy/mmmm/dddd):";
            cin >> r.yyy >> r.mmm >> r.ddd;
            cout << "Account type:";
            cin.ignore();
            cin >> r.type;
            cout << "Deposite amount:";
            cin.ignore();
            cin >> r.amount;
            otpp();
            setpin();
            write_file(r.name);
            fstream o;
            o.open("usrfl.txt", ios :: app);
            o << r.name << "\t";
            cout << "Do you want to add another [y/n]:";
            cin >> a;
        } while (a == 'y');
    }

    void balanceinquiry(string fln)
    {
        cout << endl;
        cout << "            TRANSACTION RECEIPT" << endl;
        cout << "              BALANCE ENQUIRY" << endl;
        cout << "BANK NAME: MACROWYRE BANK" << endl;
        datetime();
        read_file(fln);
        cout << "ACCOUNT HOLDER'S NAME:" << r.name << endl;
        cout << "ACTUAL BALANCE is:" << r.amount << endl;
        cout << "AVAILABLE BALANCE is:" << (r.amount) << endl;
        cout << "CHARGE AMOUNT: 0.00" << endl;
        exit(0);
    }

    void fastcash()
    {

        cout << "1. 500" << endl;
        cout << "2. 1000" << endl;
        cout << "3. 2000" << endl;
        cout << "4. 5000" << endl;
        cout << "5. 10000" << endl;
        cout << "6. 15000" << endl;
    }

    void withdraw(string uname,int amt)
    {
        char receipt;
        transcation();
        r.amount = r.amount - amt;
        write_file(uname);
        cout << "Do you wanna receive receipt(y/n):";
        cin >> receipt;
        if (receipt == 'y' || receipt == 'Y')
        {
            rcpt(amt);
            exit(0);
        }
        else if (receipt == 'n' || receipt == 'N')
        {
            cout << "Thank you for using our ATM.";
            exit(0);
        }
    }

    void transcation()
    {
        cout << "Your transaction is being processed ";
        for (int i = 0; i < 6; i++)
        {

            cout << "."
                 << " ";
            Sleep(500);
        }
        cout << endl;
    }

    void otpp()
    {
        srand(time(NULL));
        otp = (rand() % 999999) + 100000; // Generates OTP
        ofstream file("APP.txt");
        file << otp;
        file.close();
    }
};

int main()
{
    Bank obj1;
    int choice;
    static int B = 0;

gett:
    cout << endl;
    obj1.transcation();
    cout << "1. Create new account" << endl;
    cout << "2. Enter your pin" << endl;
    cout << "3. Search account" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;

    if (choice == 1)
    {
        cout << endl;
        obj1.userdetail();
        goto gett;
    }
    else if (choice == 2)
    {
        int key;
        string uname;
    get:
        cout << "Enter your username:\n ";
        cin.ignore();
        getline(cin, uname);
        obj1.read_usrfl(uname);
        if( obj1.legit == 1)
        {
            obj1.read_file(uname);
            cout << "Enter pin:\n";
            cin >> key;
            if (key == r.atmpin)
            {
                cout << "1.Balance Inquiry" << endl;
                cout << "2.Fast Cash" << endl;
                cout << "3.Cash Withdrawl" << endl;
                cout << "4.Cash Deposit " << endl;
                cout << "5.Pin Change" << endl;
                cin >> choice;

                switch (choice)
                {
                case 1:
                    obj1.balanceinquiry(uname);
                    break;

                case 2:
                    obj1.fastcash();
                    int b;
                    cin >> b;
                    if (b == 1)
                    {
                        obj1.withdraw(uname,500);
                    }

                    else if (b == 2)
                    {
                        obj1.withdraw(uname,1000);
                    }

                    else if (b == 3)
                    {
                        obj1.withdraw(uname,2000);
                    }

                    else if (b == 4)
                    {
                        obj1.withdraw(uname,5000);
                    }

                    else if (b == 5)
                    {
                        obj1.withdraw(uname,10000);
                    }

                    else if (b == 6)
                    {
                        obj1.withdraw(uname,15000);
                    }
                    break;

                case 3:
                    cout << "Cash withdraw" << endl;
                here:
                    cout << "Enter the amount you want to withdrawl:";
                    cin >> r.wdamount;
                    if (r.wdamount < (r.amount))
                    {
                        obj1.withdraw(uname,r.wdamount);
                    }
                    else
                    {
                        char P;
                        cout << "Insufficient Balance !!!!" << endl;
                        cout << "Re-enter the amount ?(y/n)";
                        cin >> P;
                        if (P == 'y')
                        {
                            goto here;
                        }
                        else
                        {
                            exit(0);
                        }
                    }
                    break;
                
                case 4:
                    obj1.deposit(uname);
                    break;

                case 5:
                    obj1.pinchange(uname);
                    break;

                default:
                    break;
                }
            }

            else
            {
                ++B;
                if (B > 2)
                {
                    cout << "You have entered wrong pin 3 times !!!\n";
                    cout << "Try again after 15 minutes." << endl;
                    ofstream obj;
                    obj.open("APP.txt");
                    obj << "ALERT !!!  ALERT !!!  ALERT !!!\n";
                    obj << "Someone is try to login your account !!!!\n";
                    Sleep(500000);
                    exit(0);
                }
                cout << "Incorrect pin!!" << endl;
                cout << "Re-enter the pin:";

                goto get;
            }
        }
        else
        {
            cout<<"Wrong username...!!! Enter again";
            goto get;
        }
    }
    else if (choice == 3)
    {
        obj1.display();
    }
}