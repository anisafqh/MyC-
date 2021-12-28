//**************************************************************************************//
// This program calculate Body Mass Index(BMI), Basal Metabolic Rate(BMR) and
// Resting Metabolic Rate(RMR) for every USM's staff. This program allows USM's staff 
// to search their BMI, BMR and RMR based on their staff ID and they also can know
// their BMI level and get an advice from their BMI Level .
//**************************************************************************************//
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

// Function prototypes
void welcome();
void menu();
void showBMI();
void showBMR();
void showRMR();
void displayBMI(string[], double[], int);
void displayBMR(string[], double[], int);
void displayRMR(string[], double[], int);
void staffInfo(string[], string[], string[], int[],
			   double[], double[], int);
void addStaff();
void displayChoice();
void rangeBMI20(double[], int);
void rangeBMI25(double[], int);
void rangeBMINormal(double[], int);
void rangeBMIObese(double[], int);
void searchStatistic(double[], string[], int[], int);
void seriousCases(double[], int[], string[], int);
void seriousCases2(double[], int[], string[], int);
void displayAdvice(string[], double[], double[], 
				   double[],int);
void outputFile(string[] , string[], string[], int[], double[],
			   double[], int);


int main()
{
	int choice, pick;				// To hold a menu choice
	char choose;		// To hold choices 	
	int size = 20;			// Size index of array
	double BMI[size];		// To hold BMI
	double BMR[size];		// To hold BMR
	double RMR[size];		// To hold RMR
	string name[size];		// To hold name 
	string staffID[size];	// To hold staffID
	int age[size];			// To hold age
	string gender[size];		// To hold gender
	double height[size];	// To hold height
	double weight[size];	// To hold weight
	int i = 0;				// Index of array
	
	
	
	ifstream staffFile;		
	staffFile.open("staffusminfo.txt", ios::app);	// Open file in append mode
	
	// runs while the file is not at the end
	if(! staffFile.eof())
		{
			// store all the usm staffs' information in array
			getline(staffFile, name[i], '\t');
			staffFile >> staffID[i] >> gender[i] >> age[i] >> weight[i] >> height[i];
				
				while(staffFile)
				{
					// calculate BMI for each staffs
					BMI[i] = (weight[i] / ((height[i]/100)*(height[i]/100)));		
				
					// calculate BMR and RMR for men and women 
					if(gender[i] == "Male")
					{
						BMR[i] = (10 * weight[i] + 6.25 * height[i] - 5 * age[i] + 5);
						RMR[i] = (88.362 + (13.397 * weight[i]) + (4.799 * height[i]) - (5.677 * age[i]));
					}
					else if(gender[i] == "Female")
					{
						BMR[i] = (10 * weight[i] + 6.25 * height[i] - 5 * age[i] - 161);
						RMR[i] = (447.593 + (9.247 * weight[i]) + (3.098 * height[i]) - (4.330 * age[i]));
					}
					
					
					i++;
					getline(staffFile, name[i], '\t');
					staffFile >> staffID[i] >> gender[i] >> age[i] >> weight[i] >> height[i];
				//	cout << name[i] <<  "\t" << staffID[i] << "\t" << gender[i] << "\t" << age[i] << "\t" << weight[i] << "\t" << height[i] << "\t" << BMR[i] << "\t" << RMR[i];

				}
		

		}
		
		staffFile.close();	// closes the file
		
		// Constants for the menu choices
		const int BMI_CHOICE = 1 ,
			 	  BMR_CHOICE = 2 ,
			 	  RMR_CHOICE = 3 ,
			  	  ADDSTAFF_CHOICE= 4 ,
			  	  RANGE_CHOICE = 5 ,
			      STATISTIC_CHOICE = 6 ,
			      SERIOUS_CHOICE = 7 ,
			      ADVICE_CHOICE = 8 ,
			      QUIT_CHOICE = 9 ;
			  
		cout << fixed << showpoint << setprecision(1); 		// set to 1 decimal place
		
		do
		{
			welcome();				// Display welcome screen
			menu();					// Display the menu and get the user's choice	
			cin >> choice;  		// user enter their choice
			cout << endl << endl;
		
			// validate the menu selection
			while (choice < BMI_CHOICE || choice > QUIT_CHOICE)
			{
				cout << " Please enter a valid menu choice: ";
				cin >> choice;
			}
		
			// if the user does not want to quit, proceed
			if (choice != QUIT_CHOICE)
			{
				// if user choose 1
				if (choice == 1)	
				{
					showBMI();						// Display intro screen for BMI	
				 	displayBMI(staffID, BMI, size);	// Display the BMI after user enter their staffID
				}
				
				
				// if user choose 2
				else if(choice == 2)	
				{
					showBMR();						// Display intro screen for BMR
					displayBMR(staffID, BMR, size);	// Display the BMR after user enter their staffID	
				}
				
				
				// if user choose 3
				else if(choice == 3)
				{
					showRMR();						// Display intro screen for RMR
					displayRMR(staffID, RMR, size);	// Display the RMR after user enter their staffID
					
				}
				
				
				// if user choose 4
				else if(choice == 4)
				{
					staffInfo(name, staffID, gender, age, weight, height, size);	// Display name list of USM,s staff
					addStaff();		// Ask user to add new information of staff
					
				}
				
				
				// if user choose 5
				else if(choice == 5)
				{
					cout << endl;
					displayChoice();		// display the choices
					cin >> pick;			// user enter the choice they want
				
					switch(pick)
					{
						case 1 : rangeBMI20(BMI, size);	// Display number of staff that have BMI less than 20
							break;
						case 2 : rangeBMI25(BMI, size);	// Display number of staff that have BMI more than 25
							break;
						case 3 : rangeBMINormal(BMI, size);	// Display number of staff that have normal BMI
							break;
						case 4 : rangeBMIObese(BMI, size);	// Display number of staff that have BMI more than 30
							break;
						default : cout << " Invalid choice !\n";	// If user enter invalid choice
					}
					
				}
				
				
				// if user choose 6
				else if(choice == 6)
				{
					cout << endl;
					searchStatistic(BMI, gender, age, size);	// Display the statistic 
					
				}
				
				
				// if user choose 7
				else if(choice == 7)
				{
					cout << " For women staffs : " << endl;
					seriousCases(BMI, age, gender, size);		// Display the number of women staffs based on specific requirements
					cout << endl;
					cout << " For men staffs : " << endl;
					seriousCases2(BMI, age, gender, size);		// Display the number of men staffs based on specific requirements
					
				}
				
				
				// if user choose 8
				else if(choice == 8)
				{
					displayAdvice(staffID, BMI, weight, height, size);	// Display the advices based on user BMI
					
				}
				
				
			}			
		}
		
		while (choice != QUIT_CHOICE);
		
		outputFile(name, staffID, gender, age, weight, height, size);	// calling function outputFile

	return 0;
}

//****************************************************************************
// Function showWelcome which displays the welcome screen 
//****************************************************************************

void welcome()
{
	cout << "\n\t\t____________________________________________________________\t\t\n";
	cout << "\t\t************************************************************\n";
	cout << "\t\t************************************************************";
	cout << endl;
	cout << "\t\t\tWELCOME TO LET'S GET FIT (LGF) CALCULATOR\t\t\t";
	cout << endl;
	cout << "\t\t____________________________________________________________\t\t\n";
	cout << "\t\t************************************************************\n";
	cout << "\t\t************************************************************";
	cout << endl << endl;
}

//*****************************************************************************
// Definition of function showMenu which displays the menu that 
// users can choose.
//*****************************************************************************

void menu()
{
	cout << "\n\tLET'S GET FIT (LGF) MENU\n";
	cout << endl;
	cout << "\tWhat you want to know ?\n";
	cout << "\tChoose one !\n";
	cout << endl;
	cout << " [1] |\tBMI\n";
	cout << " [2] |\tBMR\n";
	cout << " [3] |\tRMR\n";
	cout << " [4] |\tAdd New Staff\n";
	cout << " [5] |\tAverage of USM's Staff based on their BMI\n";
	cout << " [6] |\tSearch for USM's Staff Information\n";
	cout << " [7] |\tSerious Cases\n";
	cout << " [8] |\tWant Some Advice ?\n";
	cout << " [9] |\tQuit\n";
	cout << " Please enter your choice: ";
}

//*****************************************************************************
// Definition of function showBMI which display the title and 
// brief to user about the definition of BMI
//*****************************************************************************

void showBMI()
{
	cout << "\t______________________________________\t\n";
	cout << "\t\tBody Mass Index (BMI)\t\t\n";
	cout << "\t______________________________________\t\n";
	cout << " BMI is a value derived from the weight and height";
	cout << " of a person.\n";
}

//*****************************************************************************
// Definition of function displayBMI which display the BMI of user
// after they enter their staffID
//*****************************************************************************

void displayBMI(string STAFFID[], double BMIVAL[], int size)
{
	string StaffID;
	bool flag = false;		// flag to indicate if the staffID was found

	cout << endl << endl;
	cout << " Do you want to know your BMI ?\n";
	cout << " Please enter your Staff ID. (Example : FGT567)\n";
	cout << " Staff ID : ";
	cin >> StaffID;

	for (int j = 0; j < size; j++)
	{		
		if( STAFFID[j] == StaffID)		// if user's staff ID entered same as in the array
		{
			cout << " BMI : " << BMIVAL[j] << endl;
			if (BMIVAL[j] < 20)
					{
						cout  << " You are Underweight ! ";
					}
					else if ((BMIVAL[j] >= 20) && (BMIVAL[j] < 25))
					{
						cout << " You are Normal ! " ;
					}
		
					else if ((BMIVAL[j] >= 25) && (BMIVAL[j] < 30))
					{
						cout << " You are Overweight ! " ;
					}
		
					else if (BMIVAL[j] >= 30)
					{
						cout << " You are Obese ! " ;
					}
							
					else
					{
						cout << "Not Valid!" ;
					}
			flag = true;	// set the flag
		}
	}
	if ( flag == false)		// set the flag
	{
		cout << "BMI not found.\n";
	}
	
}


//*****************************************************************************
// Definition of function showBMR which display the title and 
// brief to user about the definition of BMR
//*****************************************************************************

void showBMR()
{
	cout << "\t______________________________________\t\n";
	cout << "\t\tBasal Metabolic Rate (BMR)\t\t\n";
	cout << "\t______________________________________\t\n";
	cout << " BMR is the amount of energy it takes for your body";
	cout << " to maintain life.\n";		
}

//*****************************************************************************
// Definition of function displayBMR which display the BMR of user
// after they enter their staffID
//*****************************************************************************

void displayBMR(string STAFFID[], double BMRVAL[], int size)
{
	string StaffID;
	bool flag = false;		// flag to indicate if the staffID was found

	cout << endl << endl;
	cout << " Do you want to know your BMR ?\n";
	cout << " Please enter your Staff ID. (Example : FGT567)\n";
	cout << " Enter Staff ID : ";
	cin >> StaffID;

	for (int j = 0; j < size; j++)
	{		
		if( STAFFID[j] == StaffID)		// if user's staff ID entered same as in the array
		{
			cout << " BMR : " << BMRVAL[j] ;
			flag = true;	// set the flag
		}
	}
	if ( flag == false)		// set the flag
	{
		cout << "BMR not found.\n";
	}
	
}

//*****************************************************************************
// Definition of function showRMR which display the title and 
// brief to user about the definition of RMR
//*****************************************************************************

void showRMR()
{
	cout << "\t______________________________________\t\n";
	cout << "\t\tResting Metabolic Rate (RMR)\t\t\n";
	cout << "\t______________________________________\t\n";
	cout << " RMR is the rate at which a body burns energy when ";
	cout << "it is at complete rest.\n";
				
}

//*****************************************************************************
// Definition of function displayBMR which display the BMR of user
// after they enter their staffID
//*****************************************************************************

void displayRMR(string STAFFID[], double RMRVAL[], int size)
{
	string StaffID;
	bool flag = false;		// flag to indicate if the staffID was found
	
	cout << endl << endl;
	cout << " Do you want to know your RMR ?\n";
	cout << " Please enter your Staff ID. (Example : FGT567)\n";
	cout << " Enter Staff ID : ";
	cin >> StaffID;

	for (int j = 0; j < size; j++)
	{		
		if( STAFFID[j] == StaffID)		// if user's staff ID entered same as in the array
		{
			cout << " RMR : " << RMRVAL[j] ;
			flag = true;	// set the flag
		}
	}
	if ( flag == false)		// set the flag
	{
		cout << "RMR not found.\n";
	}
}

//*****************************************************************************
// Definition of function stffInfo where it the list of USM's staff information
//*****************************************************************************

void staffInfo(string NAME[], string STAFFID[], string GENDER[], int AGE[], double WEIGHT[],
			   double HEIGHT[], int size)
{
	cout << "\t______________________________________\t\n";
	cout << "\t\tUSM's STAFF INFORMATION\t\t\n";
	cout << "\t______________________________________\t\n\n\n";
	cout << endl << endl;
	cout << "NAME" << "\t\t\t" << "STAFF ID" << "" << "GENDER" << " ";
	cout << "AGE" << "\t" << "WEIGHT" << "\t" << "HEIGHT" << endl;
	cout << "---------------------------------------------------------------------------------\n\n";
	
	for (int j = 0; j < size; j++)
	{
		cout << NAME[j] << "\t" << STAFFID[j] << "\t" << GENDER[j] << "\t";
		cout << AGE[j] << "\t" << WEIGHT[j] << "\t" << HEIGHT[j] ;
	}
	
	cout << endl << endl;
	cout << " Any missing staff there ?\n";
	cout << " Do you want to add new information for another staff?\n";
}

//*****************************************************************************
// Definition of function addStaff where new information about another staff
// will be add into the file.
//*****************************************************************************

void addStaff()
{
	int i;
	string NAME;
	string STAFFID;
	string GENDER;
	int AGE;
	double WEIGHT;
	double HEIGHT;

	cout << " Please enter your new information.\n";
	cin.ignore(1500, '\n');
	cout << " Enter name : ";
	getline(cin, NAME);
	cout << " Enter Staff ID : ";
	cin >> STAFFID;
	cout << " Enter age : ";
	cin >> AGE;
	cout << " Enter gender : ";
	cin >> GENDER;
	cout << " Enter weight : ";
	cin >> WEIGHT;
	cout << " Enter height : ";
	cin >> HEIGHT;

	cout << " DONE !\n";
	cout << " Your information will be saved.\n";
	
	fstream staffFile;
	
	staffFile.open("output file.txt", ios::app);	// Open file in append mode

		staffFile << endl;
		staffFile << NAME << "\t";
		staffFile << STAFFID << "\t";
		staffFile << GENDER << "\t";
		staffFile << AGE << "\t";
		staffFile << WEIGHT << "\t";
		staffFile << HEIGHT << "\t";
	
	staffFile.close();	// closes the file

}

//*****************************************************************************
// Definition of function displayChoice where it display the choices
// for user to select the option given .
//*****************************************************************************

void displayChoice()
{
	cout << " What do you want to know ?\n\n";
	cout << " A) All staff with BMI less than 20 (Underweight) ?\n";
	cout << " B) All staff with BMI more than 25 ";
	cout << "less than 30 (Overweight) ?\n";
	cout << " C) All staff with normal BMI ?\n";
	cout << " D) All staff with BMI more than 30 (Obese) ?\n";
	cout << endl;
	cout << " Enter your choice. (Example : A)" << " ";
}

//*****************************************************************************
// Definition of function rangeBMI20 where it display the total number of 
// USM's staff that has BMI value less than 20 (Underweight) .
//*****************************************************************************

void rangeBMI20(double BMIVAL[], int size)
{
	double BMIval;
	double sum = 0;
	int average;
	int j;
	
	BMIval = 20;
	
	for (j = 0; j < size; j++)
	{		
		if(BMIVAL[j] <= BMIval)		// BMIVAL less than BMIval which is 20
		{
			sum += BMIVAL[j];	
		}
	}
	
	average = sum / j;
	cout << "There are " << (average + 1) << " staffs that has BMI";
	cout << " less than 20 (Underweight).\n";
}

//*****************************************************************************
// Definition of function rangeBMI25 where it display the total number of 
// USM's staff that has BMI value more than 25 (Overweight).
//*****************************************************************************

void rangeBMI25(double BMIVAL[], int size)
{
	double sum = 0;
	int average;
	int j;
	
	for (j = 0; j < size; j++)
	{		
		if(BMIVAL[j] >= 25 && BMIVAL[j] < 30)	// BMIVAL less than 30, more than or equal to 25
		{
			sum += BMIVAL[j];	
		}
	}
	cout << endl;
	average = sum / j;
	cout << "There are " << (average - 1) << " staffs that has BMI";
	cout << " more than 25 but less than 30 (Overweight).\n";
}

//*****************************************************************************
// Definition of function rangeBMINormal where it display the number of 
// USM's staff that has normal BMI value.
//*****************************************************************************

void rangeBMINormal(double BMIVAL[], int size)
{
	double sum = 0;
	int average;
	int j;
	
	
	for (j = 0; j < size; j++)
	{		
		if(BMIVAL[j] >= 20 && BMIVAL[j] < 25)	
		{
			sum += BMIVAL[j];	
		}
	}
	cout << endl;
	average = sum / j;
	cout << "There are " << average << " staffs that has";
	cout << " normal BMI value.\n";
}

//*****************************************************************************
// Definition of function rangeBMIObese where it display the total number of 
// USM's staff that has BMI value more than 30 (Obese) .
//*****************************************************************************

void rangeBMIObese(double BMIVAL[], int size)
{
	double sum = 0;
	int average;
	int j;
	
	for (j = 0; j < size; j++)
	{		
		if(BMIVAL[j] >= 30)		// BMIVAL more than or equal to 30
		{
			sum += BMIVAL[j];	
		}
	}
	
	average = sum / j;
	cout << "There are " << (average - 1) << " staffs that has BMI";
	cout << " more than 30 (Obese).\n";
}

//*****************************************************************************
// Definition of function searchStatistic where it display the total number of
// USM's staff from BMI and age that user want 
//*****************************************************************************

void searchStatistic(double BMIVAL[], string GENDER[], int AGE[], int size)
{
	int age1, j;																
	bool flag = false;		// flag to indicate if the age was found
	
	cout << endl << endl;
	cout << " This program will display the BMI";
	cout << " for the age that you enter.\n";
	cout << " Enter age that you want.\n";
	cin >> age1;

	for (j = 0; j < size; j++)
	{		
		if( AGE[j] == age1 )	// if user's age entered same as in the array
		{
			if (GENDER[j] == "Male")
			{
				cout << " Man : BMI for age " << age1 << " is " << BMIVAL[j] << endl;

			}
			
			else if (GENDER[j] == "Female")	// if user's gender entered same as in the array
			{
				cout << " Woman : BMI for age " << age1 << " is " << BMIVAL[j] << endl;
			}
			flag = true;	// set the flag
		}
	}
	
	if ( flag == false)		// set the flag
	{
		cout << "Age you enter not found.\n";
	}
	
	
}

//*****************************************************************************
// Definition of function seriousCases where it display the total number of 
// USM's staff that has BMI value more than 25 with specific information
// which are from women staffs and age from 20.
//*****************************************************************************

void seriousCases(double BMIVAL[], int AGE[], string GENDER[], int size)
{
	double sum = 0;
	int average;
	int j;
	
	for (j = 0; j < size; j++)
	{		
		if(BMIVAL[j] > 25 && AGE[j] > 20 && GENDER[j] == "Female")
		{
			sum += BMIVAL[j];	
		}
	}

	average = sum / j;
	cout << "There are " << (average - 1) << " women staffs that are";
	cout << " overweight and obese with age from 20.\n";	
}

//*****************************************************************************
// Definition of function seriousCases2 where it display the total number of 
// USM's staff that has BMI value more than 25 with specific information
// which are from men staffs and age from 20.
//*****************************************************************************

void seriousCases2(double BMIVAL[], int AGE[], string GENDER[], int size)
{
	double sum = 0;
	int average;
	int j;
	
	for (j = 0; j < size; j++)
	{		
		if(BMIVAL[j] > 25 && AGE[j] > 20 && GENDER[j] == "Male")
		{
			sum += BMIVAL[j];	
		}
	}

	average = sum / j;
	cout << "There are " << (average - 1) << " men staffs that are";
	cout << " overweight and obese with age from 20.\n";	
}

//*****************************************************************************
// Definition of function displayAdvice which display the BMI with advices  
// for user after they enter their staffID
//*****************************************************************************

void displayAdvice(string STAFFID[], double BMIVAL[], double WEIGHT[], 
				   double HEIGHT[],int size)
{
	string StaffID;
	bool flag = false;		// flag to indicate if the staffID was found

	cout << endl << endl;
	cout << " Please enter your Staff ID. (Example : FGT567)\n";
	cout << " Staff ID : ";
	cin >> StaffID;

	for (int j = 0; j < size; j++)
	{		
		if( STAFFID[j] == StaffID)	// if user's staff ID entered same as in the array
		{
			cout << " Weight : " << WEIGHT[j] << " kg " << endl;
			cout << " Height : " << HEIGHT[j] << " m " << endl;
			cout << " BMI : " << BMIVAL[j] << endl;
			if (BMIVAL[j] < 20)
					{
						cout << " You are Underweight ! ";
						cout << " You have to eat more frequently";
						cout << " and choose nutrient rich foods ";
						cout << "to gain weight !\n";
					}
					else if ((BMIVAL[j] >= 20) && (BMIVAL[j] < 25))
					{
						cout << " You are Normal ! " ;
						cout << " Keep going with your healthy lifestyle !\n";
						cout << " Don't forget to drink a lot of water !\n";
					}
		
					else if ((BMIVAL[j] >= 25) && (BMIVAL[j] < 30))
					{
						cout << " You are Overweight !\n" ;
						cout << " Please fix your eating and sleeping time.\n";
						cout << " Don't eat late at night and get on a regular";
						cout << " schedule for sleeping.\n";
					}
		
					else if (BMIVAL[j] >= 30)
					{
						cout << " OH, NO ! You are Obese !\n";
						cout << " Please eat a balanced calorie-controlled";
						cout << " diet as recommended by a dietitian.\n";
						cout << " You also should take up activities such as fas walking\n";
						cout << ", jogging, swimming for 15 to 300 minutes(2.5 to 5 hours)";
						cout << " a week. YOU CAN DO IT !\n";
					}
							
					else
					{
						cout << "Not Valid!" ;
					}
			flag = true;	// set the flag
		}
	}
	if ( flag == false)	// set the flag
	{
		cout << "BMI not found.\n";
	}
	
}

//*****************************************************************************
// Definition of function outputFile where this file will show the information
// off the staff and new staff that have been added
//*****************************************************************************

void outputFile(string NAME[], string STAFFID[], string GENDER[], int AGE[], double WEIGHT[],
			   double HEIGHT[], int size)
{
	int i;
	fstream staffFile;
	
	staffFile.open("output file.txt", ios::app	| ios::out);	// Open file in append and output mode
	
	for (i = 0; i < size; i++)
	{
		staffFile << endl;
		staffFile << NAME[i] << "\t";
		staffFile << STAFFID[i] << "\t";
		staffFile << GENDER[i] << "\t";
		staffFile << AGE[i] << "\t";
		staffFile << WEIGHT[i] << "\t";
		staffFile << HEIGHT[i] << "\t";
		
	}
	
	staffFile.close();	// close the file
	
}
