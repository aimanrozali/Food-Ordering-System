/*******************************************************************************
/* Assignment CPT 111
/* What the program do: Food Ordering System

/* Programmer name: Muhamad Aiman bin Mohd Rozali
/* Programmer Matric #: 152993

/*******************************************************************************
/* Manager Access
/* Username : root
/* Password : 1234
/******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Declaration of Object
ofstream outFile;
ifstream inFile;

//Function Prototype Declaration	
void fetchFile(string[], double[], double[], int[], int&, int[]);
void updateMenu(string[], double[], double[], int[], int&);
void updatePrice(string[], double[], int&);
void orderOnline(string[], double[],double[], int[], int&, int[][2], double&, double&, int&, bool&, int&, int[], int&);
void acceptOrder(string[], double[], double[], int[], int[][2], double&, double&, int&, bool&, int);
void makePayment(string[], double[], int[][2], int&, double&, bool&, int);
void totalPayment(double&, int);
void deliveredTime(string[], int[][2], double[], int&);
void totalSales(string[], double[],int[], int);
void saveFile(string[], double[], double[], int[], int, int[]);
double generateID();
bool verifyManager();
int mostPicked(int[], int);
void addStock(string[], int[], int);
int firstMenu();
int managerMenu(int);
int custMenu();


// Global constant variable
const int SIZE = 100;

int main(){
	
	// Change console background color
	system("COLOR 81");
	
	//Declare Arrays and Variable
	string menuName[SIZE]={};
	double menuPrice[SIZE]={};
	double deliveryTime[SIZE]={};
	int frequencyMenu[SIZE]={};
	int stock[SIZE]={};
	int custID=0;
	int counter=0,role, optionM, optionC;
	int customerOrder[SIZE][2]={};
	char prompt;
	double total=0, totalTime=0;
	int counterCust=0, totalCust=0;
	bool orderCheck=false, managerPass=false;
	
	// fetchFile function call
	fetchFile(menuName, menuPrice, deliveryTime, stock, counter, frequencyMenu);
	
	//menu label
	menu:
	
	// Manager menu process
	do {
		// firstMenu function call to and return role	
		role = firstMenu();
		// Determine user choice	
		if(role==1){
			// Checking Manager's login details
			managerPass = verifyManager();
			// If true, can access manager's menu
			if(managerPass==true){
				// Manager label
				manager:
				// call managerMenu function to display manager menu
				optionM = managerMenu(totalCust);
			
    			switch(optionM) {
    				case 1 :
    					// Function call to updateMenu()
            			updateMenu(menuName, menuPrice, deliveryTime, stock, counter);
            			// Redirect to update label
            			goto update;
        			case 2 :
        				// Function call to updatePrice()
            			updatePrice(menuName, menuPrice, counter);
            			// Redirect to update label
            			goto update;
        			case 3 :
        				// Function call to acceptOrder()
            			acceptOrder(menuName, menuPrice, deliveryTime, stock, customerOrder, total, totalTime, counterCust, orderCheck, custID);
            			// Redirect to manager label
            			goto manager;
        			case 4 :
        				// Function call to totalPayment()
            			totalPayment(total, custID);
            			// Redirect to manager label
            			goto manager;
        			case 5 :
        				// Function call to deliveredTime()
            			deliveredTime(menuName, customerOrder, deliveryTime, counterCust);
            			// Redirect to manager label
            			goto manager;
        			case 6 :
        				// Function call to totalSales()
            			totalSales(menuName, menuPrice, frequencyMenu, counter);
            			// Redirect to manager label
            			goto manager;
            		case 7 :
            			// Function call to addStock()
            			addStock(menuName, stock, counter);
            			// Redirect to update label
            			goto update;
            		case 8 :
            			// Redirect to menu label
            			goto menu;
            		case 9 :
            			// Stop loop
            			break;
        			default :
        				// Input Validation
            			cout << "Invalid Choice" << endl;
				}
				// Stop loop to exit
				break;
				// Update label
				update:
				// Function call to saveFile()
				saveFile(menuName, menuPrice, deliveryTime, stock, counter, frequencyMenu);
				goto manager;
				}
				else
					// Input Validation
					cout << "\t\tYour login information incorrect!\n";
			}
			// Process for customer Menu
		else if(role==2){
			customer:
			optionC = custMenu();
			switch(optionC){
				case 1 :
					orderOnline(menuName, menuPrice, deliveryTime, stock, counter, customerOrder, total, totalTime, counterCust, orderCheck, custID, frequencyMenu, totalCust);
            		goto customer;
        		case 2 :
            		makePayment(menuName, menuPrice, customerOrder, counterCust, total, orderCheck, custID);
            		goto customer;
            	case 3 :
            		goto menu;
        		default :
        			// Input validation
        			cout << "Invalid Choice.\n";	
			}
		}
		// User choose to exit
		else if(role==3)
			goto exit;
		else {
			// Input validation
			cout << "\t\tInvalid Choice\n";
		}
		exit:
		// Prompt to exit
		cout << "\n\t\tExit? (Y | N) :";
		cin >> prompt;
		if(prompt=='Y' || prompt=='y'){
			cout << "\t\t See You Again!!\n";
			break;
		}
		else if(prompt!='N' || prompt!='n')
			cout << "\t\tRedirecting to Main Menu....\n";
		else
			// Input validation
			cout << "\t\tInvalid!!!\n";
	}while(prompt!='Y' || prompt!='y');
	
	return 0;
}

double generateID(){
	// Generate random Number
	srand(time(NULL));
	
	// Limit random number to 100
	return rand() %100;
}

int firstMenu(){
	// Clear Screen
	system("cls");
	// role variable to store value choosen by user
	int role;
	// Welcome message and Option for user
	cout << "\t\t--------------------------------------------------\n";
	cout << "\t\t Welcome to The Teudoongie Restaurant\t\t\n";
	cout << "\t\t--------------------------------------------------\n";
	cout << "\t\t Choose Your Role : \t\t\n";
	cout << "\t\t 1. Manager \t\t\n";
	cout << "\t\t 2. Customer \t\t\n";
	cout << "\t\t 3. Exit\n";
	cout << "\t\t--------------------------------------------------\n";
	cout << "\t\t Enter Your Choice : ";
	// Input to choose option
	cin >> role;
	
	// return value role
	return role;
}

int managerMenu(int totalCust){
	// Clear Console screen
	system("cls");
	
	// Variable to hold value to determine option choosen from user
	int num;
	
	// Display how many customer since program runs
	cout << "\t\t----------------------------------------------------\n";
	cout << "\t\t Total Customer Today is: " << totalCust << endl;
	cout << "\t\t----------------------------------------------------\n";
	
	// Display massage to manager menu
	cout << "\t\t----------------------------------------------------\n";
	cout <<"\t\t Welcome to Manager Platform \t\t\n";
	cout << "\t\t----------------------------------------------------\n";
	
	// Ask user to choose option displayed
	cout << "\t\t----------------------------------------------------\n";
	cout << "\t\t\tChoose Following Option\t\t\t\n";
	cout << "\t\t1. Create/Update Menu\n";
    cout << "\t\t2. Update Prices\n";
    cout << "\t\t3. Accept Order\n";
    cout << "\t\t4. Calculate total payments per order\n";
    cout << "\t\t5. Calculate estimated delivery time\n";
    cout << "\t\t6. Calculate total sales for a day\n";
    cout << "\t\t7. Add Stock to existing menu\n";
    cout << "\t\t8. Main Menu\n";
    cout << "\t\t9. Exit\n";
    cout << "\t\t----------------------------------------------------\n";
    
    // Prompt user 
    cout << "\n\t\tEnter Your Choice: ";
    cin >> num;
    
    // Return value inputted by user
    return num;
}

int custMenu(){
	
	// Clear console screen
	system("cls");
	
	
	// Declare variable to hold user option
	int num;
	
	// Welcome message for customer
	cout << "\t\t----------------------------------------------------\n";
	cout << "\t\t Welcome to Customer Menu \t\t\n";
	cout << "\t\t----------------------------------------------------\n";
	// Let user choose option from displayed option
	cout << "\t\t Please Choose Following Option \t\t\n";
	cout << "\t\t 1. Order Online\n";
    cout << "\t\t 2. Make Payments\n";
	cout << "\t\t 3. Back To Main Menu\n";
	cout << "\t\t----------------------------------------------------\n";
	// Prompt user to input their option
	cout << "\t\t Enter Your Choice: ";
	cin >> num;
	
	// Return user's option
	return num;
}

bool verifyManager(){
	
	// Clear console background
	system("cls");
	
	// Display welcome message to manager
	cout << "\t\t---------------------------------------------\n";
	cout << "\t\tAccess To Manager Menu\n";
	cout << "\t\t---------------------------------------------\n";
	
	// variable to hold login information
	string username, password;
	// Prompt user to input username
	cout << "\n\t\t Enter Your Username: ";
	cin >> username;
	
	// Prompt user to input password
	cout << "\n\t\t Enter your password: ";
	cin >> password;
	
	// Check if login information is same or not
	if(username=="root" && password=="1234"){
		// Return true if login information correct
		return true;
	}
	else {
		// Inform user if login information mismatch
		cout << "\t\tWrong.\n";
		// Return false if login information mismatch
		return false;
	}
}

void fetchFile(string menuName[], double menuPrice[], double deliveryTime[], int stock[], int &counter, int frequencyMenu[]){
	
	// Open file text to fetch menu details
	inFile.open("MenuRestaurant.txt");
		// Check if can read from file
		if(inFile){
			// Set index to 0
			counter=0;
			// Read line by line until end of file
			// Read and seperate with tab
			while(getline(inFile, menuName[counter], '\t')){
				// Push menu data from file to array
				inFile >> menuPrice[counter];
				inFile >> deliveryTime[counter];
				inFile >> stock[counter];
				inFile >> frequencyMenu[counter];
				
				// Clear buffer
				inFile.ignore();
				//Increment counter to move to another index
				counter++;
			}
		}
		else
			// Prompt user if cannot open file
			cout << "Error Opening File.\n";
		
		// Close file
		inFile.close();
}

void saveFile(string menuName[], double menuPrice[], double deliveryTime[], int stock[], int counter, int frequencyMenu[]){
	
	// Open text file to save updated menu information
	outFile.open("MenuRestaurant.txt");
	
	// Set decimal points
	outFile << setprecision(2);
	
	// Use for loop to access array
	for(int k=0;k<counter;k++){
		// Store menu data from array to file and seperate it by tab
		outFile << menuName[k] << '\t' << menuPrice[k] << '\t' << deliveryTime[k] << '\t' << stock[k] << '\t' << frequencyMenu[k] << endl;
	}
	
	// Close file
	outFile.close();
	
	// Tells user file updated
	cout << "Updated!\n";
}

void updateMenu(string menuName[], double menuPrice[], double deliveryTime[], int stock[], int &counter){
	
	// Clear console screen
	system("cls");
	
	// Declare variable to hold input value
	string name;
	double price,time;
	int quantity;
	cout << "-----------------------------------------------\n";
	cout << "\t\t Menu Update \t\t\n";
	cout << "-----------------------------------------------\n";
	
	// Prompt user to enter new Menu Name
	cout << "\t\tPlease Enter Menu Name: ";
	cin.ignore();
	getline(cin, name);
	
	//Loop for input validation
	do {
		// Prompt user to input price for new menu
		cout << "\t\tPlease Enter Price: RM";
		cin >> price;
		// Check if price is valid or not
		if(price<1.00)
			// Display this message if input invalid
			cout << "\t\tInvalid Price.\n";
			
	//If invalid, loop again
	}while(price<1);
	
	// Loop for input validation
	do {
		// Prompt to enter Delivery Time for new menu
		cout << "\t\tPlease Enter Estimated Delivery Time (Minutes) : ";
		cin >> time;
		// Check if input valid or not
		if(time<0)
			// If invalid, display this message
			cout << "\t\tInvalid Time\n";
	// If invalid, loop again	
	}while(time<0);
	
	// loop for input validation
	do {
		//Prompt user to input quantity
		cout << "\t\tPlease Enter Stock : ";
		cin >> quantity;
		//Check if value inputted valid or not
		if(quantity<0)
			// Display this message if value entered by user invalid
			cout << "\t\tYour Stock Invalid \n";
	// If true, loop again				
	}while(quantity<0);
	
	// Push all validated value to respective arrays
	menuName[counter]=name;
	menuPrice[counter]=price;
	deliveryTime[counter]=time;
	stock[counter]=quantity;
	// Increment counter to add total menu
	counter++;
	
	// Display to user
	cout << "Update Complete!!\n";
	system("PAUSE");
	
}

void updatePrice(string menuName[], double menuPrice[], int &counter){
	
	// Clear console screen
	system("cls");
	
	
	int index,price;
	// Display Menu
	cout << fixed << setprecision(2);
	cout << "\t\tCurrent Menu: \n";
	cout << "\t\tName\t\t\tPrice\n";
	cout << "\t\t------------------------------------------\n";
	// For loop to access array
	for(int z=0; z<counter; z++){
		// Print data from array
		cout << "\t\t" << z+1 << ". " << setw(10) << menuName[z] << '\t' << setw(10) << "RM" << menuPrice[z] << endl;
	}
	cout << "\t\t------------------------------------------\n";
	
	// Input validation
	do{
		// Prompt user to input menu
		cout << "\t\tPlease Enter which menu you want to Update: ";
		cin >> index;
		// Check if entered menu is valid or not
		if(index-1<counter){
			do{
				// Prompt user to enter menu for selected menu
				cout << "\t\tEnter New Price for " << menuName[index-1] << " : RM";
				cin >> price;
				// Check price valid or not
				if(price>0){
					// If valid, update price in array
					menuPrice[index-1]=price;
					cout << "\t\tPrice Updated!!!\n";
				}
				else
					// Display message if price is invalid
					cout << "\t\tInvalid Price!\n";
			// if true, loop again
			}while(price<0);
		}
		else
			// Display message if choice is invalid
			cout << "\t\tInvalid Choice\n";
	// If true, loop again
	}while(!(index-1<counter));
	
	system("PAUSE");
}

void orderOnline(string menuName[], double menuPrice[], double deliveryTime[], int stock[], int &counter, int customerOrder[][2], double &total, double &totalTime, int &counterCust, bool &orderCheck, int &custID, int frequencyMenu[], int &totalCust){
	
	
	system("cls");
	
	// Set all value to 0 for new customers
	total=0;
	counterCust=0;
	customerOrder[SIZE][2]={};
	// Get most popular dish from mostPicked function
	int popular = mostPicked(frequencyMenu, counter);
	int choice, quantity;
	char prompt='n';
	//Generate customer ID
	custID = generateID();
	// Add number of customers
	totalCust++;
	cout << "\t\t-----------------------------------------------------\n";
	// Display customer ID
	cout << "\t\tYour Customer ID: " << custID << endl;
	// Display most popular dish
	cout << "\t\t Most Popular Dish: " << menuName[popular]<< endl;
	cout << "\t\t Order What You Want Here \t\t\n";
	cout << "\t\t-----------------------------------------------------------------\n";
	cout << "\t\t\t Menu \t\t\t Price \t\t Estimated Time \t Stock\n";
	cout << "\t\t-----------------------------------------------------------------\n";
	cout << fixed;
	// Show menu from array
	for(int x=0; x<counter;x++){
		cout << "\t\t" << (x+1) <<  " ." << setw(15) << menuName[x] << " \t\t RM" << setprecision(2) << menuPrice[x] << setw(15) << deliveryTime[x] << " Minutes"<< "\t\t" << stock[x] << " Pcs" << endl;
	}
	cout << "\t\t-------------------------------------------------------------------------\n";	
	do{	
		// Input Validation
		do {
			cout << "\t\tEnter Your Choice Here: ";
			cin >> choice;
			// Check if valid or not
			if(choice-1>=counter)
				cout << "\t\tNot in Menu.\n";
			else{
				cout << "\t\tYou Choose " << menuName[choice-1];
			}
		// If true, loop again
		}while(choice-1>=counter);
	
	
		// Input Validation
		do {
			cout << "\n\t\t How Many You Want? :";
			cin >> quantity;
			// Check if valid or not
			if(quantity<=0 || stock[choice-1]<quantity)
				cout << "\t\tInvalid Quantity\n";
		// if true, loop again
		}while(quantity<=0 || stock[choice-1]<quantity);
		
		// Clear buffer
		cin.ignore();
		
		// Inform user order received
		cout << "\t\tYour Order Received.\n";
		
		// Store all validated values to arrays
		customerOrder[counterCust][0]=choice-1;
		customerOrder[counterCust][1]=quantity;
		// Increment total of customer
		counterCust++;
		// Calculate total price
		total+=menuPrice[choice-1] * quantity;
		// Calculate total estimated delivery Time for the order
		totalTime+=deliveryTime[choice-1] * quantity;
		// Update data in array for most popular dish
		frequencyMenu[choice-1]+=quantity;
		
		// Prompt user if user want to order again
		cout << "\t\tYou Want to Order Again (Y or N)?: ";
		cin >> prompt;
	// If user want to order again, loop again
	}while(prompt=='Y' || prompt=='y');
	
	// Indicate order still in process of approval
	orderCheck=false;
	
	// Display what user have ordered, total price, estimated delivery time for each order
	cout << "\t\t-----------------------------------------------\n";
	cout << "\t\tMenu\t\tQuantity\n"; 
	cout << "\t\t-----------------------------------------------\n";
	for(int k=0;k<counterCust;k++){
			cout << "\t\t" << setw(8) << menuName[customerOrder[k][0]] << "\t" << customerOrder[k][1] << endl;
	}
	cout << "\t\t----------------------------------------------\n";
	cout << fixed << setprecision(2);
	cout << "\n\t\tTotal Payment for Order Is: RM" << total << endl;
	cout << "\t\tEstimated Time to Prepare: " << totalTime << " Minutes" << endl;
	
	system("PAUSE");
	
}

void acceptOrder(string menuName[], double menuPrice[], double deliveryTime[], int stock[], int custOrder[][2], double &total, double &totalTime, int &counterCust, bool &orderCheck, int custID){
	system("cls");
	
	char prompt;
	// Show Order Details
	cout << "------------------------------------------\n";
	cout << " \t\t Customer Order: \t\t\n";
	cout << "\t\t Name \t Quantity \t\t" << endl;
	for(int k=0;k<counterCust;k++){
			cout << "\t\t" << menuName[custOrder[k][0]] << "\t" << custOrder[k][1] << endl;
	}
	cout << "Total Price: RM" << total << endl;
	cout << "Time to Prepare: " << totalTime << " Minutes\n";
	
	// Input Validation
	do {
		cout << "Do You want to accept the order? (Y | N)? : ";
		cin >> prompt;
		cin.ignore();
		if(prompt=='Y' || prompt=='y'){
			for(int k=0; k<counterCust; k++){
				stock[custOrder[k][0]]-= custOrder[k][1];
			}
			orderCheck=true;
			cout << "Order for Customer " << custID << " accepted.\n";
			break;
		}
		else if(prompt=='N' || prompt=='n')
			break;
		else
			cout << "Invalid Input\n";
	}while(prompt!='Y' || prompt!='y' || prompt!='N' || prompt!='n' );
	
	system("PAUSE");
	
}

void makePayment(string menuName[], double menuPrice[], int customerOrder[][2], int &counterCust, double &total, bool &orderCheck, int custID){
	
	system("cls");
	
	// Check if order accepted or not
	if(orderCheck==true){
		double payment;
		// Display order details
		cout << "\t\t---------------------------------------------------------\n";
		cout << "\t\t\t Order Receipt \t\t\t\n";
		cout << "\t\t---------------------------------------------------------\n";
		cout << "\t\t\t Your Customer ID: " << custID << endl;	
		cout << "\t\tMenu\t\tQuantity\tTotal Price\n";
		for(int k=0; k<counterCust; k++){
			cout << "\t\t" << menuName[customerOrder[k][0]] << "\t\t" << customerOrder[k][1] << "\t" << " RM" << (customerOrder[k][1]*menuPrice[customerOrder[k][0]]) << endl;
		}
		cout << "\t\t----------------------------------------------------------\n";
		// Display total need to pay by customer
		cout << "\t\tTotal need to pay: " << total << endl;
		
		// Input validation
		do{
			// Prompt user to enter amount to pay
			cout << "\t\tEnter Amount to pay: RM";
			cin >> payment;
			// Check if amount paid enough or not
			if(payment>=total){
				double balance = payment - total;
				cout << "\n\t\tBalance: RM" << balance << endl;
				cout << "\t\tPayment Successful!!\n";
				cout << "\t\tThank You!!!\n";
			}
			else
				cout << "\t\tPayment Not Enough!!\n";		
		}while(payment<total);
	}
	else
		// Inform user if their order not accepted yet
		cout << "\t\tYour Order not accepted yet.\n";
	
	system("PAUSE");
	
}

void totalPayment(double &total, int custID){
	system("cls");
	// Display payment made by customer
	cout << "\t\t-------------------------------------------------\n";
	cout << "\n\t\tTotal Payment made by Customer " << custID << setprecision(2) << " is: RM" << total << endl;
	cout << "\n\t\t-------------------------------------------------\n";
	system("PAUSE");
}

void deliveredTime(string menuName[], int customerOrder[][2], double deliveryTime[], int &counterCust){
	system("cls");
	
	double time;
	// Show estimated time for the order
	for(int k=0; k<counterCust; k++){
		time += deliveryTime[customerOrder[k][0]]*customerOrder[k][1];
	}
	cout <<"\t\t-------------------------------------------------\n";
	cout << "\n\t\tEstimated Delivery Time : " << time << " Minutes" << endl;
	cout << "\t\t-------------------------------------------------\n";
	
	system("PAUSE");
}

void totalSales(string menuName[], double menuPrice[], int frequencyMenu[], int counter){
	system("cls");
	double sales;
	// Display all total sales for all menu
	cout << "\t\t-------------------------------------------------\n";
	cout << "\t\t Total Sales For All Menu\n ";
	cout << "\t\tMenu\t\tQuantity Sold\t\tSales\n";
	cout << "\t\t-------------------------------------------------\n";
	for(int k=0; k<counter; k++){
		cout << "\t\t" << setw(10) << menuName[k] << "\t\t"<< setw(5) << frequencyMenu[k] << "\t\t" << "RM"; 
		cout << setw(8) << fixed << setprecision(2) << menuPrice[k]*frequencyMenu[k] << endl;
		sales+=menuPrice[k]*frequencyMenu[k];
	}
	cout << "\n\t\t-------------------------------------------------\n";
	cout << "\n\t\tTotal Sales: RM" << sales << endl;
	cout << "\n\t\t-------------------------------------------------\n";
	
	system("PAUSE");
}

int mostPicked(int frequencyMenu[],int counter){
	
	// set max to first element of array
	int n=0, max=frequencyMenu[0];
	// Determine max value in array
	for(int i=0; i<counter; i++){
		if(max< frequencyMenu[i]){
			max=frequencyMenu[i];
			n=i;
		}
	}
	return n;
}

void addStock(string menuName[], int stock[], int counter){
	
	int choice, quantity;
	
	system("cls");
	// Display Menu
	cout << "\t\t----------------------------------------------------\n";
	cout << "\t\t Menu \t\t Stock\n";
	cout << "\t\t----------------------------------------------------\n";
	for(int k=0; k<counter; k++){
		cout << "\t\t " << (k+1) << ". " << menuName[k] << " \t\t " << stock[k] << endl;
	}
	cout << "\t\t----------------------------------------------------\n";
	//Input Validation	
	do {
		cout << "\t\tPlease Choose Menu You want to add stock: ";
		cin >> choice;
		if(choice-1>=counter)
			cout << "\t\tNot in Menu.\n";
		else{
			cout << "\t\tYou Choose " << menuName[choice-1] << endl;
			}
		}while(choice-1>=counter);
		
	//Input Validation
	do{
		cout << "\t\tHow Many Stock You want to add to "<< menuName[choice-1] << " ? : ";
		cin >> quantity;
		if(quantity>0){
			stock[choice-1]+=quantity;
			cout << "\n\t\t" << quantity << " " << menuName[choice-1] << " added!\n";
			cout << "\t\tNew stock for " << menuName[choice-1] << " is " << stock[choice-1] << endl;
		}
		else
			cout << "\t\tInvalid Quantity to add!!\n";
	}while(quantity<=0);
	
	system("PAUSE");
}


