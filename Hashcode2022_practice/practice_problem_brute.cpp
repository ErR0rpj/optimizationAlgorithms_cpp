// This is brute force with dp. It does not run fully for long test cases but gives the best answer.
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

// dont considr incl, excl in next recurse

map<set<string>, int> dp;
int customers;
set<string> ingredientsToTake;
set<string> ingredientsNotToTake;
int maxCustomers = 0;

void capy(set<string> from, set<string> &to)
{
    for (set<string>::iterator i = from.begin(); i != from.end(); i++)
    {
        to.insert(*i);
    }
}

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
    cout << "\n";
}

void includeIngredients(set<string> &ingredientsToTakeSet, unordered_map<string, int> ingredient_negative)
{
    for (unordered_map<string, int>::iterator i = ingredient_negative.begin(); i != ingredient_negative.end(); i++)
    {
        if (i->second == 0)
        {
            ingredientsToTakeSet.insert(i->first);
        }
    }
}

void excludeIngredients(set<string> &ingredientsNotToTakeSet, unordered_map<string, int> ingredient_positive)
{
    for (unordered_map<string, int>::iterator i = ingredient_positive.begin(); i != ingredient_positive.end(); i++)
    {
        if (i->second == 0)
        {
            ingredientsNotToTakeSet.insert(i->first);
        }
    }
}

void resetPointing(string ingredientNow, set<string> &ingredientsToInclude, set<string> &ingredientsToExclude, unordered_map<string, int> &ingredient_total, unordered_map<string, int> &ingredient_positive, unordered_map<string, int> &ingredient_negative, set<int> &customersIneligible, int *customerCount, vector<string> customer_likes[], vector<string> customer_dislikes[])
{
    for (int i = 0; i < customers; i++)
    {
        if (customersIneligible.find(i) == customersIneligible.end())
        {
            int cust = find(customer_dislikes[i].begin(), customer_dislikes[i].end(), ingredientNow) - customer_dislikes[i].begin();
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
                    if (ing != ingredientNow)
                    {
                        ingredient_total[ing]++;
                        ingredient_negative[ing]--;
                    }
                }
                *customerCount = *customerCount - 1;
                customersIneligible.insert(i);
            }
        }
    }

    includeIngredients(ingredientsToInclude, ingredient_negative);
    excludeIngredients(ingredientsToExclude, ingredient_positive);
}

void countCustomers(set<string> ingredientsToInclude, vector<string> customer_likes[], vector<string> customer_dislikes[], int customerCount, set<int> customersIneligible)
{

    int count = 0;
    for (int i = 0; i < customers; i++)
    {
        bool approved = false;

        if (customersIneligible.find(i) == customersIneligible.end())
        {
            for (int j = 0; j < customer_likes[i].size(); j++)
            {
                string ing = customer_likes[i][j];
                if (ingredientsToInclude.find(ing) != ingredientsToInclude.end())
                {
                    approved = true;
                }
                else
                {
                    approved = false;
                    break;
                }
            }

            if (approved)
            {
                for (int j = 0; j < customer_dislikes[i].size(); j++)
                {
                    string ing = customer_dislikes[i][j];
                    if (ingredientsToInclude.find(ing) != ingredientsToInclude.end())
                    {
                        approved = false;
                        break;
                    }
                }
            }
        }

        if (approved)
        {
            count++;
        }
    }

    dp[ingredientsToInclude] = count;

    if (count > maxCustomers)
    {
        maxCustomers = count;
        cout << "mac customers: " << maxCustomers << '\n';
        capy(ingredientsToInclude, ingredientsToTake);
    }
}

void solutionWithout0(string ingredientNow, unordered_map<string, int> ingredient_positive, unordered_map<string, int> ingredient_negative, unordered_map<string, int> ingredient_total, set<int> customersIneligible, int customerCount, set<string> ingredientsToInclude, set<string> ingredientsToExclude, vector<string> customer_likes[], vector<string> customer_dislikes[])
{

    if (ingredientNow != "")
    {
        ingredientsToInclude.insert(ingredientNow);
        resetPointing(ingredientNow, ingredientsToInclude, ingredientsToExclude, ingredient_total, ingredient_positive, ingredient_negative, customersIneligible, &customerCount, customer_likes, customer_dislikes);
    }
    if (dp.find(ingredientsToInclude) != dp.end())
    {
        return;
    }

    // Returns if total number of customer left are less than max customers till now.
    if (customerCount <= maxCustomers)
    {
        return;
    }
    countCustomers(ingredientsToInclude, customer_likes, customer_dislikes, customerCount, customersIneligible);

    for (unordered_map<string, int>::iterator i = ingredient_total.begin(); i != ingredient_total.end(); i++)
    {
        string ingredient = i->first;
        if (ingredient_total[ingredient] <= 0 || ingredientsToInclude.find(ingredient) != ingredientsToInclude.end() || ingredientsToExclude.find(ingredient) != ingredientsToExclude.end())
        {

            continue;
        }

        solutionWithout0(ingredient, ingredient_positive, ingredient_negative, ingredient_total, customersIneligible, customerCount, ingredientsToInclude, ingredientsToExclude, customer_likes, customer_dislikes);
    }
}

// code can be optimized with:
// 1. using DP
// 2. sorting total points map and using highest point first.
void solutionWith0(string ingredientNow, unordered_map<string, int> ingredient_positive, unordered_map<string, int> ingredient_negative, unordered_map<string, int> ingredient_total, set<int> customersIneligible, int customerCount, set<string> ingredientsToInclude, set<string> ingredientsToExclude, vector<string> customer_likes[], vector<string> customer_dislikes[])
{

    if (ingredientNow != "")
    {
        ingredientsToInclude.insert(ingredientNow);
        resetPointing(ingredientNow, ingredientsToInclude, ingredientsToExclude, ingredient_total, ingredient_positive, ingredient_negative, customersIneligible, &customerCount, customer_likes, customer_dislikes);
    }

    if (dp.find(ingredientsToInclude) != dp.end())
    {
        return;
    }

    // Returns if total number of customer left are less than max customers till now.
    if (customerCount <= maxCustomers)
    {
        return;
    }
    countCustomers(ingredientsToInclude, customer_likes, customer_dislikes, customerCount, customersIneligible);

    for (unordered_map<string, int>::iterator i = ingredient_total.begin(); i != ingredient_total.end(); i++)
    {
        string ingredient = i->first;
        if (ingredient_total[ingredient] < 0 || ingredientsToInclude.find(ingredient) != ingredientsToInclude.end() || ingredientsToExclude.find(ingredient) != ingredientsToExclude.end())
        {

            continue;
        }

        solutionWith0(ingredient, ingredient_positive, ingredient_negative, ingredient_total, customersIneligible, customerCount, ingredientsToInclude, ingredientsToExclude, customer_likes, customer_dislikes);
    }
}

int main()
{
    ifstream input;
    input.open("input_5.txt");
    ofstream output;
    output.open("output_5.txt");

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

    // outputTable(ingredient_positive, ingredient_negative, ingredient_points);

    includeIngredients(ingredientsToTake, ingredient_negative);
    excludeIngredients(ingredientsNotToTake, ingredient_positive);

    set<string> tempIngredientsToInclude;
    set<string> tempIngredientsToExclude;

    capy(ingredientsToTake, tempIngredientsToInclude);
    capy(ingredientsNotToTake, tempIngredientsToExclude);

    set<int> customersIneligible;

    // countCustomers(tempIngredientsToInclude, customer_likes, customer_dislikes, customers, customersIneligible);

    solutionWith0("", ingredient_positive, ingredient_negative, ingredient_points, customersIneligible, customers, tempIngredientsToInclude, tempIngredientsToExclude, customer_likes, customer_dislikes);
    dp.clear();
    // solutionWithout0("", ingredient_positive, ingredient_negative, ingredient_points, customersIneligebile, customers, tempIngredientsToInclude, tempIngredientsToExclude, customer_likes, customer_dislikes);

    cout << "\nMaximum customers: " << maxCustomers << "\n";
    output << ingredientsToTake.size();
    for (set<string>::iterator i = ingredientsToTake.begin(); i != ingredientsToTake.end(); i++)
    {
        output << " " << *i;
    }

    return 0;
}
