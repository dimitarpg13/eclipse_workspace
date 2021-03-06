/*
 * IndustryInfo.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: root
 */

#include "IndustryInfo.h"

namespace Algorithms {

IndustryInfo::IndustryInfo(string name)
{
   m_sName = name;
}

IndustryInfo::~IndustryInfo()
{
	for (vector<IndustryInfo*>::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it )
		delete *it;
}

string IndustryInfo::getName()
{
	return m_sName;
}

IndustryInfo* IndustryInfo::getParent()
{
	return m_pParent;
}

void IndustryInfo::setParent(IndustryInfo * parent)
{
	m_pParent = parent;
}


void IndustryInfo::addChild(IndustryInfo * child)
{
	if (child != nullptr)
		m_vChildren.push_back(child);
}

vector<IndustryInfo*>& IndustryInfo::getChildren()
{
	return m_vChildren;
}

vector<CompanyInfo*>& IndustryInfo::getCompanies()
{
	return m_vCompanies;
}

void IndustryInfo::addCompany(CompanyInfo * company)
{
	if (company != nullptr)
		m_vCompanies.push_back(company);
}


CompanyInfo::CompanyInfo(string name, float marketCap, float revenue)
{
    m_sName = name;
	m_fMarketCap = marketCap;
	m_fRevenue = revenue;
}

CompanyInfo::~CompanyInfo()
{
	// TODO
}

string CompanyInfo::getName()
{
	return m_sName;
};

vector<IndustryInfo*>& CompanyInfo::getIndustries()
{
	return m_vIndustries;
};

float CompanyInfo::getMarketCap()
{
	return m_fMarketCap;
};

float CompanyInfo::getRevenue()
{
	return m_fRevenue;
};

void CompanyInfo::addIndustry(IndustryInfo * industry)
{
	m_vIndustries.push_back(industry);
};

} /* namespace Algorithms */

