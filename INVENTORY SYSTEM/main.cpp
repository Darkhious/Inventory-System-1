#include <iostream>
#include <cstdlib>

using namespace std;

const string USERNAME = "Administrator";
const string PASSWORD = "admin";
const int ROWS = 300;

string productName[ROWS] = {""};
int productAmount[ROWS] = {0};
int productPrice[ROWS] = {0};

void clearScreen()
{
    system("cls");
}

bool checkNumber(string text)
{
    int i;
    char character;
    bool found;

    found = false;

    for(i = 0; i < text.length(); i++)
    {
        character = text[i];

        if (!(character >= '0') && !(character <= '9'))
        {
            found = true;
        }
    }

    if (found)
    {
        return true;
    }
        else
        {
            return false;
        }
}

string capitalize(string text)
{
    int i;

    for(i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);
    }

    return text;
}

void addProduct()
{
    int i;
    string name, amount, price;

    clearScreen();

    cout<<"ADD PRODUCTS\n\n\n";

    for(i = 0; i < ROWS; i++)
    {
        if (productName[i] == "")
        {
            cout<<"Enter product name (Enter nothing to exit): ";
            getline(cin, name);

            if (name == "")
            {
                break;
            }
                else
                {
                    do
                    {
                        cout<<"Enter product quantity: ";
                        getline(cin, amount);

                        if (checkNumber(amount))
                        {
                            cout<<"\nERROR: Please enter numbers only!\n\n";
                        }

                    }while (checkNumber(amount));
                    
                    do
                    {
                        cout<<"Enter product price: ";
                        getline(cin, price);

                        if (checkNumber(price))
                        {
                            cout<<"\nERROR: Please enter numbers only!\n\n";
                        }
                    }while (checkNumber(price));

                    name = capitalize(name);
                    productName[i] = name;
                    productAmount[i] = stoi(amount);
                    productPrice[i] = stoi(price);

                    cout<<endl;
                }
        }
    }
}

void displayStock()
{
    string wait;
    int i, ctr;
    bool lowSupply;

    lowSupply = false;

    ctr = 1;

    clearScreen();

    cout<<"STOCKS\n\n";

    for(i = 0; productName[i] != ""; i++)
    {
        cout<<ctr<<".) "<<productName[i]<<":\n";
        cout<<productAmount[i]<<"x"<<endl;
        cout<<productPrice[i]<<" PHP"<<endl<<endl;

        ctr++;
    }

    for(i = 0; productName[i] != ""; i++)
    {
        if (productAmount[i] <= 10)
        {
            cout<<"Product extremely low on supply detected!\n\n";

            break;
        }
            else if (productAmount[i] <= 50)
            {
                cout<<"Product low on supply detected!\n\n";

                break;
            }
                else
                {
                    cout<<"No product is low on supply.\n\n";

                    break;
                }
    }

    cout<<"\nEnter anything to continue: ";
    getline(cin, wait);
}

void sellItem()
{
    int i, total;
    string itemName, quantity, response;
    bool found;

    found = false;

    clearScreen();

    cout<<"SELL ITEM\n\n\n";

    do
    {
        cout<<"Enter the product to sell (Enter nothing to exit): ";
        getline(cin, itemName);

        if (itemName == "")
        {
            break;
        }
            else
            {
                itemName = capitalize(itemName);

                for(i = 0; i < ROWS; i++)
                {
                    if (itemName == productName[i])
                    {
                        found = true;

                        break;
                    }
                }

                if (found)
                {
                    do
                    {
                        cout<<"Enter the amount to buy: ";
                        getline(cin, quantity);

                        if (checkNumber(quantity))
                            {
                                cout<<"\nERROR: Please enter numbers only!\n\n";
                            }
                    }while (checkNumber(quantity));

                    total = productPrice[i] * stoi(quantity); 

                    cout<<"\nBUYING: "<<itemName<<endl;
                    cout<<"QUANTITY: "<<quantity<<"x\n";
                    cout<<"TOTAL AMOUNT DUE: "<<total<<" PHP\n\n";

                    do
                    {
                        cout<<"Proceed to payment? (Y/N): ";
                        getline(cin, response);

                        if (response == "Y" || response == "y")
                        {
                            productAmount[i] = productAmount[i] - stoi(quantity);

                            break;
                        }
                            else if (response == "N" || response == "n")
                            {
                                clearScreen();

                                break;
                            }
                                else
                                {
                                    cout<<"\nPlease input Y/N only!\n\n";
                                }
                    }while (true);
                }
                    else
                    {
                        cout<<"\nERROR: Product not found!\n";
                    }
                
                cout<<endl;
            }
    }while (itemName != "");
}

void menu()
{
    string choice;
    bool failedAttempt;

    failedAttempt = false;

    do
    {
        clearScreen();

        cout<<"MENU\n\n\n";

        if (failedAttempt)
        {
            cout<<"ERROR: Please input only 1/2/3/4!\n\n";
        }

        cout<<"1.) Add Product \n2.) Display Stocks \n3.) Sell Item \n4.) Exit \n\n";

        cout<<"Select from the choices above (1/2/3/4): ";
        getline(cin, choice);

        if (choice == "1")
        {
            failedAttempt = false;

            addProduct();
        }
            else if (choice == "2")
            {
                failedAttempt = false;

                displayStock();
            }
                else if (choice == "3")
                {
                    failedAttempt = false;

                    sellItem();
                }
                    else if (choice == "4")
                    {
                        clearScreen();

                        cout<<"Program Terminated!\n\n\n";
                    }
                        else
                        {
                            failedAttempt = true;
                        }
    }while (choice != "4");
}

void logIn()
{
    string inputName, inputPass;
    int attemps;
    bool failedAttempt;

    attemps = 0;
    failedAttempt = false;

    do
    {   
        attemps++;

        clearScreen();

        cout<<"LOG IN\n\n\n";

        if (failedAttempt)
        {
            cout<<"ERROR: Invalid Username or Password!\n\n";
        }

        cout<<"Username: ";
        getline(cin, inputName);

        if (inputName == USERNAME)
        {
            cout<<"Password: ";
            getline(cin, inputPass);
        }
        
        if (inputName != USERNAME || inputPass != PASSWORD)
        {
            failedAttempt = true;
        }
    }while ((inputName != USERNAME || inputPass != PASSWORD) && attemps <= 3);

    if (inputName == USERNAME && inputPass == PASSWORD)
    {
        menu();
    }
}

int main()
{
    logIn();

    return EXIT_SUCCESS;
}