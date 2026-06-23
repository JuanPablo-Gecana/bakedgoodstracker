# Baked Goods Tracker on C++

## INTRODUCTION: <br>
PANADERYA NI HUWAN PABLO is a terminal based program written in c++ and it simulates as for an inventory tracker for a small filipino Bakery that sells filipino baked delicacies. <br>
<br>
It welcomes the customer as the program starts and the program has a special way of welcoming back to the customer if that customer ordered a product using the program in the past. The customer can order a product, browse the lists of available products through displaying them, and search for a specific product at its will and has an ability to change customer without requiring the user to leave and enter the program again. It can cater normal orders, pre-orders if the product they requested is currently out of stock, custom orders and an optional candle for cakes. As you pre-order, you can pick a pickup date for a product as the product restocks.<br>
<br>
Theres a hidden ADMIN option that if entered, it requires a username and password. Once the two conditions are met, it gives a whole new menu that give whole control over the inventory of the bakery as it can add and remove a product, either updating a certain product's price or quantity, and has the power to view the history records of the bakery such as its transaction record, and pending pre-orders and custom cake orders and managing other admin accounts.<br>
<br>
All of this data is saved in a text file, ensuring information can't be lost during seperate runs of the program.<br>
<br>

## REQUIREMENTS:
• Updated vscode.
• Installed C++, C++ related extensions, and code runner extension for vscode.
• All of the necessary files such as the c++ file.
• Latest mingw64 c++ compiler from MSYS2 .
• C++ standard needs to be C++20.

## FEATURES:<br>
- Menu-Driven Interface<br>
- Filipino Language Program <br>
- Can add, update, delete and search for a product in the Inventory. <br>
   A. Can automatically deduct quantity from pre orders and transfer the pre order details to the transactions record<br>
   B. if you search a term (eg. cake) any item with that name will be included. <br>
- Can display all products regardless of its availability based on stock. <br>
- Ordering system that also has pre-ordering and custom order's on cakes. <br>
   A. Pre ordering can happen if the requested product by the customer is currently out of stock.<br>
   B. Customer can avail a candle for free if the order was a cake. <br>
- Additional admin menu that requires a username and password. <br>
   A. Unique Admin Username and Password <br>
   B. Can save admin login credentials on a file <br>
   C. Can change admin name and password <br>
   D. Admins unlocked more features than the customer <br>
   E. Unique Admin menu <br>
   F. Can add an admin <br>
   G. Can remove an admin  <br>
   H. Admin can access and view pre-orders <br>
   I. Admin can access and remove custom orders once it is completed <br>
   J. Admins can access and view the transactions record <br>
- Customer's can type their names and will be remembered and greeted by the program upon entering. <br>
- Program can remember user and admin inputs. <br> 
