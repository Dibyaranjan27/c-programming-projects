# **Banking System (C Program)**
A simple Banking System built in C, which allows users to create accounts, deposit, withdraw, transfer money, and view transaction logs using a file-based storage system.

## **📌 Features**
- **Create Account** – Register a new bank account in `accounts.txt`.  
- **Deposit Money** – Add funds to an account.  
- **Withdraw Money** – Withdraw funds while ensuring sufficient balance.  
- **Transfer Money** – Transfer funds between accounts.  
- **View Account Details** – Check account balance and information.  
- **Transaction Logs** – Maintain a history of all transactions in `transactions.txt`.  
- **User-friendly Menu** – An interactive, terminal-based menu system. 
- **Colorful Output** – Uses **Green (Success), Red (Errors), Yellow (Warnings)** for better readability.  

---

## 🔧 Requirements  
Before running this program, ensure that you have the following:  
- A **C compiler** (such as **GCC**) installed  
  ```sh
  # Install GCC on Ubuntu/Debian
  sudo apt update && sudo apt install gcc
  ```  
  ```sh
  # Install GCC on Windows (via MinGW)
  winget install -e --id MSYS2.MSYS2 
  ``` 
- A **terminal** or **command prompt**
- A text editor (**VS Code**, **Notepad++**, etc.)

---

## **Installation and Usage**
### **1. Clone or Download the Project**
```sh
git clone https://github.com/Dibyaranjan27/c-programming-projects.git
cd bank-management-system
```

### **2. Compile the program**
```sh
gcc main.c banking.c -o banking_system
```
### **3. Run the program**
```sh
./banking_system
```

---

## 🚀 Usage
1. Select an option from the menu
2. Enter the required account details
3. Perform operations like creating an account, depositing, withdrawing, transferring money, and checking transaction logs 

---

## 📂 File Structure

```
/bank-management-system  
│── main.c                 # Main program with the menu system  
│── banking.c              # Core banking logic and functions  
│── banking.h              # Header file with function prototypes  
│── accounts.txt           # Stores account details  
│── transactions.txt       # Stores transaction history  
│── README.md              # Documentation  

```

## 🤝 Contribution
Feel free to contribute! Fork the repository, make improvements, and submit a pull request. 😊

## 📜 License
This project is open-source and available under the MIT License.

## 💡 Author
Dibyaranjan Maharana  
[GitHub](https://github.com/Dibyaranjan27)  | [LinkedIn](https://www.linkedin.com/in/dibyaranjan-maharana-1228012b2/) 