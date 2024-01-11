#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

std::vector<std::vector<std::string>> userDB;
std::string currentUser;
std::string paswrd;

/*
    Welcome to Piggy Bank! Your personal wallet inside your computer. 

    A fun, yet difficult project by a C++ beginner. 

    I have to thank the Internet's magical friends for achieving this.

    I admit it is not the most secure, but it's functional; it does what it's supposed to.

    What I like about this project is that it utilizes a .txt file to store user's data
    permanently. This allows for long-term storage and multi-user application. The code, 
    as messy as it is, has been a personal project of mine to look into the strange and
    difficult world of C++. 

    Project by SystemUnderscoreBox (Github).

*/

/*
    This class of the piggy bank itself.      
*/

class piggyBank {
    
    private:
        float balance = 0;

    public:

        char y;        

        int run() { 
            loadBalance();
            while (true) {
                std::cout << R"(
    [===========================================]
            Welcome to your own piggy Bank!
    )" << std::endl;
    std::cout << "          Your current balance: " << std::fixed << std::setprecision(5) << balance << std::endl;
                std::cout << R"(
    [===========================================]
     Withdraw [W]     Add money [A]     Leave [L]
    )" << std::endl;
                std::cin >> y;
                
                switch (y) {
                
                    case 'W':
                        withDraw(balance);
                        break;
                    case 'A':
                        addMoney(balance);
                        break;
                    case 'L':
                        saveBalance(balance);
                        return 0;
                    default:
                        std::cout << R"(
    Please type in a valid character.
    )" << std::endl;
                        break;                  
                }   
            
            }
            return 0;
        }
    
        /*
            The methods that make it possible
            to take money away and add. 
        */

        float withDraw(float& bal) {
        
                std::cout << R"(
    Please type in the amount you wish to withdraw.
    )" << std::endl;
                float wm; 
                std::cin >> wm;

                bal -= wm;

                std::cout << "\n" << "Successfully withdrew " << bal << " from your account!" << std::endl;

                return bal;

        }    

        float addMoney(float& bal) {
        
                std::cout << R"(
    Please type in the amount of money you wish to add. 
    )" << std::endl;
                float am;
                std::cin >> am;

                bal += am;

                std::cout << "\n" << "Successfully added " << am << " into your piggy bank account!" << std::endl;

                return bal;

        }

    private:

        /*
            This method simply loads the balance from the vector. 
        */

        void loadBalance() {

            for (const auto& row : userDB) {

                if (row[0] == currentUser) {
                        balance = std::stof(row[2]);
                        break;
                    }                
         
                }            

            }
                
        /*
            The method to save the new balance into the txt file.
        */

        void saveBalance(float& bal) {
            
            std::ofstream outFile("userDB.txt", std::ios::trunc);

            for (auto& row : userDB) {

                if (row[0] == currentUser && row[1] == paswrd) { // A security measure. This updates the old txt file's balance data to be correspond to the newly updated balance.
                    row[2] = std::to_string(bal);
                   
                } 
                
                outFile << row[0] << " " << row[1] << " " << row[2] << "\n";               
                

            } outFile.close();


        }

};

/*
    This class is for registering new users and logging in existing users.
    It checks for already existing usernames and returns either true or false.
*/

class users {
    
    std::vector<std::string> newuser;

    public:
        
        users() {
            loadUserDB();
        }

        bool addUser() {
                    
            std::string username, password;

            std::cout << R"(
    Great to hear you wish to make an account!
    Please type your username.
    )" << std::endl;
                                
            std::cin >> username;

            std::cout << R"(
    Next come up with a password.
    )" << std::endl;
                    
            std::cin >> password;            
            
            newuser.push_back(username);
            newuser.push_back(password);
            newuser.push_back(std::to_string(0));

            for (const auto& firstv : userDB) {
                for (const auto& usern : firstv) {
                    if (newuser[0] == usern) {
                        std::cout << R"(
    Sorry! That username was already taken.
    )" << std::endl;                    
                        return false;
                    }
                }
            }
            
            saveUserDB();

        /*
            The .txt file has to be updated/refreshed, in order
            for this to all work. A small headache, but it's only
            necessary when registering for the first time.
        */

            std::cout << R"(
    Due to technical reasons, you have to leave and 
    reboot the piggybank.exe file. 
    Then login with your recently created initials 
    and everything is set!'
    )" << std::endl;

            return true;

        }        

        bool checkUser() {
                    
            std::string username;
            std::string password;

            std::cout << R"(
    Please enter your username!
    )" << std::endl;
            std::cin >> username;

            std::cout << R"(
    Next type your password!
    )" << std::endl;
            std::cin >> password;

            for (const auto& row : userDB) {
                for (const auto& userdt : row) {
                    
                    if (username == row[0] && password == row[1]) {
                        std::cout << R"(
    Log in successful! Welcome back!
    )" << std::endl;
                        currentUser = username;
                        paswrd = password;
                        return true;
                    } 
                }
            }

            std::cout << R"(
    Invalid username or password. Please try again.
    )" << std::endl;

            return false;

        }

    private:
        void loadUserDB() {
            std::ifstream file("userDB.txt");
            
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string username, password;
                int bal;

                std::vector<std::string> lst;
                while (iss >> username >> password >> bal) {
                    lst.push_back(username);
                    lst.push_back(password);
                    lst.push_back(std::to_string(bal));
                }
                userDB.push_back(lst);
            }
            file.close();
        }
        
        void saveUserDB() {
            std::ofstream file("userDB.txt", std::ios::app);            

            file << newuser[0] << " " << newuser[1] << " " << newuser[2] << "\n";
            
            file.close();
        }
            
};

    /* 
        The main method. This is where it all
        begins. I know my code is very messy
        and I am 100% sure there are better
        examples out there. But since I recently
        took up C++ training, I am pretty damn
        happy with this. 

        Credits go to the Internet's vast tools and
        guides for teaching me about C++'s syntax
        and the countless abilities it has.

        Utilizing AI to easily ask for help, teach and
        locate bugs, that I simply couldn't see, was
        crucial to make this a reality.     
    */

int main() {
    
    users us;
    piggyBank pB;   

    char x;
    
    while (true) {
        std::cout << R"(
    [===========================================]
            WELCOME TO YOUR PIGGY BANK
    Start by logging in, registering, or quitting.
    [===========================================]
    Log in [L]     Register [R]       Quit [Q]
    )" << std::endl;
        std::cin >> x;
        
        switch (x){
        
            case 'L':
                if (us.checkUser()) {
                    pB.run();
                }
                break;
            case 'R': 
                if (us.addUser()) {
                    break;
                } break;
            case 'Q':
                return 0;
            default:
                std::cout << R"(
    Please type in a valid character.
    )" << std::endl;
                break;
            }
    }
    return 0;
}       
