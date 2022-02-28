#include <bits/stdc++.h>
using namespace std;

struct skill
{
    string name;
    int level;
};

struct project
{
    string name;
    int totalDays;
    int score;
    int bestBefore;
    int skills_count;
    vector<skill> skillsList;
};

struct contributor
{
    string name;
    int skills_count;
    map<string, int> skillsList;
};

bool comp(project p1, project p2)
{
    if (p1.bestBefore != p2.bestBefore)
    {
        return p1.bestBefore < p2.bestBefore;
    }

    return p1.totalDays < p2.totalDays;
}

int main()
{
    ifstream input;
    input.open("input_1.txt");
    ofstream output;
    output.open("output_1.txt");

    int contributors_count;
    int projects_count;

    input >> contributors_count >> projects_count;

    vector<contributor> contributors(contributors_count);
    vector<project> projects(projects_count);

    map<string, map<string, int>> skillsToContributor;

    // input for contributor
    for (int i = 0; i < contributors_count; i++)
    {
        input >> contributors[i].name >> contributors[i].skills_count;

        for (int j = 0; j < contributors[i].skills_count; j++)
        {
            skill current_role;
            input >> current_role.name >> current_role.level;
            contributors[i].skillsList[current_role.name] = current_role.level;

            if (skillsToContributor.find(current_role.name) != skillsToContributor.end())
            {
                map<string, int> temp;
                temp[contributors[i].name] = current_role.level;
                if ((skillsToContributor[current_role.name].begin()->second) < current_role.level)
                {
                    skillsToContributor[current_role.name] = temp;
                }
            }
            else
            {
                map<string, int> temp;
                temp[contributors[i].name] = current_role.level;
                skillsToContributor[current_role.name] = temp;
            }
        }
    }

    // input for projects
    for (int i = 0; i < projects_count; i++)
    {
        input >> projects[i].name >> projects[i].totalDays >> projects[i].score >> projects[i].bestBefore >> projects[i].skills_count;

        for (int j = 0; j < projects[i].skills_count; j++)
        {
            skill current_skill;
            input >> current_skill.name >> current_skill.level;
            projects[i].skillsList.push_back(current_skill);
        }
    }

    sort(projects.begin(), projects.end(), comp);

    int projects_planned_count = 0;
    map<string, set<string>> projects_planned;
    set<string> rejected_projects;

    for (int i = 0; i < projects_count; i++)
    {
        int skillFound = 0;
        set<string> temp;
        string notTaken;

        for (int j = 0; j < projects[i].skills_count; j++)
        {
            string skillname = projects[i].skillsList[j].name;
            int skilllevel = projects[i].skillsList[j].level;

            if (skillsToContributor.find(skillname) != skillsToContributor.end())
            {
                if ((skillsToContributor[skillname].begin()->second) >= skilllevel)
                {
                    skillFound++;
                    if (temp.find(skillsToContributor[skillname].begin()->first) == temp.end())
                    {
                        temp.insert(skillsToContributor[skillname].begin()->first);
                    }
                    else
                    {
                    }
                    continue;
                }
                else
                {
                    skillFound = -1;
                    break;
                }
            }
        }
        if (skillFound == projects[i].skills_count)
        {
        }
        if (skillFound == -1)
        {
            rejected_projects.insert(projects[i].name);
            continue;
        }
    }

    return 0;
}