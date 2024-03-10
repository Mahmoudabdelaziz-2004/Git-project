# function to convert decimal number to binary number
def decimal_to_binary(number):
    binary = ""
    number = int(number)
    while number > 0:
        binary = str(number % 2) + binary
        number = number // 2
    return binary

# function to convert decimal number to octal number
def decimal_to_octal(number):
    octal = ""
    number = int(number)
    while number > 0:
        octal = str(number % 8) + octal
        number = number // 8
    return octal

# function to convert decimal number to hexadecimal number
def decimal_to_hexadecimal(number):
    hexadecimal = ""
    hex_digits = "0123456789ABCDEF"
    number = int(number)
    while number > 0:
        remainder = number % 16
        hexadecimal = hex_digits[remainder] + hexadecimal     # we used this hex_digits[remainder] to get the value of the reminder position on the list of hexa digit
        number = number // 16
    return hexadecimal

# function to convert binary number to decimal number
def binary_to_decimal(number):
    decimal = 0
    i = 0
    number = int(number)
    while number > 0:
      digit = number % 10
      decimal = decimal + digit * (2**i)
      number = number // 10
      i = i + 1
    return decimal

# function to convert octal number to decimal number
def octal_to_decimal(number):
    decimal = 0
    i = 0
    number = int(number)
    while number > 0:
      digit = number % 10
      decimal = decimal + digit * (8**i)
      number = number // 10
      i = i + 1
    return decimal

# function to convert hexadecimal number to decimal number
def hexadecimal_to_decimal(number):
    decimal = 0
    hex_digits = "0123456789ABCDEF"
    for digit in number:
        decimal = decimal * 16 + hex_digits.index(digit)
    return decimal


# the main function of the numbering system converter
def numbering_system_converter():
    while True:

      print("\n** numbering system converter **")
      print("A) insert a new number")
      print("B) Exit program")
      choice = input("Enter your choice: ")
      if choice == 'A':
        number = input("Please insert a number: ")
        # if function to check if the inserted number is valid for our system converter
        if all(digit in '0123456789ABCDEF' for digit in str(number)):

          while True:
            print("\n** Please select the base you want to convert a number from **")
            print("A) Decimal")
            print("B) Binary")
            print("C) octal")
            print("D) hexadecimal")
            from_base = input("Enter your choice: ")
            if from_base in ['A', 'B', 'C', 'D']:
              break
            else:
                print("Please select a valid choice")
          while True:
            print("\n** Please select the base you want to convert a number to**")
            print("A) Decimal")
            print("B) Binary")
            print("C) octal")
            print("D) hexadecimal")
            to_base = input("Enter your choice: ")
            if to_base in ['A', 'B', 'C', 'D']:
              break
            else:
                print("Please select a valid choice")
          if  from_base == 'A' and to_base == 'B':
            # if function to check if the inserted number is in base 10 or not
            if all(digit in '0123456789' for digit in str(number)):
              number = decimal_to_binary(number)
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 10, please enter a valid number")
          elif  from_base == 'A' and to_base == 'C':
            if all(digit in '0123456789' for digit in str(number)):
              number = decimal_to_octal(number)
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 10, please enter a valid number")
          elif  from_base == 'A' and to_base == 'D':
            if all(digit in '0123456789' for digit in str(number)):
              number = decimal_to_hexadecimal(number)
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 10, please enter a valid number")
          elif  from_base == 'B' and to_base == 'A':
            # if function to check if the inserted number is in base 2 or not
            if all(digit in '01' for digit in str(number)):
              number = binary_to_decimal(number)
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 2, please enter a valid number")
          elif  from_base == 'C' and to_base == 'A':
            # if function to check if the inserted number is in base 8 or not
            if all(digit in '0123456789' for digit in str(number)):
              number = octal_to_decimal(number)
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 8, please enter a valid number")
          elif  from_base == 'D' and to_base == 'A':
            number = hexadecimal_to_decimal(number)
            print (number)
          elif  from_base == 'B' and to_base == 'C':
            if all(digit in '01' for digit in str(number)):
              # to convert from binary number to octal number: firstly we convert the binary number to decimal number then convert the decimal number to octal number
              number = decimal_to_octal(binary_to_decimal(number))
              print (number)
            else:
              print ("Error ", number, "is not a valid number in base 2, please enter a valid number")
          elif  from_base == 'B' and to_base == 'D':
            if all(digit in '01' for digit in str(number)):
              # to convert from binary number to hexadecimal number: firstly we convert the binary number to decimal number then convert the decimal number to hexadecimal number
              number = decimal_to_hexadecimal(binary_to_decimal(number))
              print (number)
            else:
              print ("Error ", number, "is not a valid number in base 2, please enter a valid number")
          elif  from_base == 'C' and to_base == 'B':
            if all(digit in '0123456789' for digit in str(number)):
              # to convert from octal number to binary number: firstly we convert the octal number to decimal number then convert the decimal number to binary number
              number = decimal_to_binary(octal_to_decimal(number))
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 8, please enter a valid number")
          elif  from_base == 'C' and to_base == 'D':
            if all(digit in '0123456789' for digit in str(number)):
              # to convert from octal number to hexadecimal number: firstly we convert the octal number to decimal number then convert the decimal number to hexadecimal number
              number = decimal_to_hexadecimal(octal_to_decimal(number))
              print (number)
            else:
              print ("Error: ", number, "is not a valid number in base 8, please enter a valid number")
          elif  from_base == 'D' and to_base == 'B':
            # to convert from hexadecimal number to binary number: firstly we convert the hexadecimal number to decimal number then convert the decimal number to binary number
            number = decimal_to_binary(hexadecimal_to_decimal(number))
            print (number)
          elif  from_base == 'D' and to_base == 'C':
             # to convert from hexadecimal number to octal number: firstly we convert the hexadecimal number to decimal number then convert the decimal number to octal number
            number = decimal_to_octal(hexadecimal_to_decimal(number))
            print (number)
          elif from_base == 'A' and to_base == 'A':
            if all(digit in '0123456789' for digit in str(number)):
              print ( "the result is the same value: ", number)
            else:
              print ("Error: ", number, "is not a valid number in base 10, please enter a valid number")
          elif from_base == 'B' and to_base == 'B':
            if all(digit in '01' for digit in str(number)):
              print ("the result is the same value: ", number)
            else:
              print ("Error ", number, "is not a valid number in base 2, please enter a valid number")
          elif from_base == 'C' and to_base == 'C':
            if all(digit in '0123456789' for digit in str(number)):
              print ("the result is the same value: ", number)
            else:
              print ("Error: ", number, "is not a valid number in base 8, please enter a valid number")
          elif from_base == 'D' and to_base == 'D':
            print ("the result is the same value: ", number)
        else:
          print ("Wrong number, Please enter a valid number ")    
      elif choice == 'B':
          print ("Exiting program")
          break
      else:
          print (" please select a valid choice")

numbering_system_converter()