**Clion Build Steps**
-
In the project directory, place your log file into the cmake-build-debug folder  

In the Clion project, go to...

-> Run / Debug Configurations -> Edit Configurations

In the Program arguments box Enter "your filename".csv

Click OK

Then click on run 'Coursework_for_Viva'

Program will put the generated Quality_Report.txt into the cmake-build-debug project folder

**Command Line Build Steps**
-
Locate the file where all the c files reside

Put your (yourlogfilename).csv log file into that folder

Open command prompt

type "cd directory/of/the/file"

type "gcc main.c io.c waveform.c -o waveform_analyser

Note - if gcc is not a recognised command, you will need to install it through MSYS64

To run the program, type ".\waveform_analyser.exe (yourlogfilename).csv"

Program should report a successful file creation message, if not check the csv file is present in the directory and you named it right

Once successful, the created Quality_Report.txt file can be found in that same directory
