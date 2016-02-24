/*
 * XMLSave.cpp
 *
 *  Created on: 23.02.2016
 *      Author: patrick
 */

#include "XMLSave.h"

XMLSave::XMLSave() {
	// TODO Auto-generated constructor stub

}

XMLSave::~XMLSave() {
	// TODO Auto-generated destructor stub
}

void XMLSave::_saveXml(string out,int id,string name,string tilefile,int speed,int playerFrameWidth
					,int playerFrameHeight,int playerY,string playerStdWeapon,string tilePlayer
					,string tileBot
					){
	XMLItem level("level");
	level.addChildItem(XMLItem("id",'"'+std::to_string(id)+'"'));
	level.addChildItem(XMLItem("name",'"'+name+'"'));
	XMLItem bg("tileset");
	bg.addAttribute("filename",tilefile);
	bg.addChildItem(XMLItem("scrollspeed",std::to_string(speed)));
	level.addChildItem(bg);
	XMLItem player("player");
	player.addAttribute("filename",tilePlayer);
	player.addChildItem(XMLItem("frameWidth",std::to_string(playerFrameWidth)));
	player.addChildItem(XMLItem("frameHeight",std::to_string(playerFrameHeight)));
	player.addChildItem(XMLItem("positionY",std::to_string(playerY)));
	player.addChildItem(XMLItem("stdWeapon",playerStdWeapon));
	level.addChildItem(player);
	/*for (iterator = bots.begin(); iterator != bots.end(); ++iterator) {
	    //*iterator;
		XMLItem bot("bot");
		bot.addAttribute("filename",tileBot);
		bot.addChildItem(XMLItem("frameWidth",playerFrameWidth));
		bot.addChildItem(XMLItem("frameHeight",playerFrameHeight));
		bot.addChildItem(XMLItem("positionX",iterator.X()));
		bot.addChildItem(XMLItem("positionY",iterator.Y()));
		bot.addChildItem(XMLItem("tileID",iterator.tileID()));
		bot.addChildItem(XMLItem("typ",iterator.type()));
		bot.addChildItem(XMLItem("color",iterator.color()));
		level.addChildItem(bot);
		XMLItem npc("npc");
		XMLItem func("move");
		func.addAttribute("function",iterator.func());
		npc.addChildItem(func);
		npc.addChildItem(XMLItem("fire_rate",iterator.firerate()));
		npc.addChildItem(XMLItem("speed",iterator.speed()));
		XMLItem weapon("weapon",iterator.weaponStage());
		weapon.addAttribute("type",iterator.weaponType());
		npc.addChildItem(weapon);
		XMLItem item("item",iterator.itemType());
		item.addAttribute("filename",iterator.tileitem());
		npc.addChildItem(item);
		bot.addChildItem(npc);
	}
	for (iterator = bots.begin(); iterator != bots.end(); ++iterator) {

		XMLItem item("item");
		item.addAttribute("filename",iterator.itemTile);
		item.addChildItem(XMLItem("frameWidth",iterator.itemFrameWidth));
		item.addChildItem(XMLItem("frameHeight",iterator.itemFrameHeight));
		item.addChildItem(XMLItem("positionX",iterator.X()));
		item.addChildItem(XMLItem("positionY",iterator.Y()));
		item.addChildItem(XMLItem("typ",iterator.type()));
		level.addChildItem(item);
	}*/
	_saveXmlFile(out,level);
}

void XMLSave::_saveXmlFile(string sFile,XMLItem& root){
	string data=_getXMLItemString(root,0);
	ofstream myfile;
	myfile.open (sFile);
	myfile << data;
	myfile.close();
}

string XMLSave::_getXMLItemString(XMLItem& item,int ebene){
	std::list<XMLItem> childs=item.childs;
	std::map<string,string> attributes=item.attributes;
	string tabs="";
	for(int i=0;i<ebene;i++)
		tabs+="\t";
	string itemText=tabs+"<";
	itemText+=item.name;
	for(auto outer_iter=attributes.begin(); outer_iter!=attributes.end(); ++outer_iter){
		itemText+=" "+outer_iter->first;
		itemText+="=\""+outer_iter->second+"\"";
	}
	if(childs.size()<=0 && item.value=="")
		itemText+=" /";
	itemText+=">";
	if(childs.size()>0)
		itemText+="\n";
	if(item.value!=""){
		if(childs.size()>0)
			itemText+=tabs+"\t";
		itemText+=item.value+(childs.size()>0?"\n":"");
	}
	for(std::list<XMLItem>::iterator iterator = childs.begin(); iterator != childs.end(); iterator++) {
		itemText+=_getXMLItemString(*iterator,ebene+1)+"\n";
	}
	if(!(childs.size()<=0 && item.value=="")){
		if(childs.size()>0)
			itemText+=tabs;
		itemText+="</"+item.name+">";
	}
	return itemText;
}
