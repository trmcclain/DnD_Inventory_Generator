Thank you for downloading this program!

It's a fairly basic c++ program which reads in the CSV file and selects an inventory list based on user inputs.

Changes to this CSV can be made at the user's discretion. If you choose to do so, there are 5 columns which must be maintained:
Item, Price, Misc, Rarity, Utility, Rarity Weight.

The Misc columns I used to seperate out items that wouldn't be in certain shops using keywords like Healing Potion, Potion, Instrument, Spell Weapon, etc... This way you won't find a Blacksmith with a very rare harp or an apothecary with a wand.

The Rarity Weight values are simply mapped:
	1 - Common
	2 - Uncommon
	3 - Rare
	4 - Very Rare
	5 - Legendary

To run the program, you can either compile the cpp or unzip the executable and run it from there.

When the program runs you'll be prompted by 4 options to determine the wealth and shopsize of the shop:
	-Meager
	-Average
	-Wealthy
	-Collector

Second prompt is where you will choose the kind of shop:
	-Apothecary
	-Blacksmith
	-Enchanter
	-General

Afterwhich a list will generate and you will have an option to export it to a text file in the same directory as the exe.

That's all there is too it. Thanks again!