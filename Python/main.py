class acc_hold:

    def __init__(self, id):
        self.usrnm = id                                                                                                                                      
        self.fln = f"{id}.txt"
        with open(f"{id}.txt", 'r') as f:
            data = f.read()
        self.fn = data.split("\n")[0]
        self.sn = data.split("\n")[1]
        self.age = data.split("\n")[2]
        self.balance = data.split("\n")[3]
        self.pin = data.split("\n")[4]

    def wr_fl(self):
        data = f"{self.fn}\n{self.sn}\n{self.age}\n{self.balance}\n{self.pin}"
        with open(self.fln, 'w') as f:
            f.write(data)

    def deposit(self):
        amnt = input("Enter the amount you want to deposit:\t")
        self.balance = int(self.balance)+int(amnt)
        self.wr_fl()

    def withdraw(self):
        if (self.check_pin()):
            return
        else:
            amnt = self.check_amount()
            self.balance = int(self.balance)-amnt
            self.wr_fl()
    
    @property
    def inquiry(self):
        return f"\nTotal balance:\t{self.balance}"

    @property
    def details(self):
        return f"\nName: {self.fn} {self.sn}\nAge: {self.age}\nTotal balance: {self.balance}\n"

    def check_pin(self):
        i = 0
        while True:
            if (input("Enter your transaction pin:\t") == self.pin):
                break
            else:
                i += 1
                if (i <= 3):
                    print("INVALID TRANSACTION PIN..!!\n")
                else:
                    print(
                        "You have entered the invalid transaction pin more than 3 times.....\n")
                    return True

    def check_amount(self):
        while True:
            try:
                amnt = int(
                    input("Enter the amount you want to withdraw/transfer:\n"))
                if (amnt >= int(self.balance)):
                    print("The amount exceeded your total balance.!!")
                else:
                    return amnt
            except:
                print("Enter amount correctly...\n")

    def transfer(self):
        if (self.check_pin()):
            return
        else:
            while True:
                try:
                    while True:
                        receiver = input(
                            "Enter the username of account where you want to transfer balance:\n")
                        if (receiver == self.usrnm):
                            print(
                                "You cannot transfer the money to yourself...!!!\n")
                        else:
                            break
                    amnt = self.check_amount()
                    re_acc = acc_hold(receiver)
                    self.balance = int(self.balance)-amnt
                    self.wr_fl()
                    re_acc.balance = int(re_acc.balance)+amnt
                    re_acc.wr_fl()
                    break
                except:
                    print("Sorry... The username doesn't exist\n")

def ask_pw():
    while True:            
        password = input("Enter your password:\t")
        if (len(password) >= 5 and len(password) <= 20):                     
            if (input("Confirm password:\t") != password):
                print("Password mismatch..!!\n")
            else:
                break
        else:
            print("Password must be 5 to 20 characters..!!\n")     
    return password

def ask_pin():
    while True:    
        try:
            pin = (input("Enter your transaction pin (4 digits):\t"))
            int_pin=int(pin)
            if (len(pin)==4):                
                if ((input("Confirm transaction pin:\t")) != pin):
                    print("Transaction pin mismatch..!!\n")
                else:
                    break
            else:
                print("Enter 4 digits only...!!!\n")
        except:
            print("Pin must be integer value..!!\n")           
    return int_pin

def login():
    i = 0
    legit = False
    print("For Login..")
    while (legit == False):
        username = input("Enter your username:\t")
        password = input("Enter password:\t")
        with open("saved_accounts.txt", "r") as f:
            for line in f:
                stored_username, stored_pass = line.strip().split(",")
                if (username == stored_username and password == stored_pass):
                    legit = True
                    break
                else:
                    legit = False
        if legit:
            print("LOGIN SUCCESFULL\n")
            acc = acc_hold(username)
            menu(acc)
        else:
            i += 1
            if (i <= 3):
                print("INVALID USERNAME/PASS\n")
            else:
                print(
                    "You have entered the invalid username/password more than 3 times.....\n")
                break

def ask_create():
    if (input("Do you want to create your account in Bank?(y/n)\t") == 'y'):
        cr_acc()
    else:
        pass

def startup():
    print("Welcome to Bank")
    print("---------------\n")
    while True:
        r = input("Do you have your account in our bank? (y/n)\t")
        if (r == 'n'):
            ask_create()
            break
        elif (r == 'y'):
            try:
                login()
                break
            except:
                print("Sorry..!! You don't have any accounts in our bank.\n")
                ask_create()
                break
        else:
            print("Wrong Input!!\n")

def menu(acc):
    opt = input("1. Deposit\n2. Withdraw\n3. Balance Inquiry\n4. Balance tranfer\n5. User Details\n6. Log out\n7. Create new account\n8. Exit\n")
    if (opt == '1'):
        acc.deposit()
        menu(acc)
    elif (opt == '2'):
        acc.withdraw()
        menu(acc)
    elif (opt == '3'):
        print(acc.inquiry)
        menu(acc)
    elif (opt == '4'):
        acc.transfer()
        menu(acc)
    elif (opt == '5'):
        print(acc.details)
        menu(acc)
    elif (opt == '6'):
        print("Logged out\n")
        login()
    elif (opt == '7'):
        ask_create()
    elif (opt == '8'):
        pass
    else:
        print("Wrong Input!!\n")
        menu(acc)

def cr_acc():
    fname = input("Enter your first name:\t")
    sname = input("Enter your last name:\t")
    age = input("Enter your age:\t")
    if(int(age)<18):
        print("You are minor.. Sorry, you can't create bank account..!!\n")
        return
    deposit = input("Enter the deposit amount:\t")
    while True:
        try:
            username = input("Enter your username:\t")
            fln = f"{username}.txt"
            with open(fln, 'x'):
                pass
            break
        except:
            print("Invaid username...")
    password = ask_pw()
    pin = ask_pin()
    data = f"{username},{password}\n"
    with open("saved_accounts.txt", "a") as file:
        file.write(data)
    data = f"{fname}\n{sname}\n{age}\n{deposit}\n{pin}"
    with open(fln, 'w') as f:
        f.write(data)
    login()

if (__name__ == "__main__"):
    startup()
