#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
class Warrior
{
public:
    int health;
    int damage;
    bool hitten;
    bool hitted;

    Warrior()
    {
        Warrior::health = 100;
        Warrior::damage = 10;
        Warrior::hitten = false;
        Warrior::hitted = false;
    }

    void hit(Warrior &warrior)
    {

        int Chance = rand() % 10 + 1;
        bool Critical = false;
        if (Chance == 2)
        {
            Critical = true;
            Warrior::health = (Warrior::health - (Warrior::damage + (Warrior::damage * ((rand() % 30 + 1) / 100.0))));
            Warrior::hitted = true;
        }
        else
        {
            warrior.takeDamage(Warrior::damage);
            Warrior::hitted = true;
        }
    }

    void takeDamage(int damage)
    {
        Warrior::hitten = true;
        if (Warrior::health > 0)
        {
            Warrior::health = (Warrior::health - (damage - (damage * ((rand() % 50 + 1) / 100.0))));
        }
        else
        {
        }
    };

    void print()
    {
        cout << "Warrior's health is : " << health << endl;
        if (Warrior::health <= 0)
        {
        }
    };
    void copyWarrior(Warrior a)
    {
        health = a.health;
        damage = a.damage;
    }
    void resetWarrior()
    {
        if (Warrior::hitten == true)
        {
            Warrior::hitten = false;
        }
        if (Warrior::hitted == true)
        {
            Warrior::hitted = false;
        }
        //reset flags za hitted it hitten :D
    }
    bool isWarriorAlive()
    {
        if (Warrior::health > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Army
{
public:
    int numberOfWarriors = 2;
    Warrior arr[2] = {};
    Army()
    {
    }
    int getFirstWarriorNotHitted()
    {
        for (int i = 0; i < numberOfWarriors; i++)
        {
            if (arr[i].hitted == false)
            {
                return i;
            }
        }
        return -1;
    }
    int getFirstWarriorNotHitten()
    {
        for (int i = 0; i < numberOfWarriors; i++)
        {
            if (arr[i].hitten == false)
            {
                return i;
            }
        }
        return -1;
    }

    void resetFlag()
    {
        for (int i = 0; i < numberOfWarriors; i++)
        {
            arr[i].resetWarrior();
        }

        // za svaki warriot pravis reset odnosno resetWarrior":D
    }

    bool isArmyAlive()
    {
        //loop da proveris svakog od warrira dali je allive :D

        for (int i = 0; i < numberOfWarriors; i++)
        {
            if (arr[i].isWarriorAlive() == true)
            {
                return true;
            }
        }
        return false;
    }

    int getfirstAliveWarrior()
    {
        for (int i = 0; i < numberOfWarriors; i++)
        {
            if (arr[i].health > 0)
            {
                return i;
            }
        }
        return -1;
    }
};

int main()
{
    Army red;
    Army blue;

    while (red.isArmyAlive() == true && blue.isArmyAlive() == true)
    {
        int i = red.getFirstWarriorNotHitted();
        int s = red.getFirstWarriorNotHitten();
        if (i > -1)
        {
            if (s > -1)
            {
                int j = blue.getFirstWarriorNotHitten();
                int p = blue.getFirstWarriorNotHitted();
                if (j > -1)
                {
                    if (p > -1)
                    {
                        if (red.arr[i].isWarriorAlive() == true && blue.arr[j].isWarriorAlive() == true && blue.arr[p].isWarriorAlive() == true && red.arr[s].isWarriorAlive() == true)
                        {   //red udara
                            red.arr[i].hit(blue.arr[j]);
                            cout << "Blue army index: " << j << "\nHealth: " << blue.arr[j].health << endl;
                            if (blue.arr[j].isWarriorAlive() == false)
                            {
                                cout << "Warrior is dead!" << endl;
                            }
                            //blue udara
                            blue.arr[p].hit(red.arr[s]);
                            cout << "Red army index: " << s << "\nHealth: " << red.arr[s].health << endl;
                            if (red.arr[s].isWarriorAlive() == false)
                            {
                                cout << "Warrior is dead!" << endl;
                            }  
                        }
                        else if (red.arr[s].isWarriorAlive() == false && blue.arr[p].isWarriorAlive() == true)
                        {
                            int m = red.getfirstAliveWarrior();
                            if (m > -1)
                            {
                                blue.arr[p].hit(red.arr[m]);
                                cout << "Red army index: " << m << "\nHealth: " << red.arr[m].health << endl;
                                if (red.arr[m].isWarriorAlive() == false)
                                {
                                    cout << "Warrior is dead!" << endl;
                                }
                            }
                        }
                        else if (red.arr[i].isWarriorAlive() == true && blue.arr[j].isWarriorAlive() == false)
                        {
                            int n = blue.getfirstAliveWarrior();
                            if (n > -1)
                            {
                                red.arr[i].hit(blue.arr[n]);
                                cout << "Red army index: " << i << "\nHealth: " << red.arr[i].health << endl;
                                cout << "Blue army index: " << n << "\nHealth: " << blue.arr[n].health << endl;
                                if (blue.arr[n].isWarriorAlive() == false)
                                {
                                    cout << "Warrior is dead!" << endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        blue.resetFlag();
                    }
                }
                else
                {
                    blue.resetFlag();
                }
            }
            else
            {
                red.resetFlag();
            }
        }
        else
        {
            red.resetFlag();
        }
    }
    if (red.isArmyAlive() == true)
    {
        cout << "Red army won!" << endl;
    }
    if (blue.isArmyAlive() == true)
    {
        cout << "Blue army won!" << endl;
    }
}
