/*
 * XMLSave.h
 *
 *  Created on: 23.02.2016
 *      Author: patrick
 */

#ifndef XMLSAVE_H_
#define XMLSAVE_H_
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <fstream>
using std::string;
using std::list;
using std::map;
using std::pair;
using std::to_string;
using std::ofstream;

class XMLSave{
public:
	XMLSave();
	virtual ~XMLSave();
	void _saveXml(string out,int id,string name,string tilefile,int speed,int playerFrameWidth
			,int playerFrameHeight,int playerY,string playerStdWeapon,string tilePlayer
			,string tileBot);
private:
	class XMLItem
	{
		public:
			std::list<XMLItem> childs;
			std::map<string,string> attributes;
			string value;
			string name;
			XMLItem(string name):name(name){}
			XMLItem(string name,string val):name(name),value(val){}
			void addChildItem(XMLItem x){
				childs.push_back(x);
			}
			void addAttribute(string name,string value){
				attributes.insert(std::pair<string, string>(name,value));
			}
			void setValue(string val){
				value=val;
			}
	};
	void _saveXmlFile(string File,XMLItem& root);
	string _getXMLItemString(XMLItem& item,int ebene);
};

#endif /* XMLSAVE_H_ */
