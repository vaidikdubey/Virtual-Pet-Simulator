#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void petChoices(){
    cout << "1. Cat" << endl;
    cout << "2. Dog" << endl;
    cout << "3. Rabbit" << endl;
    cout << "4. Parrot" << endl;
    cout << "5. Tiger" << " -> Beware it can attack" << endl;
}

//Parent Class
class Pet{
protected:
    string name;
    int hunger;
    int happiness;
    int cleanliness;
    int consecutiveTurns;

public:
    Pet(const string& petName) : name(petName), hunger(50), happiness(50), cleanliness(50){}

    //Method to feed pet
    void feed(){
        hunger -= 10;
        happiness += 5;
        cleanliness -= 5;
        cout << "You feeded " << name << ". Hunger decreased, happiness increased." << endl;
    }

    //Method to play with pet
    void play(){
        happiness += 10;
        hunger += 5;
        cleanliness -= 5;
        cout << "You played with " << name << ". Happiness increased." << endl;
    }

    //Method to clean pet
    void clean(){
        cleanliness += 10;
        hunger += 5;
        cout << "You cleaned " << name << ". Cleanliness increased." << endl;
    }

    //Method to display pet's updated status after choice
    void displayStatus(){
        cout << "Pet Name: " << name << endl;
        cout << "Hunger: " << hunger << endl;
        cout << "Happiness: " << happiness << endl;
        cout << "Cleanliness: " << cleanliness << endl;
        cout << "Your Health: " << happiness << endl;
    }

    //Virtual function for special behavior of pets
    virtual void specialBehavior(){}

    //Method to update parameters based on consecutive terms
    void updateConsecuiteTurns(char lastAction){
        consecutiveTurns++;
        if(consecutiveTurns >= 3){
            if(lastAction == '1'){//Last action was feeding
                hunger += 10;
                cout << "Your pet is hungry because it wasn't played with or cleaned." << endl;
            }
            else if(lastAction == '2'){//Last a5ction was playing
                happiness -= 10;
                cout << "Your pet is unhappy because it wasn't fed or cleaned." << endl;
            }
            else if(lastAction == '3'){//Last action was cleaning
                cleanliness -= 10;
                 cout << "Your pet is dirty because it wasn't fed or played." << endl;
            }
            consecutiveTurns = 0; //Reset consecutive turns
        }
    }
};

//Child class Dog
class Dog : public Pet{
public:
    Dog(const string& petName) : Pet(petName){}
};

//Child class Cat
class Cat : public Pet{
public:
    Cat(const string& petName) : Pet(petName){}
};

//Child class Rabbit
class Rabbit : public Pet{
public:
    Rabbit(const string& petName) : Pet(petName){}
};

//Child class Parrot
class Parrot : public Pet{
public:
    Parrot(const string& petName) : Pet(petName){}
};

//Child class Tiger
class Tiger : public Pet{
private:
    int health;
public:
    Tiger(const string& petName) : Pet(petName), health(100){}

    //Overrride the special behavior of Tiger
    void specialBehavior() override{
        //Randomly decide if the tiger will attach (20% chance)
        if(rand() % 5 == 0){
            cout << "Oh no! The tiger attacked you!!" << endl;
            health -= 10;
        }

        //Check hunger level
        if(hunger >= 90){
            cout << "Oh no! The tiger is too hungry and attacked you! You died" << endl;
            health = 0;
        }

        //Check happiness level
        if(happiness < 30){
            cout << "Warning! The tiger is getting aggressive!" << endl;
            health -= 20;
        }

        //Automatically healing conditions
        if(happiness >=  70 && hunger <= 40){
            health += 10;
            cout << "Your wounds are healing due to your tiger's good mood and full stomach" << endl;
        }

        //Ensure health stays within bounds
        health = max(0, min(100, health));
    }

    //Method to display tiger's status including health
    void displayStatus(){
        Pet::displayStatus(); //Call base class displayStatus method
        cout << "Health: " << health << endl;
    }

    //Function to get health
    int getHealth() const{
        return health;
    }
};

int main(){
    srand(time(nullptr)); //SEed the random number generator for Tiger attack

    cout << "Welcome to Virtual Pet Simulator" << endl;
    cout << "Select the pet you want to have" << endl;

    petChoices();
    int petChoice;
    cin >> petChoice;
    cin.ignore(); //Clear newline characters from input

    string petName;
    cout << "Enter your Pet's name: ";
    getline(cin, petName);

    //Create a pet based on user's choice
    Pet* myPet;
    switch(petChoice){
        case 1:
            myPet = new Cat(petName);
            break;

        case 2:
            myPet = new Dog(petName);
            break;

        case 3:
            myPet = new Rabbit(petName);
            break;

        case 4:
            myPet = new Parrot(petName);
            break;
        
        case 5:
            myPet = new Tiger(petName);
            break;

        default:
            cout << "Invalid Pet choice" << endl;
            return 1;
    }

    //Game loop
    char choice;
    char lastAction = ' ';//Initializing the last action
    do{
        //Display Pet's status
        myPet->displayStatus();

        //Special behavior for Tiger
        myPet->specialBehavior();

        //End the game if user's health reaches 0
        if(petChoice = 5 && static_cast<Tiger*>(myPet)->getHealth() <= 0){
            cout << "You died. Game over!!" << endl;
            delete myPet;
            return 0;
        }

        //Display menu options
        cout << "\nChoose an action for your pet: " << endl;
        cout << "1. Feed" << endl;
        cout << "2. Play" << endl;
        cout << "3. Clean" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); //Clear newline characters from input buffer

        switch(choice){
            case '1':
                myPet->feed();
                lastAction = '1';
                break;
            case '2':
                myPet->play();
                lastAction = '2';
                break;
            case '3':
                myPet->clean();
                lastAction = '3';
                break;
            case '4':
                cout << "Exiting the game" << endl;
                cout << "Thanks for playing" << endl;
                break;
            default:
                cout << "Invalid choice. Try again" << endl;
        }
    }while(choice != '4');

    delete myPet; //Free the memory allcoated for Pet object

    return 0;
}