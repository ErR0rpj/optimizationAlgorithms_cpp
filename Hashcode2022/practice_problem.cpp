#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

unordered_set<string> ingredientsToTake;
unordered_set<string> ingredientsNotToTake;
int maxCustomers = 0;

// Prints the table with points of every ingredient.
void outputTable(unordered_map<string, int> ingredient_positive,
                 unordered_map<string, int> ingredient_negative, unordered_map<string, int> ingredient_points)
{
    for (unordered_map<string, int>::iterator i = ingredient_points.begin(); i != ingredient_points.end(); i++)
    {
        string name = i->first;
        cout << name << "  " << ingredient_positive[name] << " " << ingredient_negative[name] << " " << ingredient_points[name];
        cout << "\n";
    }
}

void includeIngredients(unordered_set<string> ingredientsToTakeSet, unordered_map<string, int> ingredient_negative)
{
    for (unordered_map<string, int>::iterator i = ingredient_negative.begin(); i != ingredient_negative.end(); i++)
    {
        if (i->second == 0)
        {
            ingredientsToTakeSet.insert(i->first);
        }
    }
}

void excludeIngredients(unordered_set<string> ingredientsNotToTakeSet, unordered_map<string, int> ingredient_positive)
{
    for (unordered_map<string, int>::iterator i = ingredient_positive.begin(); i != ingredient_positive.end(); i++)
    {
        if (i->second == 0)
        {
            ingredientsNotToTakeSet.insert(i->first);
        }
    }
}

int main()
{
    ifstream input;
    input.open("input_3.txt");
    ofstream output;
    output.open("output_3.txt");

    int customers;
    input >> customers;

    vector<string> customer_likes[customers];
    vector<string> customer_dislikes[customers];

    // // 1 point to ingredient if it is liked by someone, -1 if disliked
    unordered_map<string, int> ingredient_points;
    unordered_map<string, int> ingredient_positive;
    unordered_map<string, int> ingredient_negative;

    // Calculates points
    for (int i = 0; i < customers * 2; i++)
    {
        int itemsCount;
        input >> itemsCount;

        while (itemsCount--)
        {
            string ingredient;
            input >> ingredient;
            if (ingredient_points.find(ingredient) == ingredient_points.end())
            {
                ingredient_points[ingredient] = 0;
                ingredient_negative[ingredient] = 0;
                ingredient_positive[ingredient] = 0;
            }

            if (i % 2 == 0)
            {
                customer_likes[i / 2].push_back(ingredient);
                ingredient_points[ingredient]++;
                ingredient_positive[ingredient]++;
            }
            else
            {
                customer_dislikes[i / 2].push_back(ingredient);
                ingredient_points[ingredient]--;
                ingredient_negative[ingredient]++;
            }
        }
    }

    outputTable(ingredient_positive, ingredient_negative, ingredient_points);

    includeIngredients(ingredientsToTake, ingredient_negative);
    excludeIngredients(ingredientsNotToTake, ingredient_positive);

    unordered_set<string> ans;
    int count = 0;

    for (unordered_map<string, int>::iterator i = ingredient_points.begin(); i != ingredient_points.end(); i++)
    {
        if (i->second > 0)
        {
            ans.insert(i->first);
        }
    }

    count = ans.size();
    output << count;
    for (unordered_set<string>::iterator i = ans.begin(); i != ans.end(); i++)
    {
        output << " " << *i;
    }

    return 0;
}
