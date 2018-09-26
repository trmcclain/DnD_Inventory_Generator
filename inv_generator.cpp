// reading a text file
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <map>
using namespace std;
struct item{
	string name;
	int price;
	string misc;
	string rarity;
	string util;
	int rarity_weight;
} ;
void listGenerator(int file_size, string wealth, string shop_type, item item_list[]);
bool dupCheck(item invlist[], item checkMe, int sSize);
bool weightCheck(item checkMe, int weight);
void printList(item invlist[], int sSize, string wealth, string shop_type);

int main () {
	srand( time( NULL ) );
  	string line;
  	int file_size=0;
  	ifstream myfile;
  	int comma_flag = 0;
 	myfile.open(".\\magical item inventory - All.csv");

  	if (myfile.is_open()){
		while ( myfile.good()){
			getline(myfile,line);
			file_size++;
   		}
		myfile.close();
	}
	cout<<"CSV contains "<< file_size<<" rows."<<endl;
	string full_list[file_size];
	item item_list[file_size];
	string list_element;
	int i = 0;
	myfile.open(".\\magical item inventory - All.csv");
	if(myfile.is_open()){
		while(myfile.good()){
			getline(myfile, line);
			string token;
			string delimiter = ",";
			size_t pos = 0;
			comma_flag=0;
			//cout<<"Before while statement"<<endl;
			while ((pos=line.find(delimiter)) != string::npos){
				//cout<<"Parsing Line: "<<line<<endl;
				token = line.substr(0,pos);
				item_list[i].rarity_weight=0;
				//cout<<"Before Switch Statement"<<'\t'<<"Token: "<<token<<endl;
				switch(comma_flag){
					case 0 :{
						item_list[i].name=token;
						break;
						}
					case 1 :{
						stringstream convert(token);
						int price=0;
						convert >> price;
						if(price == 0){
							int die = rand() % 10 + 1;
							price=die*10;
						}
						item_list[i].price=price;
						break;
					}
					case 2 : {
						item_list[i].misc = token;
						break;
					}
					case 3 : {
						item_list[i].rarity = token;
						break;
					}
					case 4 : {
						item_list[i].util = token;
						break;
					}
					case 5 : {
						stringstream convert(token);
						int weight;
						convert >> weight;
						item_list[i].rarity_weight = weight;
						//cout<<"Comma Flag: "<<comma_flag<<'\t'<<item_list[i].rarity_weight<<endl;
						//cout<<"Token: "<<token<<endl;
						//system("PAUSE");
						break;
					}
					default : {
						cout<<"Invalid entry"<<endl;
						break;
					}
				}
				comma_flag++;
				if(line.length() > 1)
					line.erase(0,pos+ delimiter.length());
			}
				//cout<<"Finished parsing line. Iterating to next: "<<i<<endl;
				if(item_list[i].rarity_weight == 0){
					stringstream convert(line);
					int weight;
					convert >> weight;
					item_list[i].rarity_weight = weight;
				}
				i++;
		}
		cout<<"Completed read-in of file. Composing pool."<<endl;
	}	

	else 
		cout << "Unable to open file"; 
	myfile.close();
	int rarity;
	int shop;
	
	string wealth;
	string shop_type;
	char cont;
	do{
		
		cout<<"Choose your stock:"<<endl;
		cout<<'\t'<<"1. Meager"<<endl;
		cout<<'\t'<<"2. Average"<<endl;
		cout<<'\t'<<"3. Wealthy"<<endl;
		cout<<'\t'<<"4. Collector"<<endl;
		cin>>rarity;
		
		switch(rarity){
			case 1 :{
				wealth = "Meager";
				break;
			}
			
			case 2 :{
				wealth = "Average";
				break;
			}
			case 3 :{
				wealth = "Wealthy";
				break;
			}
			case 4 :{
				wealth = "Collector";
				break;
			}
			default : {
						cout<<"Invalid entry"<<endl;
						break;
					}
		}
		
	
		
		cout<<"Choose your shop:"<<endl;
		cout<<'\t'<<"1. Apothecary"<<endl;
		cout<<'\t'<<"2. Blacksmith"<<endl;
		cout<<'\t'<<"3. Enchanter"<<endl;
		cout<<'\t'<<"4. General"<<endl;
		cin>>shop;
		
		switch(shop){
			case 1 :{
				shop_type = "Apothecary";
				break;
			}
			
			case 2 :{
				shop_type = "Blacksmith";
				break;
			}
			case 3 :{
				shop_type = "Enchanter";
				break;
			}
			case 4 :{
				shop_type = "General";
				break;
			}
			default : {
						cout<<"Invalid entry"<<endl;
						break;
					}
		}
		
	
		listGenerator(file_size, wealth, shop_type, item_list);
		cout<<"Generate a new list? (y/n): ";
		cin>>cont;
	}while(cont == 'y');

	return 0;
}
/***********************************************
*Meager - 5-10 items, no Game-Changers or Summoning
*	95% Common/Uncommon, 5% rare
*Average - 8-12 items, no Game-Changers or Summoning
*	75% Common/Uncommon, 25% rare, 0% very rare
*Wealthy - 12-18 items
*	60% Common/Uncommon, 25% rare, 10% very rare, 5% legendary
*Collector - 15-20 items
*	40% Common/Uncommon, 20% rare, 20% very rare, 10% legendary
*
*Apothecary - Conumables, (Summoning if Wealthy or Collector)
*Blacksmith - Combat, (Game-changer if Wealthy or Collector)
*Enchanter - Non-Combat, (Summoning & Game-changer if Wealthy or Collector)
*General - Consumables, Non-Combat, Combat, (Game-changer if Wealthy or Collector)
*/

void listGenerator(int size, string wealth, string shop_type, item item_list[]){
	srand( time( NULL ) );
	item selection_pool[size];
	char print;
	int j=0;
	int shopsize=0;
	int tier1 =0; //common-uncommon
	int tier2 =0; //rare
	int tier3 =0; //very rare
	int tier4 =0; //legendary
	
	map<string, int> sTypes;
	sTypes["Apothecary"]=0;
	sTypes["Blacksmith"]=1;
	sTypes["Enchanter"]=2;
	sTypes["General"]=3;

	if(wealth == "Average" || wealth == "Meager"){
		switch (sTypes[shop_type]){
			case 0:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 3 && (item_list[i].misc == "Healing Potion" || item_list[i].misc == "Potion")){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}			
				break;
			}
			case 1:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 3 && item_list[i].util == "Combat" && item_list[i].misc != "Instrument" && item_list[i].misc != "Spell Weapon"){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
			case 2:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 3 && (item_list[i].util == "Non-Combat" || item_list[i].misc == "Spell Weapon")){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
			case 3:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 3 && (item_list[i].util == "Consumable" || item_list[i].util == "Non-Combat" || item_list[i].util == "Combat")){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
		}
	}
	if(wealth == "Wealthy" || wealth == "Collector"){
		switch (sTypes[shop_type]){
			case 0:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 5 && ((item_list[i].misc == "Healing Potion" || item_list[i].misc == "Potion") || item_list[i].util == "Summoning")){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
			case 1:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 5 && (item_list[i].util == "Combat" || item_list[i].util == "Game-changer") && item_list[i].misc != "Instrument" && item_list[i].misc != "Spell Weapon"){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
			case 2:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 5 && (item_list[i].util == "Non-Combat" || item_list[i].util == "Game-changer"|| item_list[i].util == "Summoning" || item_list[i].misc == "Spell Weapon")){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
			case 3:{
				for(int i=0; i<size; i++){
					if(item_list[i].rarity_weight <= 5 && (item_list[i].util == "Consumable" || item_list[i].util == "Non-Combat" || item_list[i].util == "Combat" || item_list[i].util == "Game-changer")){
						selection_pool[j] = item_list[i];
						j++;
					}
			
				}				
				break;
			}
		}
	
		
	}
	int new_pool_size =0;
	for(int m =0; m<size; m++){
		if(selection_pool[m].name != "")
			new_pool_size++;
	}
	//cout<<"New Pool Size: "<<new_pool_size<<endl;
	//system("PAUSE");
	item new_list[new_pool_size];
	int iter=0;
	for(int n=0; n<size; n++){
		if(selection_pool[n].name != ""){
			new_list[iter]= selection_pool[n];
			iter++;
		}		
	}
	
	int maxweight =0;
	if(wealth == "Meager"){
		shopsize = rand() % 5 + 5;
		//cout<<"Shop size: "<<shopsize<<endl;
		tier1 = floor(shopsize*.95);
		if(shop_type == "Apothecary")
			tier1=shopsize;
		tier2 = shopsize-tier1;
		//cout<<"Tier 2: "<<endl;
		maxweight = 3;
	}
	if(wealth == "Average"){
		shopsize = rand() % 4 + 8;
		cout<<"Shop size: "<<shopsize<<endl;
		tier1=floor(shopsize*.75);
		tier2=floor(shopsize*.25);
		//cout<<"Tier 2: "<<tier2<<endl;
		//tier3=shopsize-tier1-tier2;
		maxweight = 4;
		
	}
	if(wealth == "Wealthy"){
		shopsize = rand() % 6 + 12;
		cout<<"Shop size: "<<shopsize<<endl;
		tier1=floor(shopsize*.60);
		tier2=floor(shopsize*.25);
		tier3=floor(shopsize*.1);
		tier4= shopsize-tier1-tier2-tier3;
		//cout<<"Tier 2: "<<tier2<<"\t"<<"Tier 3: "<<tier3<<"\t"<<"Tier 4: "<<tier4<<endl;
		maxweight = 5;

	}
	if(wealth == "Collector"){
		shopsize = rand() % 5 + 15;
		cout<<"Shop size: "<<shopsize<<endl;
		tier1=floor(shopsize*.45);
		tier2=floor(shopsize*.25);
		tier3=floor(shopsize*.2);
		tier4= shopsize-tier1-tier2-tier3;
		//cout<<"Tier 2: "<<tier2<<"\t"<<"Tier 3: "<<tier3<<"\t"<<"Tier 4: "<<tier4<<endl;
		maxweight = 5;
	}
	item invlist[shopsize];
	int size_check = 0;
	//int index=0;
	cout<<"Inventory List:"<<endl;
	cout<<"Name"<<"\t"<<"Rarity"<<"\t"<<"Price"<<endl;
	while(size_check <=shopsize){
		if(size_check >= shopsize){
			break;
		}
		for(int i=0; i<tier1; i++){
			int element=0;
			do{
			//	cout<<"****IN TIER1 DO-WHILE****"<<endl;
				element = rand() % new_pool_size;
				if(weightCheck(new_list[element], 2) && !dupCheck(invlist, new_list[element], shopsize)){
					invlist[size_check] = new_list[element];
					cout<<invlist[size_check].name<<"\t"<<invlist[size_check].rarity<<"\t"<<invlist[size_check].price<<endl;
					size_check++;
				}
				if(new_list[element].rarity_weight <= 2){
					break;
				}
				//system("PAUSE");
			}while(new_list[element].rarity_weight > 2);
			
		}
		//cout<<"Tier 1 Set."<<endl;
		for(int i=0; i<tier2; i++){
			int element=0;
			do{
				//cout<<"****IN TIER2 DO-WHILE****"<<endl;
				element = rand() % new_pool_size;
				if(weightCheck(new_list[element], 3) && !dupCheck(invlist, new_list[element], shopsize)){
					invlist[size_check] = new_list[element];
					cout<<invlist[size_check].name<<"\t"<<invlist[size_check].rarity<<"\t"<<invlist[size_check].price<<endl;
					size_check++;
				}
				if(new_list[element].rarity_weight == 3){
					break;
				}
			}while(new_list[element].rarity_weight != 3);
			
		}
		//cout<<"Tier 2 Set."<<endl;
		if(tier3 > 0){	
			for(int i=0; i<tier3; i++){
				int element=0;
				/*for(int seek = 0; seek < new_pool_size; seek++){
					if(new_list[seek].rarity_weight == 4){
						cout<<seek<<'\t'<<new_list[seek].name<<endl;;
					}
				}*/
				do{
					element = rand() % new_pool_size;
					if(weightCheck(new_list[element], 4) && !dupCheck(invlist, new_list[element], shopsize)){
						invlist[size_check] = new_list[element];
						cout<<invlist[size_check].name<<"\t"<<invlist[size_check].rarity<<"\t"<<invlist[size_check].price<<endl;
						size_check++;
					}
					if(new_list[element].rarity_weight == 4){
						break;
					}		
				}while(new_list[element].rarity_weight != 4);
				
			}
			//cout<<"Tier 3 Set."<<endl;
			for(int i=0; i<tier4; i++){
				//cout<<"***In Legendary Loop***"<<endl;
				int element=0;
				do{
					element = rand() % new_pool_size;
					if(weightCheck(new_list[element], 5) && !dupCheck(invlist, new_list[element], shopsize)){
						invlist[size_check] = new_list[element];
						cout<<invlist[size_check].name<<"\t"<<invlist[size_check].rarity<<"\t"<<invlist[size_check].price<<endl;
						size_check++;
					}
					if(new_list[element].rarity_weight == 5){
						break;
					}					
				}while(new_list[element].rarity_weight != 5);
			}
			//cout<<"Tier 4 Set."<<endl;
		}
		if(size_check == shopsize){
			break;
		}
		
	}
	cout<<"Print to outfile? (y/n): ";
	cin>>print;
	if(print=='y')
		printList(invlist, shopsize, wealth, shop_type);
	/*for(int j =0; j<shopsize; j++){
		cout<<invlist[j].name<<'\t'<<invlist[j].rarity<<'\t'<<invlist[j].price<<endl;
	}*/
	
	//code end
}

bool dupCheck(item invlist[], item checkMe, int sSize){
	if(checkMe.util.compare("Consumable")==0 && (checkMe.misc.compare("Healing Potion")==0 || checkMe.misc.compare("Scroll"))){
		return false;
	}
	for(int i=0; i<sSize; i++){
		item temp=invlist[i];
		if(temp.name.compare(checkMe.name) == 0 && temp.misc.compare(checkMe.misc)==0){
			return true;
		}
	}
	return false;
}
bool weightCheck(item checkMe, int weight){
	switch (weight){
		case 1:{
			if(checkMe.rarity_weight <= weight){
				return true;
			}
			else{
				return false;
			}						
			break;
		}
		case 2:{
			if(checkMe.rarity_weight <= weight){
				return true;
			}
			else{
				return false;
			}			
			break;
		}
		case 3:{
			if(checkMe.rarity_weight == weight){
				return true;
			}
			else{
				return false;
			}						
			break;
		}
		case 4:{
			if(checkMe.rarity_weight == weight){
				return true;
			}
			else{
				return false;
			}						
			break;
		}
		case 5: {
			if(checkMe.rarity_weight == weight){
				return true;
			}
			else{
				return false;
			}
			break;
		}
		default:{
			return false;
			break;
		}
	}

}

void printList(item invlist[], int sSize, string wealth, string shop_type){
	ofstream txtOut;
	string temp = "inventoryList_";
	temp.append(wealth);
	temp.append(shop_type);
	temp.append(".txt");
	txtOut.open(temp.c_str());
	txtOut<<"Item"<<"\t"<<"Price"<<"\t"<<"Misc"<<"\t"<<"Rarity"<<"\t"<<"Utility"<<endl;
	for(int i =0;i<sSize;i++){
		txtOut<<invlist[i].name<<"\t"<<invlist[i].price<<"\t"<<invlist[i].misc<<"\t"<<invlist[i].rarity<<"\t"<<invlist[i].util<<endl;
	}
	txtOut.close();
}

