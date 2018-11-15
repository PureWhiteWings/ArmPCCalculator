/*
Copyright (c) 2018 RunnerScrab

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "pch.h"
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "../sqlite3lib/sqlite3.h"
#include "SkillsDB.h"
#include "Character.h"
#include "CArmSkillApp.h"
#include <afxwin.h>


/*
int Test(void)
{
	std::unique_ptr<SkillsDB> upDb;
	
	try
	{
		upDb = std::make_unique<SkillsDB>();
	}
	catch (std::exception ex)
	{
		printf("Error: %s\n", ex.what());
		return -1;
	}

	std::map<std::string, Skill> skill_list;
	std::map<std::string, PC_Class> pc_class_list;
	
	char mainguild[64] = { 0 };
	char subguild[64] = { 0 };
	std::cout << "Main guild name:";
	std::cin.getline(mainguild, 64);

	if (pc_class_list.find(mainguild) == pc_class_list.end() || 
		pc_class_list.find(mainguild)->second.m_bIsSubclass)
	{
		printf("Could not find main guild with name %s\n", mainguild);
	
		return 0;
	}

	std::cout << "Sub guild name:";
	std::cin.getline(subguild, 64);

	if (pc_class_list.find(subguild) == pc_class_list.end() || 
		!pc_class_list.find(subguild)->second.m_bIsSubclass)
	{
		printf("Could not find subguild with name %s\n", subguild);
		return 0;
	}

	Character pc;
	pc.m_pMainClass = &pc_class_list[mainguild];
	pc.m_pSubClass = &pc_class_list[subguild];

	printf("\nClass/Subguild: %s/%s\n", pc.m_pMainClass->m_strName.c_str(),
		pc.m_pSubClass->m_strName.c_str());
	pc.ProcessClassAbilities();
	printf("%s\n", pc.m_AbilityReport.c_str());
	pc.ProcessClassSkills();
	printf("%s\n", pc.m_SkillReport.c_str());
	getchar();
	return 0;
}
*/