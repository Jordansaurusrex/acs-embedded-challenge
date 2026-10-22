1. port into Linux
2. In this folder, run `make` then `./titan-protocol`.
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

As a note I went with a C architecture in C++ as this is a satelitte company so i was unsure of the space(memory) overhead of using objects. Preferably I'd have used just C but some C++ standard libraries were too useful not include. 

So I aimed to make this as readable as possible while keeping time complexity low and space complexity. I tried to structure the code so it was modular and was easy to expand. However i acknowledge objects could probably do a better job of this.

The soloution tries to read messages line by line, handling a common header between messages and storing the data into a relevant structure. Then based on the command ID handle the payload.

To read the data from the file, we read each char and shift from ASCII to numbers rejecting any that isnt a valid number and append based on the unit.


Known Issues
1. multiple messages on 1 line, I assuemd each message is on a new line, to fix id read until a'|' is seen.
2. didnt test SENSOR_FAILURE as the script was broken- i didnt have time to investigate/fix this issue
