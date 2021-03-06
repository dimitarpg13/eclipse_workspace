/*
 * IndustryInfo.h
 *
 *  Created on: Oct 11, 2014
 *      Author: root
 */

#ifndef INDUSTRYINFO_H_
#define INDUSTRYINFO_H_

#include <string>
#include <vector>


using namespace std;

namespace Algorithms {



class CompanyInfo;

class IndustryInfo {
public:
	IndustryInfo(string name);
	virtual ~IndustryInfo();

	string getName();
    IndustryInfo* getParent();
    void setParent(IndustryInfo *);
    void addChild(IndustryInfo * );

    vector<IndustryInfo*>& getChildren();
    vector<CompanyInfo*>& getCompanies();

    void addCompany(CompanyInfo * );

private:
	string m_sName;
	IndustryInfo* m_pParent;
	vector<IndustryInfo*> m_vChildren;
	vector<CompanyInfo*> m_vCompanies;
};

class CompanyInfo {
public:
	CompanyInfo(string name, float marketCap, float revenue);
	virtual ~CompanyInfo();
    string getName();
    float getMarketCap();
    float getRevenue();
    vector<IndustryInfo*>& getIndustries();
    void addIndustry(IndustryInfo *);

private:
	string m_sName;
	float m_fMarketCap;
	float m_fRevenue;
    vector<IndustryInfo*> m_vIndustries;
};

} /* namespace Algorithms */

#endif /* INDUSTRYINFO_H_ */
