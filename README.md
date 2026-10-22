1. Build and run on Linux or WSL with g++ && C++11
2. In this folder, run `cd titan-protocol/titan-protocol` then `make clean` then  `make` then `./titan-protocol`.
3. Expected output
    <Data> $1;15;6607;;| </Data>
    <Output> Ping: sequence=15, timestamp=6607 ms </Output>
    <Data2> $10;1;0;0;12000;-90000;68;-29950;| </Data2>
    <Output2> Housekeeping: sequence=1, timestamp=0 ms, status=0 (operational), theta=12.000 deg, phi=-90.000 deg, intensity=68, temperature=-29.950 deg 
    </Output2>




By default, it reads titan-protocol-capture.txt from the current working directory.
To use another file, run `./titan-protocol path/to/capture.txt` (quote paths containing spaces).
It prints each line with the decoded values underneath. The supplied capture has 20 Ping and 10 housekeeping messages.
----------------------------------------------------------------------------------------------------------------

As a note, I went with a C architecture in C++. This can be done with an Object-oriented approach, but i thought it would add unnecessary complexity in which virtual functions and allocating data to the heap might have to be managed. In addition, there was also a limited number of message classes so a struct approach for this issue seemed appropriate for the scale.

So I aimed to make this as readable as possible while keeping time and space complexity low. I tried to structure the code so it was modular and easy to expand. However, theres an argument that objects could do this.

The solution tries to read messages line by line, handling a common header between messages and storing the data in a relevant structure. Then, based on the command ID, it handles the payload.

To store the data from the file, we read each character and convert digit characters to numbers by subtracting `0`, rejecting any that isn't a valid number, and append based on the unit.


Known Issues
1. Multiple messages on one line: I assumed each message is on a new line. To fix this, I'd read until a '|' is seen.
2. I didn't test SENSOR_FAILURE as the script was broken. I didn't have time to investigate/fix this issue and unit tests are missing.

