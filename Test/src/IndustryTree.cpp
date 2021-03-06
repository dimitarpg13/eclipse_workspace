/*
 * IndustryTree.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: root
 */

#include "IndustryTree.h"

namespace Algorithms {

IndustryTree::IndustryTree(string fileName) {
    m_pRoot = new IndustryInfo("Classification");
    parseIndustries(fileName);

}



IndustryTree::~IndustryTree() {

	// delete all IndustryInfo instances
	delete m_pRoot;

	// delete all companyInfo instances
	map<string,CompanyInfo*>::iterator it;
    for (it = m_mapCompanies.begin(); it != m_mapCompanies.end(); ++it )
		delete it->second;

}

bool IndustryTree::parseIndustries (string fileName)
{
	bool res = false;

	try
	{
		ifstream ifs;
		ifs.open(fileName);
		if (ifs.is_open())
		{
		   string line, val, name, parentName;
           IndustryInfo * cur = nullptr, * parent = nullptr;
           pair<map<string,IndustryInfo*>::iterator,bool> ret;
           map<string,IndustryInfo*>::iterator it;
		   while (getline(ifs, line, '\n'))
		   {
			   //cout << line << '\n';

			   if (line.substr(0,2)=="//")
            	   continue;

			   parent = nullptr;
			   cur = nullptr;

			   istringstream iss(line);
			   int i=0;
			   while (getline(iss, val, '|' ))
			   {
				  // cout << '\t' << val << '\n';
                  if (i==1)
                	  name = val;
                  else if (i==2)
                	  parentName = val;
                  else if (i > 2)
                	  break;
                  i++;
			   }


			   it = m_mapIndustries.find(name);
			   if (it == m_mapIndustries.end())
			   {
				  cur = new IndustryInfo(name);
				  m_mapIndustries[name] = cur;

				  if (!parentName.empty())
				  {
					  it = m_mapIndustries.find(parentName);
					  if (it == m_mapIndustries.end())
					  {
						  parent = new IndustryInfo(parentName);
						  // since we do not know who is the parent
						  // of the parent industry insert it at the root
						  m_pRoot->addChild(parent);
					  }
					  else
					  {
						  parent = it->second;
					  }

					  parent->addChild(cur);
					  cur->setParent(parent);

				  }
				  else
				  {
                      // the current industry does not have a parent so
					  // insert it at the root
					  m_pRoot->addChild(cur);
				  }

				  if (!res)
				     res = true;
			   }
			   else
			   {
				   if (!parentName.empty())
				   {
					   it = m_mapIndustries.find(parentName);
					   if (it == m_mapIndustries.end())
					   {
					 	   parent = new IndustryInfo(parentName);
					 	   // since we do not know who is the parent
					 	   // of the parent industry insert it at the root
					 	   m_pRoot->addChild(parent);
					   }
				   }
			   }


		   }

		   ifs.close();
		}
	}
	catch (...)
	{
	   cout << "Could not parse file " + fileName << '\n';
	}

	return res;
}


string IndustryTree::getCompanyKey(string name, float marketCap, float revenue)
{
	stringstream sstr;

    sstr << name;
    sstr << ":";
    sstr << setprecision(2) << fixed << marketCap;
    sstr << ":";
    sstr << setprecision(2) << fixed << revenue;
    return sstr.str();
}

bool IndustryTree::addCompanies(string fileName)
{
	bool res = false;

	try
	{
		ifstream ifs;
		ifs.open(fileName);
		if (ifs.is_open())
		{
		   string line, val, compName, industryName, compKey;
		   float marketCap, revenue;
           CompanyInfo * company = nullptr;
           IndustryInfo * industry = nullptr;
           pair<map<string,IndustryInfo*>::iterator,bool> ret;
           map<string,CompanyInfo*>::iterator itComp;
           map<string,IndustryInfo*>::iterator itInd;
		   while (getline(ifs, line, '\n'))
		   {

			   //cout << line << '\n';
			   if (line.substr(0,2)=="//" || line.empty())
            	   continue;

			   istringstream iss(line);
			   int i=0;
			   while (getline(iss, val, '|' ))
			   {
				  // cout << '\t' << val << '\n';
                  if (i==1)
                	  compName = val;
                  else if (i==2)
                	  industryName = val;
                  else if (i==3)
                	  marketCap = stof(val);
                  else if (i==4)
                	  revenue = stof(val);
                  else if (i>4)
                	  break;
                  i++;
			   }

			   if (compName=="Gemvax & Kael")
			   {
				   cout << compName << "'s industry: " << industryName << "\n";
			   }

               compKey = compName;//getCompanyKey(compName,marketCap,revenue);
			   itComp = m_mapCompanies.find(compKey);
			   if (itComp == m_mapCompanies.end())
			   {
                  company = new CompanyInfo(compName,marketCap,revenue);

                  itInd = m_mapIndustries.find(industryName);

                  if (itInd == m_mapIndustries.end())
                  {
                     // if the industry is not found in the tree
                	 // then add it to the root
                     industry = new IndustryInfo(industryName);
                     m_pRoot->addChild(industry);
                  }
                  else
                     industry = itInd->second;

                  industry->addCompany(company);
                  company->addIndustry(industry);
                  m_mapCompanies[compKey] = company;
			   }
			   else
			   {
                  company = itComp->second;
                  itInd = m_mapIndustries.find(industryName);

                  if (itInd == m_mapIndustries.end())
                  {
                	  // if the industry is not found in the tree
                	  // then add it to the root
                	  industry = new IndustryInfo(industryName);
                	  m_pRoot->addChild(industry);

                  }
                  else
                  {
                	  industry = itInd->second;
                  }

                  industry->addCompany(company);
                  company->addIndustry(industry);


			   }

		   }

		   ifs.close();
		}
	}
	catch (...)
	{
	   cout << "Could not parse file " + fileName << '\n';
	}

	return res;
}

bool IndustryTree::addIndustries(string fileName)
{
	bool res = parseIndustries(fileName);

	return res;
}

void IndustryTree::printIndustries()
{
   cout << m_pRoot->getName() << "\n[\n";
   printIndustries(m_pRoot, "");
   cout << "]\n";
}

void IndustryTree::printIndustries(IndustryInfo * industry, string indent)
{

	if (industry != nullptr)
	{
		if (industry != m_pRoot)
           cout << indent << industry->getName() << "\n";

		string newIndent = indent + "\t";
		vector<IndustryInfo*> industries = industry->getChildren();
		for (vector<IndustryInfo*>::iterator it = industries.begin(); it != industries.end(); ++it )
            printIndustries(*it,newIndent);
	}
}

void IndustryTree::findCompanies(string industryName, string propertyName)
{
	string name_lc = propertyName;
	name_lc.erase(name_lc.find_last_not_of(" \n\r\t")+1);
	transform(name_lc.begin(), name_lc.end(), name_lc.begin(), ::tolower);
	IndustryInfo * industry = nullptr;

	map<string,IndustryInfo*>::iterator it = m_mapIndustries.find(industryName);
    if (it != m_mapIndustries.end())
    {
    	industry = it->second;
        set<CompanyInfo*> compSet;
        findCompanies(industry,compSet);

        vector<CompanyInfo*> companies(compSet.begin(),compSet.end());

		if (name_lc=="companyname")
		{
           sort(companies.begin(), companies.end(), m_foCompNameCmp);
		}
		else if (name_lc=="marketcap")
		{
		   sort(companies.begin(), companies.end(), m_foCompMrktCapCmp);
		}
		else if (name_lc=="revenue")
		{
		   sort(companies.begin(), companies.end(), m_foCompRevenueCmp);
		}
		else
		{
			throw invalid_argument("findCompanies: invalid property name "+propertyName);
		}

		cout << "[";
		for (vector<CompanyInfo*>::iterator it = companies.begin(); it != companies.end(); ++it )
		{
			cout << (*it)->getName();
			if (it != companies.end() - 1)
				cout << ", ";
		}
		cout << "]" << "\n";
    }
    else
    {
    	cout << "[" << "]" << "\n";
    }


}


void IndustryTree::findCompanies(IndustryInfo * industry, set<CompanyInfo*>& companies)
{

	if (industry != nullptr)
	{
		vector<CompanyInfo*>& curCompanies = industry->getCompanies();
		for (vector<CompanyInfo*>::iterator itComp = curCompanies.begin(); itComp != curCompanies.end(); ++itComp )
		   companies.insert(*itComp);

		vector<IndustryInfo*>& children = industry->getChildren();
		for (vector<IndustryInfo*>::iterator itInd = children.begin(); itInd != children.end(); ++itInd )
		{
           findCompanies(*itInd, companies);
		}
	}

}


void IndustryTree::findIndustries(string companyName)
{
	CompanyInfo * company = nullptr;
    map<string,CompanyInfo*>::iterator it = m_mapCompanies.find(companyName);
    if (it != m_mapCompanies.end())
    {
       company = it->second;
       vector<IndustryInfo*>& industries = company->getIndustries();
       cout << "[";
       for (vector<IndustryInfo*>::iterator it = industries.begin(); it != industries.end(); ++it )
       {
       	  cout << (*it)->getName();
       	  if (it != industries.end() - 1)
       		 cout << ", ";
       }
       cout << "]\n";
    }
}

} /* namespace Algorithms */
