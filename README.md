# Baked Goods Tracker on C++

## NOTE:
- Dito ilalagay ung na document na errors and ung naging solutions.<br>
- Use ai carefully, make sure na naiintihan natin ung binibigay satin ni ai<br>
- Try to comment na din sa bawat part ng magiging code para sa iba para madali nila maintindihan ung code.<br>
- Feel free to edit and test ung gawa natin, basta pakilagay nalang ng details sa pag nagcommit na para maiintindihan ung changes.<br>
  (Or gawa nalang ng bagong branch tas i pull request para mareview and ma merge sa main branch)<br>
  
<br>

## TIPS:<br>
- If wala kayong VsCode and gusto itry ung program since may kasama na yang file handling, i download nyo nalang ung .exe file and ung Menu.txt sa laptop/pc nyo and kailangan magkasama sa isang folder yang .exe and .txt file. Thanks! <br>

## PROGRAM< EXPLANATION<br>
May dalawang menu dito sa program, isa sa customer and isa sa admin (satin). Basically ang admin menu is customer menu sya pero with more new features (parang subscription services lang ganun pero di ka magbabayad obv). Sa Customer menu is order, display, search, exit (in order) and then sa Admin menu ang additional is ung Add and delete ng product including din ung update ng product (with possibly a seperate menu pero may additional option dun na "Admin" dun sa pinaka menu talaga). Dont worry na ung sa pagsasave ng info sa file since automatically na sya. As admin syempre may login system and hidden sya sa mga options sa customer menu, katulad din ng isang login system is pwede mo din paltan ung username and password just like usual. Wait nalang siguro na maimplement ko yan.

## CHALLENGES AND SOLUTION:<br>
### NOTE:<br>
- Dito muna ilalagay lahat ng naencounter na Challenges during the coding process and ung naging solutions before ilagay sa pinaka paper natin.<br>
<br>

**Challenges:** 
- Some parts of the program doesnt work like the developers intended to work. <br>
- Developers need to figure out a way to make sure the program isn't case sensitive in user input, as it hampers the user's experience with the program. <br>
- The Program's ability to remember what the items are listed in its menu.<br>

<br>

**Solution:**
- Experiment and try until the issue gets resolved.<br>
- Algorithm header alongside transform() syntax makes the program case-insensitive<br> 
- Using filehandling and its properties enables the program to remember what its menu contents without re entering. <br>

<br>

## FEATURES:<br>
🟥 - No Progress<br>
🟧 - Currently Working <br>
🟩 - Done<br>

<br>

- A Menu Interface.<br> (**STATUS:** 🟧)
- Adding new products to the inventory.<br> (**STATUS:** 🟩, Additional Comment: TANGINA AYOQ NA ~~MABUHAY~~)
- Updating current product information.<br> (**STATUS:** 🟩)
- Deleting product records from the inventory.<br> (**STATUS:** 🟩)
- Can Search for a specific product.<br> (**STATUS:** 🟩, Additional Comment: took a ton of hours to fix that bruh ._.)
- Display all available products and their details.<br> (**STATUS:** 🟩)
- Monitor and display current stock quantities.<br> (**STATUS:** 🟩, Additional Comment: personally idk ano gagawin here)
- Accept and process customer orders.<br> (**STATUS:** 🟥)
- Validate stock availability before confirming an order.<br> (**STATUS:** 🟥)
- Automatically deduct inventory quantities after a successful order.<br> (**STATUS:** 🟥)
- Save and retrieve inventory records.<br> (**STATUS:** 🟩)
- Saves all transactions in a file.<br> (**STATUS:** 🟥)
- Generate transaction summaries or order receipts. <br> (**STATUS:** 🟥)
- Admin menu
   A. Unique Admin Password
   B. Can save admin login credentials on a file
   C. Can change admin name and password
   D. Admins unlocked more features than the customer
   E. Unique Admin menu
   F. Possibly more pa if may naisip pako
<br>



