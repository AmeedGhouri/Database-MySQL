
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
using namespace std;

// Global Variable Movie Ticket Booking System in C++ with MySQL
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
// Global Variable End

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost:3307", "ameed", "ameedghouri123", "db_lab", 0, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};

// Extra Functions Movie Ticket Booking System in C++ with MySQL codewithc.com
void Welcome() {
    cout << "Welcome To Movie Ticket Booking System" << endl << endl;
    cout << "Menu" << endl;
}

// Fucntions
void BookTicket();
void ShowMyTicket();
void CheckSeat();
void ReserveSeat();
void AddNewMovie();
void EditMovie();
void DeleteMovie();
void ShowMovieList();

int main()
{
    // Initial Load
    system("cls");
    system("title Music Store Management Program");
    system("color 0f");
    // Initial Load End

    // Call Methods
    db_response::ConnectionFunction();
    // Call Methods End

    // Variables
    int chooseOneFromMenu = 0;
    char exitSurity;
    int num = 1;
    int fin = 0;
    // Variables End

    Welcome();
    for (int i = 0; i < 1; i++) {
        fin = num;
        cout << fin << ". Book Ticket" << endl;
        fin += num;
        cout << fin << ". Show My Ticket" << endl;
        fin += num;
        cout << fin << ". Check Seat" << endl;
        fin += num;
        cout << fin << ". Add New Movie" << endl;
        fin += num;
        cout << fin << ". Edit Movie" << endl;
        fin += num;
        cout << fin << ". Delete Movie" << endl;
        fin += num;
        cout << fin << ". Show Movie List" << endl;
        fin += num;
        cout << fin << ". Exit" << endl;
        cout << "Choose One: ";
    }
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        BookTicket();
        break;
    case 2:
        ShowMyTicket();
        break;
    case 3:
        CheckSeat();
        break;
    case 4:
        AddNewMovie();
        break;
    case 5:
        EditMovie();
        break;
    case 6:
        DeleteMovie();
        break;
    case 7:
        ShowMovieList();
        break;
    case 8:
        ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
            return 0;
        }else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            main();
        }else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 7. Press Enter To Continue...";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}

// Function Implementation
void BookTicket() { //Poorab Gangwani CS191092

    std::string ID,customer_name,customer_phone;
    std::string movie,format,seat,price,showdate,showtime;
    mysql_query(conn,"select * from movie_tb where m_seat>0");
    res=mysql_store_result(conn);
    int num_field=mysql_num_fields(res);
    while(row=mysql_fetch_row(res))
    {
        for(int i=0;i<num_field;i++)
        {
            if(i==0)
            {
                while(field=mysql_fetch_field(res))
                {
                    std::cout<<field->name<<" | ";
                }
                std::cout<<std::endl;
            }
            std::cout<<" "<<row[i]<<" | ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Enter Movie ID:";
    std::cin>>ID;
    std::string query="select * from movie_tb where m_id="+ID+" and m_seat != 0";
    mysql_query(conn,query.c_str());
    res=mysql_store_result(conn);
    if(!(row=mysql_fetch_row(res)))
    {
        system("cls");
        std::cout<<" _________________________"<<std::endl;
        std::cout<<"|Entered ID was Invalid   |"<<std::endl;
        std::cout<<"|_________________________|"<<std::endl;
        BookTicket();
    }
    else
    {
        std::cin.ignore();
        std::cout<<"Enter Customer Name:";
        getline(std::cin,customer_name);
        std::cout<<"Enter Customer Contact Number:";
        std::cin>>customer_phone;
        std::string query="select * from movie_tb where m_id="+ID+" and m_seat != 0";
        mysql_query(conn,query.c_str());
        res=mysql_store_result(conn);
        num_field=mysql_num_fields(res);
        while(row=mysql_fetch_row(res))
        {
            for(int i=0;i<num_field;i++)
            {
                if(i==1)
                {
                    movie=row[i];
                }
                else if(i==3)
                {
                    format=row[i];
                }
                else if(i==4)
                {
                    showdate=row[i];
                }
                else if(i==5)
                {
                    showtime=row[i];
                }
                else if(i==6)
                {
                    price=row[i];
                }
                else if(i==7)
                {
                    seat=row[i];
                }
            }
        }
        std::string change_query="update movie_tb set m_seat=0 where m_id="+ID;
        mysql_query(conn,change_query.c_str());
        std::string insert_query="insert into customer_tb(name,phone,movie,format,seat,price,showdate,showtime) values('"+customer_name+"','"+customer_phone+"','"+movie+"','"+format+"',"+seat+","+price+",'"+showdate+"','"+showtime+"');";
        mysql_query(conn,insert_query.c_str());
    }
    system("cls");
    main();
}

void ShowMyTicket() {

    system("cls");

    // Variables
    char choose;
    string input;
    // Variables End

    Welcome();
    cin.ignore(1, '\n');
    cout << "Enter Your Id Or Name: ";
    getline(cin, input);
    string findbyname_query = "select * from  customer_tb where id = '"+input+"' or name = '"+input+"'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    int c = 0;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "ID: " << row[0] << "\nName: " << row[1] << "\nPhone: " << row[2] << "\nMovie: " << row[3] << "\nFormat: " << row[4] << "\nSeat: " << row[5] << "\nPrice: " << row[6] << "\nShow Date: " << row[7] << "\nShow Time: " << row[8] << endl << endl;
            c++;
        }

        if (c == 0) {
            cout << "No ticket with this input" << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'a' to Search again and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        ShowMyTicket();
    }
    else
    {
        exit(0);
    }

}

void CheckSeat() {
    system("cls");

    // Variables
    char choose;
    string input;
    // Variables End

    Welcome();
    cin.ignore(1, '\n');
    qstate = mysql_query(conn, "select * from  movie_tb");

    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("-------------------------------------\n");
        printf("| %-15s | %-15s |\n", "Name", "Seat");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s | %-15s |\n", row[1], row[7]);
        }
        printf("-------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

void AddNewMovie() { //Poorab Gangwani CS191092
    std::string movie_name,genre,format,showdate,showtime,ticket_price,seat;
    std::cin.ignore();
    std::cout<<"Enter Movie Name:";
    getline(std::cin,movie_name);
    std::cout<<"Enter Genre:";
    getline(std::cin,genre);
    std::cout<<"Enter Format:";
    std::cin>>format;
    std::cout<<"Enter Show-Date(YY-MM-DD):";
    std::cin>>showdate;
    std::cout<<"Enter Show-Time(HH:MM:SS):";
    std::cin>>showtime;
    std::cout<<"Enter Ticket price:";
    std::cin>>ticket_price;
    std::cout<<"Enter Seat Number:";
    std::cin>>seat;
    std::string insert_query="insert into movie_tb(m_name,m_genre,m_format,m_showdate,m_showtime,m_ticketprice,m_seat) values('"+movie_name+"','"+genre+"','"+format+"','"+showdate+"','"+showtime+"',"+ticket_price+","+seat+");";
    mysql_query(conn,insert_query.c_str());
    system("cls");
    std::string display="select * from movie_tb";
    mysql_query(conn,display.c_str());
    res=mysql_store_result(conn);
    int num_field=mysql_num_fields(res);
    while(row=mysql_fetch_row(res))
    {
        for(int i=0;i<num_field;i++)
        {
            if(i==0)
            {
                while(field=mysql_fetch_field(res))
                {
                    std::cout<<field->name<<" | ";
                }
                std::cout<<std::endl;
            }
            std::cout<<row[i]<<" | ";
        }
        std::cout<<std::endl;
    }
    main();
}

void EditMovie() {

    system("cls");

    // Variables
    string name = "";
    string genre = "";
    string format = "";
    string showDate = "";
    string showTime = "";
    string ticketPrice = "";
    string seat = "";
    string items[5000];
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storename = "";
    string storegenre = "";
    string storeformat = "";
    string storeshowDate = "";
    string storeshowTime = "";
    string storeticketPrice = "";
    string storeseat = "";
    // Variables End

    Welcome();
    qstate = mysql_query(conn, "select m_id, m_name from movie_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("--------------------------------\n");
        printf("| %-10s | %-15s |\n", "Column Id", "Name");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s |\n", row[0], row[1]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("--------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from movie_tb where m_id = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    cout << "Column ID: " << row[0] << "\nName: "
                         << row[1] << "\nGenre: " << row[2] << "\nFormat: " << row[3] << "\nShow Date: " << row[4] << "\nShow Time: " << row[5] << "\nTicket Price: " << row[6] << "\nSeat: " << row[7] << endl << endl;

                    storeid = row[0];
                    storename = row[1];
                    storegenre = row[2];
                    storeformat = row[3];
                    storeshowDate = row[4];
                    storeshowTime = row[5];
                    storeticketPrice = row[6];
                    storeseat = row[7];
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            string defaultString = "xN";
            cout << "Enter Name (" << defaultString << "  to not change): ";
            getline(cin, name);
            if (name == defaultString)
            {
                name = storename;
            }
            cout << "Enter Genre (" << defaultString << "  to not change): ";
            getline(cin, genre);
            if (genre == defaultString)
            {
                genre = storegenre;
            }
            cout << "Enter Format (" << defaultString << "  to not change): ";
            getline(cin, format);
            if (format == defaultString)
            {
                format = storeformat;
            }
            cout << "Enter Show Date (" << defaultString << "  to not change): ";
            getline(cin, showDate);
            if (showDate == defaultString)
            {
                showDate = storeshowDate;
            }
            cout << "Enter Show Time (" << defaultString << "  to not change): ";
            getline(cin, showTime);
            if (showTime == defaultString)
            {
                showTime = storeshowTime;
            }
            cout << "Enter Ticket Price (" << defaultString << "  to not change): ";
            cin >> ticketPrice;
            if (ticketPrice == defaultString)
            {
                 ticketPrice = storeticketPrice;
            }
            cout << "Enter Seat (" << defaultString << "  to not change): ";
            cin >> storeseat;
            if (seat == defaultString)
            {
                seat = storeseat;
            }

            string update_query = "update movie_tb set m_name = '"+name+"', m_genre = '"+genre+"', m_format = '"+format+"', m_showdate = '"+showDate+"', m_showtime = '"+showTime+"', m_ticketprice = '"+ticketPrice+"', m_seat = '"+seat+"' where m_id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        EditMovie();
    }
    else
    {
        exit(0);
    }
}

void DeleteMovie() {
    system("cls");

    // Variables
    char choose;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    Welcome();
    qstate = mysql_query(conn, "select * from movie_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("--------------------------------------------------\n");
        printf("| %-10s | %-15s | %-15s |\n", "Column Id", "Name", "Price");
        printf("--------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-15s |\n", row[0], row[1], row[6]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("--------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from movie_tb where m_id = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Press 'm' to Menu, 'd' to delete another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'd' || choose == 'D')
    {
        DeleteMovie();
    }
    else
    {
        exit(0);
    }
}

void ShowMovieList() {
    system("cls");

    // Variables
    char choose;
    string input;
    // Variables End

    Welcome();
    qstate = mysql_query(conn, "select * from movie_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Name", "Genre", "Format", "Show Date", "Show Time", "Price");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %s | %s | %s | %s | %s | %s |\n", row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        }
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << "Press 'm' to Menu any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

















