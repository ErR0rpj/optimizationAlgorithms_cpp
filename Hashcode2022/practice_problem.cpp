#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std;

int customers;
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

void resetPointing(string ingredientNow, unordered_set<string> ingredientsToInclude, unordered_map<string, int> &ingredient_total, unordered_map<string, int> &ingredient_positive, unordered_map<string, int> &ingredient_negative, set<int> &customersIneligible, int customerCount, vector<string> customer_likes[], vector<string> customer_dislikes[])
{
    for (int i = 0; i < customers; i++)
    {
        if (customersIneligible.find(i) == customersIneligible.end())
        {
            int cust = find(customer_dislikes[i].begin(), customer_dislikes[i].end(), i) - customer_dislikes[i].begin();
            if (cust < customer_dislikes[i].size())
            {
                for (int j = 0; j < customer_likes[i].size(); j++)
                {
                    string ing = customer_likes[i][j];
                    ingredient_total[ing]--;
                    ingredient_positive[ing]--;
                }
                for (int j = 0; j < customer_dislikes[i].size(); j++)
                {
                    string ing = customer_dislikes[i][j];
                    ingredient_total[ing]++;
                    ingredient_negative[ing]--;
                }
                customerCount--;
                customersIneligible.insert(i);
            }
        }
    }
}

// code can be optimized with:
// 1. using DP
// 2. sorting total points map and using highest point first.
void solution(string ingredientNow, unordered_map<string, int> ingredient_positive, unordered_map<string, int> ingredient_negative, unordered_map<string, int> ingredient_total, set<int> customersIneligible, int customerCount, unordered_set<string> ingredientsToInclude, unordered_set<string> ingredientsToExclude, vector<string> customer_likes[], vector<string> customer_dislikes[])
{
    if (ingredientNow != "")
    {
        ingredientsToInclude.insert(ingredientNow);
        resetPointing(ingredientNow, ingredientsToInclude, ingredient_total, ingredient_positive, ingredient_negative, customersIneligible, customerCount, customer_likes, customer_dislikes);
    }

    for (unordered_map<string, int>::iterator i = ingredient_total.begin(); i != ingredient_total.end(); i++)
    {
        string ingredient = i->first;
        if (ingredient_total[ingredient] <= 0 || ingredientsToInclude.find(ingredient) != ingredientsToInclude.end() || ingredientsToExclude.find(ingredient) != ingredientsToExclude.end())
        {
            continue;
        }
    }
}

int main()
{
    ifstream input;
    input.open("input_3.txt");
    ofstream output;
    output.open("output_3.txt");

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

    unordered_set<string> tempIngredientsToInclude;
    unordered_set<string> tempIngredientsToExclude;
    unordered_set<string>::iterator itr1;
    unordered_set<string>::iterator itr2;

    copy(ingredientsToTake.begin(), ingredientsToTake.end(), inserter(tempIngredientsToInclude, itr1));
    copy(ingredientsNotToTake.begin(), ingredientsNotToTake.end(), inserter(tempIngredientsToExclude, itr2));

    set<int> customersIneligebile;
    solution("", ingredient_positive, ingredient_negative, ingredient_points, customersIneligebile, customers, tempIngredientsToInclude, tempIngredientsToExclude, customer_likes, customer_dislikes);

    cout << "\nMaximum customers: " << maxCustomers << "\n";

    output << ingredientsToTake.size();
    for (unordered_set<string>::iterator i = ingredientsToTake.begin(); i != ingredientsToTake.end(); i++)
    {
        output << " " << *i;
    }

    return 0;
}
