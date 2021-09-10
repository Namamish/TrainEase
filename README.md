# Cpp-Project
I have made a Train Reservation Management Project using C++. This was the first project made by me during my 12th Practicals, and I have blended my whole syllabus in one code. I have used mainly File Handling and Object Oriented Programming Concepts in this Project.


Key Features:

1. It has User Management as I have created 2 modes, one is the Admin Mode and one is the User Mode.

2. It has a "inputpassword()" function that user can input password and he will see the "asterisk"(*) on screen and user can use backspace to delete the wrong character. Also, user can include "Space" in his password. This has been done using "getch()" function included in non-standard C++ library "conio.h".

3. The code is well structured.

4. The Admin can add data of Train and Station Lists and their distance from source and also Advanced Reservation Period, also Admin can add number of available seats on all dates within Advanced Reservation Period. Also, he can add price per kilometres for first class and second class so that the price will be generated automatically when the user will make booking. The admin can view and manage the whole data of trains.

5. The user can create his own account for booking and create his own username and Password. The code will ensure that Username should be unique and I have added constraints on Password size also.

6. The User can make booking conveniently but there is one more feature which I have added that the User will not get the PNR number and his seat will not be booked until he makes the payment. After booking, the booking details will go to Admin section and as soon Admin confirms the booking, the seat availability status gets updated.

7. There is also a ticket cancellation feature given to a user.

